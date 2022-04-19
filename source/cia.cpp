#include "cia.hpp"
#include <stdio.h>
#include <cstdlib>
extern "C"
{
	#include "fs.h"
}


Result CIA_LaunchTitle(u64 titleId, FS_MediaType mediaType) {
	Result ret = 0;
	u8 param[0x300];
	u8 hmac[0x20];

	if (R_FAILED(ret = APT_PrepareToDoApplicationJump(0, titleId, mediaType))) {
		printf("Error In:\nAPT_PrepareToDoApplicationJump");
		return ret;
	}
	if (R_FAILED(ret = APT_DoApplicationJump(param, sizeof(param), hmac))) {
		printf("Error In:\nAPT_DoApplicationJump");
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
		return ret;
	}

	u32 read_titles = 0;
	u64 * titleIDs = (u64*)malloc(titles_amount * sizeof(u64));
	ret = AM_GetTitleList(&read_titles, media, titles_amount, titleIDs);
	if (R_FAILED(ret)) {
		free(titleIDs);
		printf("Error in:\nAM_GetTitleList\n");
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
		return ret;
	}

	return 0;
}

FS_MediaType getTitleDestination(u64 titleId) {
	u16 platform = (u16) ((titleId >> 48) & 0xFFFF);
	u16 category = (u16) ((titleId >> 32) & 0xFFFF);
	u8 variation = (u8) (titleId & 0xFF);

	//     DSiWare                3DS                    DSiWare, System, DLP         Application           System Title
	return platform == 0x0003 || (platform == 0x0004 && ((category & 0x8011) != 0 || (category == 0x0000 && variation == 0x02))) ? MEDIATYPE_NAND : MEDIATYPE_SD;
}

// Variables.
u64 installSize = 0, installOffset = 0;

Result installCia(const char * ciaPath, bool updatingSelf) {
    u64 size = 0;
    u32 bytes;
    Handle ciaHandle, fileHandle;
    AM_TitleEntry info;
    
    result = FSUSER_OpenFileDirectly(&fileHandle, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""), fsMakePath(PATH_ASCII, ciaPath.c_str()), FS_OPEN_READ, 0);
    if (R_FAILED(result))
    {
        return;
    }
    
    if (R_FAILED(result = AM_GetCiaFileInfo(MEDIATYPE_SD, &info, fileHandle)))
    {
        return;
    }
    
    deletePrevious(info.titleID);
    if (R_FAILED(result))
    {
        return;
    }
    
    if (R_FAILED(result = FSFILE_GetSize(fileHandle, &size)))
    {
        return;
    }

    if (R_FAILED(result = AM_StartCiaInstall(MEDIATYPE_SD, &ciaHandle)))
    {
        return;
    }
    
    u32 toRead = 0x1000;
    u8* cia_buffer = malloc(toRead);
    for (u64 startSize = size; size != 0; size -= toRead)
    {
        if (size < toRead) toRead = size;
        FSFILE_Read(fileHandle, &bytes, startSize-size, cia_buffer, toRead);
        FSFILE_Write(ciaHandle, &bytes, startSize-size, cia_buffer, toRead, 0);
    }
    free(cia_buffer);

    if (R_FAILED(result = AM_FinishCiaInstall(ciaHandle)))
    {
        return;
    }

    result = FSFILE_Close(fileHandle);
}
