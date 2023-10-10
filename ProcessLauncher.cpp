#include "ProcessLauncher.h"
#include <stdexcept>
#include <thread>
#include <array>
#include <iostream>

using std::string;
using std::future;
using std::async;
using std::launch;

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
#endif

void ProcessLauncher::launch(const string& filePath, const string& args)
{
#ifdef _WIN32
    string command = filePath + " " + args;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    path p(filePath);
    string directory = p.parent_path().string();

    if (!CreateProcess(NULL, const_cast<char*>(command.c_str()), NULL, NULL, FALSE, 0, NULL, directory.empty() ? NULL : directory.c_str(), &si, &pi))
    {
        throw std::runtime_error("CreateProcess failed");
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
#else
    pid_t pid = fork();

    if (pid < 0)
    {
        throw std::runtime_error("fork failed");
    }
    else if (pid == 0)
    {
        execl(filePath.c_str(), filePath.c_str(), args.c_str(), (char*)NULL);
        exit(EXIT_FAILURE);
    }
#endif
}

future<string> ProcessLauncher::launchAsync(const string& filePath, const string& args)
{
    return async(launch::async, [=]() {
        string output;

#ifdef _WIN32
        // Windows-specific code to launch and read from the process
        // ...
#else
        string command = filePath + " " + args;
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe)
        {
            throw std::runtime_error("popen failed");
        }

        std::array<char, 128> buffer;
        while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
        {
            output += buffer.data();
            std::cout << buffer.data(); // Print the output in real-time
        }

        pclose(pipe);
#endif

        return output;
    });
}
