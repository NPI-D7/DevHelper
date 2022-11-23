#include "nightlyreader.hpp"
#include "cia.hpp"
#include "download.hpp"
#include <iostream>
#include <rd7.hpp>
#include <renderd7/log.hpp>

#include <Tasks.hpp>

#include <curl/curl.h>

extern float DLTotal;
extern float DLNow;

extern Log flog;

extern bool showProgressBar;
extern int progressBarType;

void DBLoader::DownloadEntry(int index) {
  this->versions.clear();
  std::string s = "sdmc:/DevHelper/dbs/" + DBLoader::GetRepoName() + "/";
  mkdir("sdmc:/DevHelper/", 0777);
  mkdir("sdmc:/DevHelper/dbs/", 0777);
  mkdir(s.c_str(), 0777);

  if (index <= (int)this->db.e_list.size() + 1) {
    showProgressBar = true;
    Tasks::create((ThreadFunc)displayProgressBar);
    downloadToFile(
        this->db.e_list[index].dl_link,
        "sdmc:/DevHelper/dbs/" + DBLoader::GetRepoName() + "/" +
            GetFileName<std::string>(this->db.e_list[index].dl_link));
    showProgressBar = false;
  } else {
    RenderD7::AddOvl(std::make_unique<Warnings>("Menu->Error",
                                                "What are you trying to do?"));
  }
}

void DBLoader::Download3dsx(int index) {
  std::string s = "sdmc:/3ds/";
  mkdir(s.c_str(), 0777);
  showProgressBar = true;
  Tasks::create((ThreadFunc)displayProgressBar);
  downloadToFile(this->versions[index].dl_3dsx,
                 s + GetFileName<std::string>(this->versions[index].dl_3dsx));
  showProgressBar = false;
  if (this->versions[index].Name == "DevHelper") {
    RenderD7::AddOvl(std::make_unique<Warnings>(
        "Menu->Info", "Restart the App to apply changes..."));
  }
}

void DBLoader::InstallCia(int index) {
  std::string s = "sdmc:/DevHelper/cache/";

  bool ___is___ = false;
  mkdir(s.c_str(), 0777);
  if (this->versions[index].Name == "DevHelper") {
    ___is___ = true;
    RenderD7::AddOvl(std::make_unique<Warnings>(
        "Menu->Info", "Normally the app should Update it Self..."));
  }
  showProgressBar = true;
  Tasks::create((ThreadFunc)displayProgressBar);
  downloadToFile(this->versions[index].dl_cia,
                 s + GetFileName<std::string>(this->versions[index].dl_cia));
  std::string pathof =
      s + GetFileName<std::string>(this->versions[index].dl_cia);
  progressBarType = 1;
  flog.Write(pathof);
  Result res = installCia(pathof.c_str(), ___is___);
  if (res != R_OK) {
    RenderD7::AddOvl(std::make_unique<Errors>(res));
    RenderD7::AddOvl(std::make_unique<Warnings>(
        "Installer->Error", "Error when installing Cia file!\n"));
  }
  progressBarType = 0;
  showProgressBar = false;
  RenderD7::Msg::Display("DevHelper->Download-Cia", "Deleting Cia ...", Top);
  // remove(pathof.c_str());
}

void DBLoader::LoadDB(std::string link) {
  int dtmm = 0;
  mkdir("sdmc:/DevHelper/", 0777);
  mkdir("sdmc:/DevHelper/dbs/", 0777);
  showProgressBar = true;
  Tasks::create((ThreadFunc)displayProgressBar);
  downloadToFile(link, "sdmc:/DevHelper/dbs/" + GetFileName<std::string>(link));
  showProgressBar = false;
  INI::INIFile file("sdmc:/DevHelper/dbs/" + GetFileName<std::string>(link));
  INI::INIStructure ini;
  file.read(ini);
  this->db.reponame = ini["info"]["repository"];
  this->db.repo_host = ini["info"]["user"];
  DB_Entry dbe;
  for (auto const &it : ini) {
    auto const &section = it.first;
    std::cout << "[" << section << "]" << std::endl;
    this->secs.push_back(section);
    RenderD7::Msg::DisplayWithProgress("DevHelper", "Reading Database Sections",
                                       dtmm, (int)ini.size(),
                                       RenderD7::Color::Hex("#00ff00"));
    if (ini[section]["name"] != "") {
      dbe = {ini[section]["name"], ini[section]["data"]};
      this->db.e_list.push_back(dbe);
    }
    dtmm++;
  }
}

void DBLoader::LoadEntry(int index) {
  int dtmm = 0;
  INI::INIFile file("sdmc:/DevHelper/dbs/" + DBLoader::GetRepoName() + "/" +
                    GetFileName<std::string>(this->db.e_list[index].dl_link));
  INI::INIStructure ini;
  file.read(ini);
  APPH dbe;
  this->appsecs.clear();
  this->versions.clear();
  for (auto const &it : ini) {

    auto const &section = it.first;
    std::cout << "[" << section << "]" << std::endl;
    this->appsecs.push_back(section);
    RenderD7::Msg::DisplayWithProgress("DevHelper", "Reading APPV Sections",
                                       dtmm, (int)ini.size(),
                                       RenderD7::Color::Hex("#00ff00"));
    dbe = {ini[section]["name"],       ini[section]["author"],
           ini[section]["commit_tag"], ini[section]["desc"],
           ini[section]["version"],    ini[section]["3dsx"],
           ini[section]["cia"]};
    this->versions.push_back(dbe);
    dtmm++;
  }
  std::reverse(this->versions.begin(), this->versions.end());
}
