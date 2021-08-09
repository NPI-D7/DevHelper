#include "ini.hpp"

struct DB_Entry = 
{
     std::string name;
     std::string dl_link;
}
struct DB =
{
     std::string reppname;
     std::string repo_host;
     std::vector<DB_Entry> e_list;
};

struct APPH =
{
     std::string Name;
};
