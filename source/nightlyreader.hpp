#include "ini.hpp"

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
};

class DBLoader
{
     public:
     DBLoader(){}
     ~DBLoader(){}
     private:
};

class apploader
{
     public:
     apploader(){}
     ~apploader(){}
     private:
};
