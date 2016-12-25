#include <mado/window_builder.hpp>
#include <Windows.h>
#include <codecvt>

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    mado::window_builder builder;
    auto result = builder.build();
    if (auto const hwnd = std::get_if<HWND>(&result)) {
        ShowWindow(*hwnd, SW_SHOW);
    } else {
        auto const message = std::get<0>(result).message();
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> conversion;
        MessageBox(nullptr, conversion.from_bytes(message).data(), _T("hoge"), MB_OK);
    }
    MessageBox(nullptr, _T("hoge"), _T("hoge"), MB_OK);
    return 0;
}
