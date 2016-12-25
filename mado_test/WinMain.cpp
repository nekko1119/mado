#include <Windows.h>
#include <mado/utility/random_generator.hpp>

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    MessageBox(nullptr, mado::generate_random_string(20).c_str(), L"hoge", MB_OK);
    return 0;
}
