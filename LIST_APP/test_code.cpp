// #include <windows.h>
// #include <tlhelp32.h>
// #include <iostream>

// int main()
// {
//     // Create a snapshot of the current processes
//     HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

//     if (hSnapshot == INVALID_HANDLE_VALUE) {
//         std::cout << "Failed to create process snapshot.\n";
//         return 1;
//     }

//     // Get the first process in the snapshot
//     PROCESSENTRY32 pe32;
//     pe32.dwSize = sizeof(PROCESSENTRY32);

//     if (!Process32First(hSnapshot, &pe32)) {
//         std::cout << "Failed to get first process in snapshot.\n";
//         CloseHandle(hSnapshot);
//         return 1;
//     }

//     // Loop through all the processes in the snapshot and print their names
//     do {
//         std::cout << "Process name: " << pe32.szExeFile << "\n";
//     } while (Process32Next(hSnapshot, &pe32));

//     CloseHandle(hSnapshot);
//     return 0;
// }

// #include <windows.h>
// #include <iostream>
// #include <psapi.h>

// int main()
// {
//     // Enumerate the top-level windows
//     HWND hwnd = NULL;
//     while ((hwnd = FindWindowEx(NULL, hwnd, NULL, NULL)) != NULL) {
//         // Get the process ID of the window
//         DWORD processId;
//         GetWindowThreadProcessId(hwnd, &processId);

//         // Get the handle to the process
//         HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId);

//         // Get the executable name of the process
//         if (hProcess != NULL) {
//             char exeName[MAX_PATH];
//             DWORD exeNameSize = sizeof(exeName);
//             if (GetProcessImageFileNameA(hProcess, exeName, exeNameSize)) {
//                 std::cout << "Application name: " << exeName << "\n";
//             }
//             CloseHandle(hProcess);
//         }
//     }

//     return 0;
// }

// #include <iostream>
// #include <cstdio>
// #include <cstdlib>

// int main() {
//     // Thực thi lệnh "Get-AppxPackage" trong PowerShell và lưu kết quả vào file tạm thời
//     system("powershell Get-ItemProperty HKLM:\\Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\* | Select-Object * | Format-Table -Wrap -AutoSize");

//     // Mở file tạm thời chứa kết quả
//     FILE *fp = fopen("appxpackages.txt", "r");

//     if (fp != NULL) {
//         char buffer[1024];

//         // Đọc từng dòng trong file và trích xuất tên ứng dụng
//         while (fgets(buffer, sizeof(buffer), fp)) {
//             std::string line(buffer);

//             // Tìm vị trí đầu tiên của tên ứng dụng
//             size_t pos = line.find("Name : ");

//             if (pos != std::string::npos) {
//                 // Lấy phần tử con của chuỗi chứa tên ứng dụng
//                 std::string app_name = line.substr(pos + 7);

//                 // In tên ứng dụng
//                 std::cout << app_name << std::endl;
//             }
//         }

//         // Đóng file và xóa file tạm thời
//         fclose(fp);
//         // remove("appxpackages.txt");
//     }

//     return 0;
// }

// #include <iostream>
// #include <fstream>
// #include <string>

// int main()
// {
//     // Thực hiện lệnh PowerShell để lấy danh sách các ứng dụng
//     // system("Get-ItemProperty HKLM:\\Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\* | Select-Object InstallLocation| Format-Table -AutoSize > appxpackages.txt");
//     // system("C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe Get-ItemProperty HKLM:\\Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\* | Select-Object InstallLocation| Format-Table -AutoSize > appxpackages.txt");
//     // system("C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe -command \"& {Import-Module 'C:\\Program Files\\WindowsPowerShell\\Modules\\Microsoft.PowerShell.Utility\\Microsoft.PowerShell.Utility.psd1'; Get-ItemProperty HKLM:\\Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\* | Format-Table -Property InstallLocation -AutoSize > appxpackages.txt}\"");
//     system("C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe -command \"& {Import-Module -Name Microsoft.PowerShell.Utility; Get-ItemProperty HKLM:\\Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\* | Format-Table -Wrap -Property InstallLocation -AutoSize > appxpackages.txt}\"");

//     // Đọc danh sách các ứng dụng từ file
//     std::ifstream file("appxpackages.txt");
//     std::string line;
//     while (std::getline(file, line) && line != "")
//     {
//         std::cout << line << std::endl;
//     }
//     file.close();

//     return 0;
// }

// #include <iostream>
// #include <fstream>
// #include <string>

// int main()
// {
//     // Thực hiện lệnh PowerShell để lấy danh sách các ứng dụng
//     system(R"(C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -command "& {Import-Module -Name Microsoft.PowerShell.Utility; Get-ItemProperty HKLM:\Software\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall\* | Format-Table -Wrap -Property InstallLocation -AutoSize > appxpackages.txt}")");

//     // Đọc danh sách các ứng dụng từ file
//     std::ifstream file("appxpackages.txt");
//     std::string line;
//     while (std::getline(file, line) && line != "")
//     {
//         size_t pos = line.find("InstallLocation");
//         if (pos != std::string::npos)
//         {
//             std::string exePath = line.substr(pos + 17);
//             size_t firstNotSpace = exePath.find_first_not_of(" \t\r\n");
//             if (firstNotSpace != std::string::npos)
//             {
//                 exePath = exePath.substr(firstNotSpace);
//                 std::cout << exePath << std::endl;
//             }
//         }
//     }
//     file.close();

//     return 0;
// }

// oke
// #include <Windows.h>
// #include <iostream>
// #include <vector>
// #include <string>

// #pragma comment(lib, "advapi32.lib")

// int main()
// {
//     std::vector<std::string> installed_programs;

//     HKEY hKey;
//     if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ | KEY_WOW64_32KEY, &hKey) != ERROR_SUCCESS) {
//         std::cerr << "Failed to open registry key" << std::endl;
//         return 1;
//     }

//     char szDisplayName[1024];
//     char szKeyName[1024];
//     DWORD dwSize = sizeof(szDisplayName);

//     for (DWORD i = 0, retValue = ERROR_SUCCESS; retValue == ERROR_SUCCESS; ++i) {
//         retValue = RegEnumKeyEx(hKey, i, szKeyName, &dwSize, NULL, NULL, NULL, NULL);
//         dwSize = sizeof(szKeyName);

//         if (retValue == ERROR_SUCCESS) {
//             HKEY hSubKey;
//             if (RegOpenKeyEx(hKey, szKeyName, 0, KEY_READ | KEY_WOW64_32KEY, &hSubKey) == ERROR_SUCCESS) {
//                 dwSize = sizeof(szDisplayName);
//                 if (RegQueryValueEx(hSubKey, "DisplayName", NULL, NULL, (LPBYTE)szDisplayName, &dwSize) == ERROR_SUCCESS) {
//                     installed_programs.push_back(szDisplayName);
//                 }
//                 RegCloseKey(hSubKey);
//             }
//         }
//     }

//     RegCloseKey(hKey);

//     for (auto const& program : installed_programs) {
//         std::cout << program << std::endl;
//     }

//     return 0;
// }

// #include <windows.h>
// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>

// // Hàm kiểm tra xem một chuỗi có kết thúc bằng chuỗi khác không
// bool endsWith(const std::string &str, const std::string &suffix) {
//     return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
// }

// int main() {
//     // Lấy danh sách các ứng dụng được cài đặt trên máy tính
//     std::vector<std::string> apps;
//     HKEY hKey;
//     if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
//         char szDisplayName[1024], szUninstallString[1024];
//         DWORD dwIndex = 0, dwType, dwSize = sizeof(szDisplayName);
//         while (RegEnumKeyEx(hKey, dwIndex++, szDisplayName, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
//             HKEY hSubKey;
//             if (RegOpenKeyEx(hKey, szDisplayName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
//                 dwSize = sizeof(szDisplayName);
//                 if (RegQueryValueEx(hSubKey, "DisplayName", NULL, &dwType, (LPBYTE)szDisplayName, &dwSize) == ERROR_SUCCESS && dwType == REG_SZ) {
//                     if (endsWith(szDisplayName, "_is1")) {
//                         // Remove the suffix "_is1" if it exists
//                         szDisplayName[dwSize - 5] = '\0';
//                     }
//                     apps.push_back(szDisplayName);
//                 }
//                 RegCloseKey(hSubKey);
//             }
//             dwSize = sizeof(szDisplayName);
//         }
//         RegCloseKey(hKey);
//     }

//     // Sắp xếp và in ra danh sách các ứng dụng
//     std::sort(apps.begin(), apps.end());
//     for (const auto &app : apps) {
//         std::cout << app << std::endl;
//     }

//     return 0;
// }

// #include <windows.h>
// #include <iostream>
// #include <string>
// #include <vector>

// void EnumInstalledApps(std::vector<std::string>& apps)
// {
//     // Mở khóa cơ sở dữ liệu cài đặt ứng dụng
//     HKEY hKey;
//     if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
//         std::cout << "Khong the mo key." << std::endl;
//         return;
//     }

//     // Lấy số lượng phần tử con trong khóa
//     DWORD numSubKeys;
//     if (RegQueryInfoKey(hKey, NULL, NULL, NULL, &numSubKeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) {
//         std::cout << "Khong the lay thong tin key." << std::endl;
//         RegCloseKey(hKey);
//         return;
//     }

//     // Liệt kê tất cả các phần tử con và lấy thông tin tên ứng dụng
//     for (DWORD i = 0; i < numSubKeys; i++) {
//         char szSubKey[MAX_PATH];
//         DWORD dwSubKeyLen = sizeof(szSubKey);
//         if (RegEnumKeyEx(hKey, i, szSubKey, &dwSubKeyLen, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
//             HKEY hSubKey;
//             if (RegOpenKeyEx(hKey, szSubKey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
//                 char szDisplayName[MAX_PATH];
//                 DWORD dwSize = sizeof(szDisplayName);
//                 if (RegQueryValueEx(hSubKey, "DisplayName", NULL, NULL, (LPBYTE)szDisplayName, &dwSize) == ERROR_SUCCESS) {
//                     std::string app_name = szDisplayName;
//                     apps.push_back(app_name);
//                 }
//                 RegCloseKey(hSubKey);
//             }
//         }
//     }

//     RegCloseKey(hKey);
// }

// int main()
// {
//     std::vector<std::string> apps;
//     EnumInstalledApps(apps);

//     // In tên tất cả các ứng dụng đã cài đặt
//     for (const auto& app : apps) {
//         std::cout << app << std::endl;
//     }

//     return 0;
// }

// #include <windows.h>
// #include <psapi.h>
// #include <iostream>
// #include <string>
// #include <vector>

// using namespace std;

// vector<string> GetInstalledApps() {
//     vector<string> apps;

//     // Lấy ID của các tiến trình đang chạy
//     DWORD processIds[1024], bytesReturned;
//     if (!EnumProcesses(processIds, sizeof(processIds), &bytesReturned)) {
//         cerr << "Lỗi khi lấy danh sách tiến trình!" << endl;
//         return apps;
//     }

//     // Tính số lượng tiến trình và cấp phát bộ nhớ cho mảng các module
//     int count = bytesReturned / sizeof(DWORD);
//     HMODULE modules[1024];

//     for (int i = 0; i < count; i++) {
//         // Mở tiến trình
//         HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processIds[i]);
//         if (process) {
//             // Lấy đường dẫn của tiến trình
//             TCHAR processName[MAX_PATH] = TEXT("<unknown>");
//             HMODULE module = NULL;
//             DWORD cbNeeded = 0;
//             if (EnumProcessModules(process, &module, sizeof(module), &cbNeeded)) {
//                 GetModuleFileNameEx(process, module, processName, sizeof(processName) / sizeof(TCHAR));
//             }

//             // Thêm đường dẫn của tiến trình vào danh sách các ứng dụng cài đặt
//             string app = string(processName);
//             if (app.length() > 4 && app.substr(app.length() - 4) == ".exe") {
//                 apps.push_back(app);
//             }

//             // Đóng tiến trình
//             CloseHandle(process);
//         }
//     }

//     return apps;
// }

// int main() {
//     vector<string> apps = GetInstalledApps();
//     for (int i = 0; i < apps.size(); i++) {
//         cout << apps[i] << endl;
//     }
//     return 0;
// }

// #include <Windows.h>
// #include <iostream>

// int main()
// {
//     HKEY hKey;
//     if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
//         DWORD index = 0;
//         WCHAR szSubKeyName[MAX_PATH];
//         DWORD cchSubKeyName = ARRAYSIZE(szSubKeyName);
//         while (RegEnumKeyExW(hKey, index, szSubKeyName, &cchSubKeyName, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
//             HKEY hSubKey;
//             if (RegOpenKeyExW(hKey, szSubKeyName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
//                 WCHAR szDisplayName[MAX_PATH];
//                 DWORD cbDisplayName = sizeof(szDisplayName);
//                 DWORD dwType;
//                 if (RegQueryValueExW(hSubKey, L"DisplayName", NULL, &dwType, (LPBYTE)szDisplayName, &cbDisplayName) == ERROR_SUCCESS && dwType == REG_SZ) {
//                     std::wcout << szDisplayName << std::endl;
//                 }
//                 RegCloseKey(hSubKey);
//             }
//             index++;
//             cchSubKeyName = ARRAYSIZE(szSubKeyName);
//         }
//         RegCloseKey(hKey);
//     }

//     return 0;
// }

// #include <windows.h>
// #include <iostream>

// int main() {
//     HKEY hKey;
//     LSTATUS result;

//     // Mở registry key
//     result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall", 0, KEY_READ, &hKey);
//     if (result != ERROR_SUCCESS) {
//         std::cout << "Không thể mở registry key." << std::endl;
//         return 1;
//     }

//     // Lấy số lượng subkey
//     DWORD subkeyCount;
//     result = RegQueryInfoKey(hKey, NULL, NULL, NULL, &subkeyCount, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
//     if (result != ERROR_SUCCESS) {
//         std::cout << "Không thể truy vấn thông tin registry key." << std::endl;
//         return 1;
//     }

//     // Liệt kê các subkey và in ra tên ứng dụng
//     for (DWORD i = 0; i < subkeyCount; i++) {
//         char subkeyName[256];
//         DWORD subkeyNameLength = 256;
//         result = RegEnumKeyEx(hKey, i, subkeyName, &subkeyNameLength, NULL, NULL, NULL, NULL);
//         if (result != ERROR_SUCCESS) {
//             std::cout << "Not have subkey." << std::endl;
//             return 1;
//         }

//         HKEY appKey;
//         result = RegOpenKeyEx(hKey, subkeyName, 0, KEY_READ, &appKey);
//         if (result != ERROR_SUCCESS) {
//             continue;
//         }

//         // Lấy đường dẫn của file thực thi từ giá trị DisplayIcon
//         DWORD displayIconSize;
//         char displayIcon[256];
//         displayIconSize = 256;
//         result = RegQueryValueEx(appKey, "DisplayIcon", NULL, NULL, (LPBYTE)displayIcon, &displayIconSize);
//         if (result != ERROR_SUCCESS) {
//             // std::cout << "Not have exe." << std::endl;
//             // continue;
//         }

//         // Tách đường dẫn file thực thi từ giá trị DisplayIcon
//         std::string exePath;
//         size_t exeIndex = std::string(displayIcon).find(".exe");
//         if (exeIndex != std::string::npos) {
//             exePath = std::string(displayIcon).substr(0, exeIndex + 4);
//         }
//         // if(exePath == "")
//         //     continue;
//         std::cout << "Executable Path: " << exePath << std::endl;

//         // Lấy tên
//         DWORD valueSize;
//         char displayName[256];
//         valueSize = 256;
//         result = RegQueryValueEx(appKey, "DisplayName", NULL, NULL, (LPBYTE)displayName, &valueSize);
//         if (result != ERROR_SUCCESS) {
//             std::cout << "Not have name." << std::endl;
//             continue;
//         }

//         std::cout << displayName << std::endl;
        

//         // Lấy lệnh để gỡ cài đặt ứng dụng
//         DWORD uninstallStringSize;
//         char uninstallString[256];
//         uninstallStringSize = 256;
//         result = RegQueryValueEx(appKey, "UninstallString", NULL, NULL, (LPBYTE)uninstallString, &uninstallStringSize);
//         if (result != ERROR_SUCCESS) {
//             std::cout << "Not have uninstall exe." << std::endl;
//             continue;
//         }
//         std::cout << "Uninstall String: " << uninstallString << std::endl;

//         // Lấy đường dẫn cài đặt của ứng dụng
//         DWORD installLocationSize;
//         char installLocation[256];
//         installLocationSize = 256;
//         result = RegQueryValueEx(appKey, "InstallLocation", NULL, NULL, (LPBYTE)installLocation, &installLocationSize);
//         if (result != ERROR_SUCCESS) {
//             std::cout << "Not have path." << std::endl;
//             continue;
//         }
//         std::cout << "Install Location: " << installLocation << std::endl;
//         RegCloseKey(appKey);

//     }

//     // Đóng registry key
//     RegCloseKey(hKey);

//     return 0;
// }

// #include <windows.h>
// #include <initguid.h>
// #include <KnownFolders.h>
// // #include <ShObjIdl_core.h>
// #include <shlobj_core.h>
// #include <ShlObj.h>
// #include <wchar.h>

// using namespace std;

// int main()
// {
    // PWSTR path = NULL;

    // // HRESULT hr = SHGetKnownFolderPath(FOLDERID_AppsFolder, 0, NULL, &path);

    // // if (SUCCEEDED(hr)) {
    // //     wprintf(L"%ls\n", path);
    // // }

    // // CoTaskMemFree(path);

    // return 0;
    //  GUID appsFolderId = FOLDERID_AppsFolder;
    //  wchar_t* appsFolderIdString = NULL;
    //  StringFromIID(appsFolderId, &appsFolderIdString);
    //  std::wcout << "FOLDERID_AppsFolder: " << appsFolderIdString << std::endl;
    //  CoTaskMemFree(appsFolderIdString);

//    IShellItem *psiFolder = nullptr;
//    IEnumIDList *pEnum = nullptr;
//    LPITEMIDLIST pidl = nullptr;
//    HRESULT hr = SHGetKnownFolderItem(FOLDERID_AppsFolder, 0, nullptr, IID_PPV_ARGS(&psiFolder));

    // if (SUCCEEDED(hr))
    // {
    //     hr = psiFolder->BindToHandler(nullptr, BHID_EnumItems, IID_PPV_ARGS(&pEnum));
    // }

    // if (SUCCEEDED(hr))
    // {
    //     while (S_OK == pEnum->Next(1, &pidl, nullptr))
    //     {
    //         LPWSTR pszName = nullptr;
    //         SHGetNameFromIDList(pidl, SIGDN_NORMALDISPLAY, &pszName);
    //         std::wcout << pszName << std::endl;
    //         CoTaskMemFree(pszName);
    //         ILFree(pidl);
    //     }
    //     pEnum->Release();
    // }

    // psiFolder->Release();

    // return 0;
// }

// #include <Windows.h>
// #include <stdio.h>
// #include <iostream>

// bool IsInstalled(const wchar_t* path)
// {
//     wchar_t buffer[MAX_PATH];
//     if (GetFullPathNameW(path, MAX_PATH, buffer, nullptr) == 0) {
//         return false;
//     }

//     DWORD attrib = GetFileAttributesW(buffer);
//     if (attrib == INVALID_FILE_ATTRIBUTES) {
//         return false;
//     }

//     return (attrib & FILE_ATTRIBUTE_DIRECTORY) == 0;
// }

// int main()
// {
//     // if (argc < 2) {
//     //     printf("Usage: %s <file_path>\n", argv[0]);
//     //     return 1;
//     // }

//     const wchar_t* path = reinterpret_cast<const wchar_t*>("C:\\Users\\nhatn\\AppData\\Roaming\\Zoom\bin\\Zoom.exe");
//     bool installed = IsInstalled(path);
//     std::cout<<path;
//     if (installed) {
//         printf("%S is an installed application.\n", path);
//     } else {
//         printf("%S is not an installed application.\n", path);
//     }

//     return 0;
// }

// oke
// #include <iostream>
// #include <windows.h>
// #include <tchar.h>
// #include <string>

// using namespace std;

// string getFileDescription(string filePath) {
//     DWORD dwSize = 0;
//     BYTE* pVersionInfo = NULL;
//     string fileDescription = "";
//     if ((dwSize = GetFileVersionInfoSize(filePath.c_str(), NULL)) != 0) {
//         pVersionInfo = new BYTE[dwSize];
//         if (GetFileVersionInfo(filePath.c_str(), 0, dwSize, pVersionInfo)) {
//             LPVOID lpBuffer = NULL;
//             UINT uLen = 0;
//             if (VerQueryValue(pVersionInfo, _T("\\StringFileInfo\\040904B0\\FileDescription"), &lpBuffer, &uLen)) {
//                 fileDescription = (const char*)lpBuffer;
//             }
//         }
//         delete[] pVersionInfo;
//     }
//     return fileDescription;
// }

// int main() {
//     string filePath = "C:\\Windows\\System32\\notepad.exe";
//     string fileDescription = getFileDescription(filePath);
//     cout << "File Description: " << fileDescription << endl;
//     return 0;
// }
// #include <iostream>
// #include <string>
// #include <windows.h>

// using namespace std;

// void listFiles(string folderPath) {
//     WIN32_FIND_DATAA findData;
//     HANDLE hFind = FindFirstFileA((folderPath + "\\*").c_str(), &findData);
//     if (hFind != INVALID_HANDLE_VALUE) {
//         int cnt = 0;
//         do {
//             if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
//                 if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0) {
//                     // Nếu tìm thấy một thư mục con, tiếp tục tìm kiếm trong thư mục con
//                     string subFolderPath = folderPath + "\\" + findData.cFileName;
//                     listFiles(subFolderPath);
//                 }
//             } else {
//                 // Nếu tìm thấy một tệp tin .exe, in ra đường dẫn đầy đủ của nó
//                 string fileName = findData.cFileName;
//                 if (fileName.size() > 4 && fileName.substr(fileName.size() - 4) == ".exe") {
//                     cout << folderPath + "\\" + fileName << endl;
//                 }
//             }
//             cnt ++;
//         } while (FindNextFileA(hFind, &findData) && cnt < 3);
//         FindClose(hFind);
//     }
// }

// int main() {
//     string folderPath = "C:\\Program Files";
//     listFiles(folderPath);
//     return 0;
// }

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <windows.h>
#include <tchar.h>
#include <string>

using namespace std;

std::string getFileDescription(const char* fileName)
{
    DWORD   verHandle = 0;
    UINT    size = 0;
    LPBYTE  lpBuffer = NULL;
    std::string result;

    // Lấy kích thước thông tin phiên bản của tệp thực thi
    size = GetFileVersionInfoSizeA(fileName, &verHandle);
    if (size > 0)
    {
        // Cấp phát bộ nhớ cho thông tin phiên bản
        lpBuffer = new BYTE[size];
        if (GetFileVersionInfoA(fileName, verHandle, size, lpBuffer))
        {
            // Lấy trỏ đến thông tin File Description
            LPSTR lpDescription = NULL;
            UINT len = 0;
            VerQueryValueA(lpBuffer, "\\StringFileInfo\\FF6F7200\\FileDescription", (LPVOID*)&lpDescription, &len);
            // std::cout<<size;
            if (lpDescription != NULL)
            {
                result = lpDescription;
            }
        }
        delete[] lpBuffer;
    }
    return result;
}
int main() {
    string folderPath = "C:\\Program Files";
    string command = "dir /b /s \"" + folderPath + "\"\\*.exe";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Could not execute command." << std::endl;
        return EXIT_FAILURE;
    }
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        string filePath = buffer;
        // const char * filePath = "C:\\Program Files\\UniKeyNT.exe";
        // string fileDescription = getFileDescription(filePath);
        // if(fileDescription.empty())
        //     continue;
        // cout << "File Description: " << fileDescription << endl;
        std::cout << filePath;
    }
    pclose(pipe);
    return EXIT_SUCCESS;
}

// #include <Windows.h>
// #include <iostream>
// std::string getFileDescription(const char* fileName)
// {
//     DWORD   verHandle = 0;
//     UINT    size = 0;
//     LPBYTE  lpBuffer = NULL;
//     std::string result;

//     // Lấy kích thước thông tin phiên bản của tệp thực thi
//     size = GetFileVersionInfoSizeA(fileName, &verHandle);
//     if (size > 0)
//     {
//         // Cấp phát bộ nhớ cho thông tin phiên bản
//         lpBuffer = new BYTE[size];
//         if (GetFileVersionInfoA(fileName, verHandle, size, lpBuffer))
//         {
//             // Lấy trỏ đến thông tin File Description
//             LPSTR lpDescription = NULL;
//             UINT len = 0;
//             VerQueryValueA(lpBuffer, "\\StringFileInfo\\040904B0\\FileDescription", (LPVOID*)&lpDescription, &len);
//             // std::cout<<size;
//             if (lpDescription != NULL)
//             {
//                 result = lpDescription;
//             }
//         }
//         delete[] lpBuffer;
//     }
//     return result;
// }
// int main()
// {
//     std::string fileName = "C:\\Program Files\\WinRAR\\WinRAR.exe";
//     std::string fileDescription = getFileDescription(fileName.c_str());

//     if (!fileDescription.empty())
//     {
//         std::cout << "File Description: " << fileDescription << std::endl;
//     }
//     else
//     {
//         std::cout << "Failed to get file description." << std::endl;
//     }


//     return 0;
// }