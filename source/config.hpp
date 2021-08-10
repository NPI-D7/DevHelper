#include "ini.hpp"

class Config
{
     public:
     Config(){}
     ~Congig(){}
     private:
     INI::INIFile cfile;
     INI::INIStructure cstruct;
};
