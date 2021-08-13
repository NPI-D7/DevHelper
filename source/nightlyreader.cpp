#include "nightlyreader.hpp"
#include "renderd7.hpp"
#include "download.hpp"
#include <iostream>

void DBLoader::DownloadEntry(int index)
{
     std::string s = "sdmc:/DevHelper/dbs/" + DBLoader::GetRepoName() + "/";
     mkdir("sdmc:/DevHelper/", 0777);
     mkdir("sdmc:/DevHelper/dbs/", 0777);
     mkdir(s.c_str(), 0777);
     if (index <= (int)this->db.e_list.size() + 1) downloadToFile(this->db.e_list[index].dl_link, "sdmc:/DevHelper/dbs/" + DBLoader::GetRepoName() + "/" + GetFileName<std::string>(this->db.e_list[index].dl_link));
     else {/** Do Nothing Yet*/}
}

void DBLoader::LoadDB(std::string link)
{
     mkdir("sdmc:/DevHelper/", 0777);
     mkdir("sdmc:/DevHelper/dbs/", 0777);
     downloadToFile(link, "sdmc:/DevHelper/dbs/" + GetFileName<std::string>(link));
     INI::INIFile file("sdmc:/DevHelper/dbs/" + GetFileName<std::string>(link));
     INI::INIStructure ini;
     file.read(ini);
     this->db.reponame = ini["info"]["repository"];
     this->db.repo_host = ini["info"]["user"];
     DB_Entry dbe;
     for (auto const& it : ini)
     {
	     auto const& section = it.first;
	     auto const& collection = it.second;
	     std::cout << "[" << section << "]" << std::endl;
             this->secs.push_back(section);
	     for (int i = 1; i < (int)this->secs.size(); i++)
	     {
		     dbe = {ini[this->secs[i]]["name"], ini[this->secs[i]]["data"]};
                     this->db.e_list.push_back(dbe);
	     }
     }
}
