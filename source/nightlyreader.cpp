#include "nightlyreader.hpp"

void DBLoader::DownloadEntry(int index)
{
     downloadToFile(this->db.e_list[index].dl_link);
}
