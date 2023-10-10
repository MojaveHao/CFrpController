#ifndef CFRPCONTROLLER_PROCESSLAUNCHER_H
#define CFRPCONTROLLER_PROCESSLAUNCHER_H

#include <string>
#include <future>

using std::string;
using std::future;

class ProcessLauncher
{
public:
    static void launch(const string& filePath, const string& args);
    static future<string> launchAsync(const string& filePath, const string& args);
};

#endif //CFRPCONTROLLER_PROCESSLAUNCHER_H
