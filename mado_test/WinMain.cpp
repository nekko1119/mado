#include <mado/application.hpp>
#include <mado/form.hpp>

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    auto const form = mado::make_form();
    try {
        form->add_create_handler([](std::shared_ptr<mado::form>) {
            MessageBox(nullptr, _T("hoge"), _T("hoge"), MB_OK);
            return true;
        });
        form->add_close_handler([](std::shared_ptr<mado::form>) {
            return MessageBox(nullptr, _T("hoge"), _T("hoge"), MB_OKCANCEL) == IDOK;
        });
        form->disable_minimizebox();
        form->create();
        form->title(_T("foo"));
        form->show();
        mado::application<mado::blocking>::run(form);
    } catch (std::system_error const& e) {
        auto code = e.code();
        (void) code;
        auto message = e.what();
        (void) message;
        MessageBox(nullptr, _T("失敗した"), _T("あちゃー"), MB_OK);
    }
}
