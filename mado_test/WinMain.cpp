#include <mado/application.hpp>
#include <mado/form.hpp>

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    auto form = mado::make<mado::form>();
    try {
        form->set_should_create_handler([](mado::form&) {
            MessageBox(nullptr, _T("hoge"), _T("hoge"), MB_OK);
            ::OutputDebugString(_T("should create"));
            return true;
        });
        form->set_should_close_handler([](mado::form&) {
            return MessageBox(nullptr, _T("hoge"), _T("hoge"), MB_OKCANCEL) == IDOK;
        });
        form->disable_minimizebox();
        form->disable_maximizebox();
        form->enable_minimizebox();
        form->title(_T("foo"));
        mado::application<mado::blocking>::run(std::move(form));
    } catch (std::system_error const& e) {
        auto const code = e.code();
        ::OutputDebugStringA(code.message().c_str());
        MessageBox(nullptr, _T("失敗した"), _T("あちゃー"), MB_OK);
    }
}
