#include "nightlyreader.hpp"

void DBLoader::DownloadEntry(int index)
{
     if (index <= (int)this->db.e_list.size() + 1) downloadToFile(this->db.e_list[index].dl_link, "sdmc:/DevHelper/dbs/" + DBLoader::GetRepoName() + "/" + GetFileName(this->db.e_list[index].dl_link));
     else int i = 0;
}

void DBLoader::LoadDB(std::string link)
{
     downloadToFile(link, "sdmc:/DevHelper/dbs/" + GetFileName(link));
     INI::INIFile file;
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
