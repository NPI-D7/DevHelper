#include "cia.hpp"
#include "Ovls.hpp"
#include <cstdlib>
#include <renderd7/log.hpp>
#include <stdio.h>

extern Log flog;

Result CIA_LaunchTitle(u64 titleId, FS_MediaType mediaType) {
  Result ret = 0;
  u8 param[0x300];
  u8 hmac[0x20];

  if (R_FAILED(ret = APT_PrepareToDoApplicationJump(0, titleId, mediaType))) {
    printf("Error In:\nAPT_PrepareToDoApplicationJump");
    RenderD7::AddOvl(std::make_unique<Warnings>(
        "Installer->Error", "Can't prepare Application Jump!"));
    return ret;
  }
  if (R_FAILED(ret = APT_DoApplicationJump(param, sizeof(param), hmac))) {
    printf("Error In:\nAPT_DoApplicationJump");
    RenderD7::AddOvl(std::make_unique<Warnings>("Installer->Error",
                                                "Can't do Application Jump!"));
    return ret;
  }

  return 0;
}

Result deletePrevious(u64 titleid, FS_MediaType media) {
  Result ret = 0;

  u32 titles_amount = 0;
  ret = AM_GetTitleCount(media, &titles_amount);
  if (R_FAILED(ret)) {
    printf("Error in:\nAM_GetTitleCount\n");
    flog.Write("Error: AM_GetTitleCount");
    RenderD7::AddOvl(std::make_unique<Warnings>("Installer->Error",
                                                "Can't get Title Count!"));
    return ret;
  }

  u32 read_titles = 0;
  u64 *titleIDs = (u64 *)malloc(titles_amount * sizeof(u64));
  ret = AM_GetTitleList(&read_titles, media, titles_amount, titleIDs);
  if (R_FAILED(ret)) {
    free(titleIDs);
    printf("Error in:\nAM_GetTitleList\n");
    flog.Write("Error: AM_GetTitleList");
    RenderD7::AddOvl(std::make_unique<Warnings>("Installer->Error",
                                                "Can't get Title List!"));
    return ret;
  }

  for (u32 i = 0; i < read_titles; i++) {
    if (titleIDs[i] == titleid) {
      ret = AM_DeleteAppTitle(media, titleid);
      break;
    }
  }

  free(titleIDs);
  if (R_FAILED(ret)) {
    printf("Error in:\nAM_DeleteAppTitle\n");
    flog.Write("Failed to delete Title");
    RenderD7::AddOvl(
        std::make_unique<Warnings>("Installer->Error", "Can't delete Title!"));
    return ret;
  }

  return 0;
}

FS_MediaType getTitleDestination(u64 titleId) {
  u16 platform = (u16)((titleId >> 48) & 0xFFFF);
  u16 category = (u16)((titleId >> 32) & 0xFFFF);
  u8 variation = (u8)(titleId & 0xFF);

  //     DSiWare                3DS                    DSiWare, System, DLP
  //     Application           System Title
  return platform == 0x0003 || (platform == 0x0004 &&
                                ((category & 0x8011) != 0 ||
                                 (category == 0x0000 && variation == 0x02)))
             ? MEDIATYPE_NAND
             : MEDIATYPE_SD;
}

// Variables.
u64 installSize = 0, installOffset = 0;

Result installCia(const char *ciaPath, bool updatingSelf) {
  u32 bytes_read = 0, bytes_written;
  installSize = 0, installOffset = 0;
  u64 size = 0;
  Handle ciaHandle, fileHandle;
  AM_TitleEntry info;
  Result ret = 0;
  FS_MediaType media = MEDIATYPE_SD;
  FSUSER_OpenFileDirectly(&fileHandle, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""), fsMakePath(PATH_ASCII, ciaPath), FS_OPEN_READ, 0);
  //ret = openFile(&fileHandle, ciaPath, false);
  if (R_FAILED(ret)) {
    std::cout << ("Error in:\nopenFile\n");
    RenderD7::AddOvl(std::make_unique<Warnings>(
        "Installer->Error", "File Not Found!\nC(" +
                                std::to_string(R_LEVEL(ret)) + ") - D(" +
                                std::to_string(R_DESCRIPTION(ret)) + ") - S(" +
                                std::to_string(R_SUMMARY(ret)) + ") - M(" +
                                std::to_string(R_MODULE(ret)) + ")"));
    flog.Write("Cant open File");
    return ret;
  }

  ret = AM_GetCiaFileInfo(media, &info, fileHandle);
  if (R_FAILED(ret)) {
    std::cout << ("Error in:\nAM_GetCiaFileInfo\n");
    RenderD7::AddOvl(std::make_unique<Warnings>(
        "Installer->Error", "Can't get Cia File Info!\nC(" +
                                std::to_string(R_LEVEL(ret)) + ") - D(" +
                                std::to_string(R_DESCRIPTION(ret)) + ") - S(" +
                                std::to_string(R_SUMMARY(ret)) + ") - M(" +
                                std::to_string(R_MODULE(ret)) + ")"));
    flog.Write("Cant get File Info");
    return ret;
  }

  media = getTitleDestination(info.titleID);

  if (!updatingSelf) {
    ret = deletePrevious(info.titleID, media);
    if (R_FAILED(ret)) {
      RenderD7::AddOvl(std::make_unique<Warnings>(
          "Installer->Error",
          "Can't delete File\nC(" + std::to_string(R_LEVEL(ret)) + ") - D(" +
              std::to_string(R_DESCRIPTION(ret)) + ") - S(" +
              std::to_string(R_SUMMARY(ret)) + ") - M(" +
              std::to_string(R_MODULE(ret)) + ")"));
      return ret;
    }
  }

  ret = FSFILE_GetSize(fileHandle, &size);
  if (R_FAILED(ret)) {
    std::cout << ("Error in:\nFSFILE_GetSize\n");
    RenderD7::AddOvl(std::make_unique<Warnings>(
        "Installer->Error", "Can't Get Cia File Size!\nC(" +
                                std::to_string(R_LEVEL(ret)) + ") - D(" +
                                std::to_string(R_DESCRIPTION(ret)) + ") - S(" +
                                std::to_string(R_SUMMARY(ret)) + ") - M(" +
                                std::to_string(R_MODULE(ret)) + ")"));
    flog.Write("Cant get File size");
    return ret;
  }
  ret = AM_StartCiaInstall(media, &ciaHandle);
  if (R_FAILED(ret)) {
    std::cout << ("Error in:\nAM_StartCiaInstall\n");
    RenderD7::AddOvl(std::make_unique<Warnings>(
        "Installer->Error", "Can't get File Size\nC(" +
                                std::to_string(R_LEVEL(ret)) + ") - D(" +
                                std::to_string(R_DESCRIPTION(ret)) + ") - S(" +
                                std::to_string(R_SUMMARY(ret)) + ") - M(" +
                                std::to_string(R_MODULE(ret)) + ")"));
    flog.Write("Cant start Install");
    return ret;
  }

  u32 toRead = 0x200000;
  u8 *buf = new u8[toRead];
  if (buf == nullptr) {
    return -1;
  }

  installSize = size;
  do {
    FSFILE_Read(fileHandle, &bytes_read, installOffset, buf, toRead);
    FSFILE_Write(ciaHandle, &bytes_written, installOffset, buf, toRead,
                 FS_WRITE_FLUSH);
    installOffset += bytes_read;
  } while (installOffset < installSize);
  delete[] buf;

  ret = AM_FinishCiaInstall(ciaHandle);
  if (R_FAILED(ret)) {
    std::cout << ("Error in:\nAM_FinishCiaInstall\n");
    RenderD7::AddOvl(std::make_unique<Warnings>(
        "Installer->Error", "Failed to finish Cia Install!\nC(" +
                                std::to_string(R_LEVEL(ret)) + ") - D(" +
                                std::to_string(R_DESCRIPTION(ret)) + ") - S(" +
                                std::to_string(R_SUMMARY(ret)) + ") - M(" +
                                std::to_string(R_MODULE(ret)) + ")"));
    flog.Write("Cant finish install");
    return ret;
  }

  ret = FSFILE_Close(fileHandle);
  if (R_FAILED(ret)) {
    std::cout << ("Error in:\nFSFILE_Close\n");
    RenderD7::AddOvl(std::make_unique<Warnings>(
        "Installer", "Failed to Close Handle!\nC(" +
                         std::to_string(R_LEVEL(ret)) + ") - D(" +
                         std::to_string(R_DESCRIPTION(ret)) + ") - S(" +
                         std::to_string(R_SUMMARY(ret)) + ") - M(" +
                         std::to_string(R_MODULE(ret)) + ")"));
    flog.Write("Cant close file");
    return ret;
  }

  if (updatingSelf) {
    if (R_FAILED(ret = CIA_LaunchTitle(info.titleID, MEDIATYPE_SD)))
      return ret;
  }
  FS_CloseArchive(sdmc_archive);
  return 0;
}
