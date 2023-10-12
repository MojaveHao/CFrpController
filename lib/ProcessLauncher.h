#ifndef CFRPCONTROLLER_PROCESSLAUNCHER_H
#define CFRPCONTROLLER_PROCESSLAUNCHER_H

#include <string>
#include <future>
#include <filesystem>
#include <stdexcept>
#include <array>


#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
#endif

using std::string;
using std::future;
using std::filesystem::path;

class ProcessLauncher
{
public:
    static void launch(const string& filePath, const string& args);
    static future<string> launchAsync(const string& filePath, const string& args);
};

#endif //CFRPCONTROLLER_PROCESSLAUNCHER_H
