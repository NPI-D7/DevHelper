#include "nightlyreader.hpp"

void DBLoader::DownloadEntry(int index)
{
     downloadToFile(this->db.e_list[index].dl_link, "sdmc:/DevHelper/dbs/" + GetFilename(this->db.e_list[index].dl_link));
}
