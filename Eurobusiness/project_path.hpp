#ifndef PROJECT_PATH_HPP_INCLUDED
#define PROJECT_PATH_HPP_INCLUDED

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include <errno.h>
#include <stdio.h>

const char* project_path(string path, string file)
{
    string path_tmp = path;
    int tmp = path.find("bin");
    if(tmp > 0)
    {
        path_tmp.erase(tmp,path_tmp.size()-tmp);
        path_tmp += file;
    }
        else
    {
        path_tmp = file;
    }
     return const_cast<char*>(path_tmp.c_str());
}

string project_path_deprecated(char* file)
{
    string tmp = "";
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return tmp;
    }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

    printf("%s\n",cCurrentPath);

    tmp = cCurrentPath;
    tmp += "\\";
    tmp += file;

    std::cout << tmp << std::endl;

    return tmp;
}

#endif // PROJECT_PATH_HPP_INCLUDED
