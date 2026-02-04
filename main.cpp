#include <windows.h>
#include <string>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmd, int show) {
    HRSRC hRes = FindResourceW(hInst, MAKEINTRESOURCEW(101), (LPCWSTR)RT_RCDATA);
    if (!hRes) return 1;

    HGLOBAL hData = LoadResource(hInst, hRes);
    DWORD size = SizeofResource(hInst, hRes);
    const char* data = (const char*)LockResource(hData);
    if (!data) return 1;

    std::string content(data, size);
    int len = MultiByteToWideChar(CP_UTF8, 0, content.c_str(), -1, NULL, 0);
    std::wstring wContent(len, 0);
    MultiByteToWideChar(CP_UTF8, 0, content.c_str(), -1, &wContent[0], len);

    std::wstring edgePath = L"\"C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe\"";
    std::wstring fullCmd = edgePath + L" --app=\"" + wContent + L"\" --no-first-run";

    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (CreateProcessW(NULL, (LPWSTR)fullCmd.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }

    return 0;
}