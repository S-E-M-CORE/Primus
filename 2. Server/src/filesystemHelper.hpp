#ifndef FILESYSTEM_CLIENT_H
#define FILESYSTEM_CLIENT_H

#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#elif __linux__
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace primus {
    namespace component {
        // Not fully functional. May be implemented later on
//         std::string getExecutablePath()
//         {
//             char buffer[FILENAME_MAX];
// #ifdef _WIN32
//             GetModuleFileNameA(NULL, buffer, FILENAME_MAX);
// #elif __linux__
//             ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
//             if (len != -1) {
//                 buffer[len] = '\0';
//             }
// #endif
//             return std::string(buffer);
//         }
// 
//         bool createDirectory(const std::string& path)
//         {
// #ifdef _WIN32
//             if (_mkdir(path.c_str()) == 0) {
// #elif __linux__
//             if (mkdir(path.c_str(), 0777) == 0) {
// #endif
//                 return true;
//             }
//             else {
//                 return false;
//             }
//         }
// 
//         bool createFile(const std::string & fileName, const std::string & content)
//         {
//             std::ofstream file(fileName);
//             if (file.is_open()) {
//                 file << content;
//                 file.close();
//                 return true;
//             }
//             else {
//                 return false;
//             }
//         }
    } // namespace component
} // Namespace primus
#endif // FILESYSTEM_CLIENT_H
