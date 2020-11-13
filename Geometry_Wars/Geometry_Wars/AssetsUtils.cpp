#include "AssetsUtils.h"
#include <windows.h>

string getAppPath() {
    char cExeFilePath[256];
    GetModuleFileNameA(NULL, cExeFilePath, 256);
    string exeFilePath = cExeFilePath;
    int exeNamePos = exeFilePath.find_last_of("\\/");
    string appPath = exeFilePath.substr(0, exeNamePos + 1);
    return appPath;
}

string getAssetsPath() {
    string assetsPath = getAppPath() + "\Assets\/";
    return assetsPath;
}