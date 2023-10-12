#include "Classes.h"
#include "cpptoml.h"
#include <iostream>
#include <string>
#include <vector>

using std::string,std::vector;

class CFrpClasses::baseFrp {
public:
    string name;
    string path;
    vector<string> args;
    static inline CFrpClasses::baseFrp readInfo(const string& path,const string& name);
    void startFrp();
};

class CFrpClasses::paidFrpProviderInfo:public CFrpClasses::baseFrp {
public:
    string user;
    string proxy;
};

CFrpClasses::baseFrp CFrpClasses::baseFrp::readInfo(const string& path,const string& name)
{
    std::shared_ptr<cpptoml::table> config = cpptoml::parse_file(path);
    cpptoml::option<string> cname;
    cname = config->get_qualified_as<string>(name + ".name");
    cpptoml::option<string> cpath;
    cpath = config->get_qualified_as<string>(name + ".path");

}

void CFrpClasses::baseFrp::startFrp()
{
    string args_str;
    for (const string& arg : args)
    {
        args_str += arg;
        args_str += " "; // 在每一项后添加空格，如果需要的话
    }
    string command = path + " " + args_str;
}