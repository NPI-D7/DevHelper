#include "nightlyreader.hpp"

void DBLoader::DownloadEntry(int index)
{
     if (index <= (int)this->db.e_list.size() + 1) downloadToFile(this->db.e_list[index].dl_link, "sdmc:/DevHelper/dbs/" + GetFilename(this->db.e_list[index].dl_link));
     else int i = 0;
}
