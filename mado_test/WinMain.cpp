#include <Windows.h>

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    MessageBox(nullptr, L"hoge", L"hoge", MB_OK);
    return 0;
}
