#include "nightlyreader.hpp"

void DBLoader::DownloadEntry(int index)
{
     if (index <= (int)this->db.e_list.size() + 1) downloadToFile(this->db.e_list[index].dl_link, "sdmc:/DevHelper/dbs/" + DBLoader::GetRepoName() + "/" + GetFilename(this->db.e_list[index].dl_link));
     else int i = 0;
}

void DBLoader::DoenloadDB(std::string link)
{
     downloadToFile(link, "sdmc:/DevHelper/dbs/" + GetFileName(link));
     
     for (auto const& it : ini)
     {
	     auto const& section = it.first;
	     auto const& collection = it.second;
	     std::cout << "[" << section << "]" << std::endl;
	     for (auto const& it2 : collection)
	     {
		     auto const& key = it2.first;
		     auto const& value = it2.second;
		     std::cout << key << "=" << value << std::endl;
	     }
     }
}
