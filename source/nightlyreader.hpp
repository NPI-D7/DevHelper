#include "ini.hpp"
#include <string>
#include <vector>

struct DB_Entry
{
     std::string name;
     std::string dl_link;
}
struct DB
{
     std::string reppname;
     std::string repo_host;
     std::vector<DB_Entry> e_list;
};

struct APPH
{
     std::string Name;
     std::string author;
     std::string commit_tag;
     std::string desc;
     std::string ver;
     std::string dl_3dsx;
     std::string dl_cia;
};

class DBLoader
{
     public:
     DBLoader(){}
     ~DBLoader(){}
     private:
     DB db;
};

class apploader
{
     public:
     apploader(){}
     ~apploader(){}
     private:
};
