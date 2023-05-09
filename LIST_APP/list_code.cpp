#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>

#pragma comment(lib, "advapi32.lib")

using namespace std;

void printMenu()
{
    cout << "+----------------------------------------+\n";
    cout << "| Ban muon bat dau hay ket thuc mot app? |\n";
    cout << "+----------------------------------------+\n";
    cout << "| 1. Bat dau chay app                    |\n";
    cout << "| 2. Ket thuc app                        |\n";
    cout << "+----------------------------------------+\n";
}
vector<string> listAllAppDemo()
{
    std::vector<std::string> installed_programs;

    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths", 0, KEY_READ | KEY_WOW64_32KEY, &hKey) != ERROR_SUCCESS) {
        std::cerr << "Failed to open registry key" << std::endl;
        return installed_programs;
    }

    char szDisplayName[1024];
    char szKeyName[1024];
    DWORD dwSize = sizeof(szDisplayName);

    for (DWORD i = 0, retValue = ERROR_SUCCESS; retValue == ERROR_SUCCESS; ++i) {
        retValue = RegEnumKeyEx(hKey, i, szKeyName, &dwSize, NULL, NULL, NULL, NULL);
        dwSize = sizeof(szKeyName);

        if (retValue == ERROR_SUCCESS) {
            HKEY hSubKey;
            if (RegOpenKeyEx(hKey, szKeyName, 0, KEY_READ | KEY_WOW64_32KEY, &hSubKey) == ERROR_SUCCESS) {
                dwSize = sizeof(szDisplayName);
                if (RegQueryValueEx(hSubKey, NULL, NULL, NULL, (LPBYTE)szDisplayName, &dwSize) == ERROR_SUCCESS) {
                    installed_programs.push_back(szDisplayName);
                }
                RegCloseKey(hSubKey);
            }
        }
    }

    RegCloseKey(hKey);

    installed_programs.erase(unique(installed_programs.begin(), installed_programs.end()), installed_programs.end());
    
    int cnt = 0;
    for (;cnt < installed_programs.size();)
    {
        installed_programs[cnt].erase(remove(installed_programs[cnt].begin(), installed_programs[cnt].end(), '\"'), installed_programs[cnt].end());
        string program = installed_programs[cnt];
        std::cout << ++cnt << ". " << program << std::endl;
    }

    return installed_programs;
}
void listAllAppMore(vector<string> & pathApps)
{
    vector<string> moreApps;
    moreApps.push_back("Het");

    int nextIdx = pathApps.size();
    for (auto const& app : moreApps) {
        std::cout << ++nextIdx << ". " << app << std::endl;
    }
    pathApps.insert(pathApps.end(), moreApps.begin(), moreApps.end());
}
bool isPositiveInteger(const string& s)
{
    if (s.empty() || (!isdigit(s[0])))
        return false;
    for (char c : s) {
        if (!isdigit(c))
            return false;
    }
    if (s.size() > 1 && s[0] == '0')
        return false;
    return true;
}
string findChoice(string choice, vector<string> pathApps)
{
    string pathApp = choice;
    if (isPositiveInteger(choice))
    {
        int idx = stoi(choice);
        if (idx > pathApps.size())
            return "ERROR";

        pathApp = pathApps[idx - 1];
    }

    return pathApp;
}
string escapePath(string path) {
    string escapedPath;
    for (char c : path) {
        if (c == '\\' || c == '\"') {
            escapedPath += '\\';
        }
        escapedPath += c;
    }
    return escapedPath;
}
void processRunApp()
{
    vector<string> appsDemo = listAllAppDemo();

    cout << endl;
    cout << "Ban co muon xem them? (nhap 'y' de tiep tuc): ";
    char continue_choice;
    cin >> continue_choice;
    if (continue_choice == 'y')
    {
        listAllAppMore(appsDemo);
        cout << endl;
    }

    fflush(stdin);
    cout << "App ban muon chay (nhap <so thu tu> hoac <dia chi>): ";
    string choice;
    cin >> choice;

    string path = findChoice(choice, appsDemo);
    if (path == "ERROR")
        cout << "Nhap khong hop le!\n";
    cout << "Chay app: " << path << endl;
    string command = "cmd /c \"" + escapePath(path) + "\"";
    system(command.c_str());
}
void solve()
{
    char continue_choice;
    do {
        printMenu();

        cout << endl;
        int opt;
        cout << "Thao tac ban chon (1, 2): ";
        cin >> opt;
        cout << endl;

        if (opt == 1) {
            // Xử lý thao tác 1
            cout << "Ban da chon thao tac 1" << endl;
            cout << endl;

            processRunApp();
            cout << endl;
        } 
        else {
            // Xử lý thao tác 2
            cout << "Ban da chon thao tac 2" << endl;
            
            // processCloseApp();
            cout << endl;
        }

        cout << "Ban co muon tiep tuc thao tac voi App? (nhap 'y' de tiep tuc): ";
        cin >> continue_choice;
    } while (continue_choice == 'y');
}
int main()
{
    solve();
}

// run: g++ list_code.cpp -o list_code.exe & list_code.exe