#pragma once
#include "ini.hpp"
#include <string>
#include <vector>
#define D_P() \
        std::cout << "\u001b[33;1mBreakpoint reached: \n" << (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) << ":" << __LINE__ << "\u001b[0m\n";


struct DB_Entry
{
     std::string name;
     std::string dl_link;
};
struct DB
{
     std::string reponame;
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
     void LoadDB(std::string link);
     void DownloadEntry(int index);
     std::string GetRepoName(){ return this->db.reponame; }
     std::string GetRepoHost(){ return this->db.repo_host; }
     DB db;
     private:
     std::vector<std::string> secs;
};

class apploader
{
     public:
     apploader(){}
     ~apploader(){}
     private:
};
