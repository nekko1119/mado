#include <mado/application.hpp>
#include <mado/button.hpp>
#include <mado/form.hpp>

#include <cstdio>

// test code
#pragma comment( \
    linker, \
    "/manifestdependency:\"type='win32' \
    name='Microsoft.Windows.Common-Controls' \
    version='6.0.0.0' \
    processorArchitecture='*' \
    publicKeyToken='6595b64144ccf1df' \
    language='*'\"")

struct fcloser {
    void operator()(std::FILE** fp) const {
        std::fclose(*fp);
    }
};

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) try {
    ::AllocConsole();
    FILE* fp = nullptr;
    std::unique_ptr<FILE*, fcloser> fpp{&fp};
    ::freopen_s(fpp.get(), "CONOUT$", "w", stdout);
    std::atexit([]() { ::FreeConsole(); });
    auto form = mado::make<mado::form>();
    form->on_create([](mado::form&) {
        MessageBox(nullptr, _T("hoge"), _T("hoge"), MB_OK);
        ::OutputDebugString(_T("should create"));
    });
    form->should_close([](mado::form&) { return MessageBox(nullptr, _T("hoge"), _T("hoge"), MB_OKCANCEL) == IDOK; });
    form->create();
    auto button = mado::make<mado::button>(form->hwnd(), _T("buttonやで"));
    button->on_create([](mado::button&) { MessageBox(nullptr, _T("bar"), _T("bar"), MB_OK); });
    button->create();
    button->on_click(
        [](mado::button&, std::pair<short, short>) { MessageBox(nullptr, _T("clicked"), _T("button"), MB_OK); });
    form->title(_T("foo"));
    form->show();
    mado::application<mado::blocking>::run(std::move(form));
} catch (std::system_error const& e) {
    auto const code = e.code();
    ::OutputDebugStringA(code.message().c_str());
    MessageBox(nullptr, _T("a system error occuered"), _T("oops"), MB_OK);
}
