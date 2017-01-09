#include <mado/application.hpp>
#include <mado/form_builder.hpp>

struct main_form
{
    void operator()(std::shared_ptr<mado::form> form) const
    {
        try {
            form->add_create_handler([](std::shared_ptr<mado::form>) {
                MessageBox(nullptr, _T("hoge"), _T("hoge"), MB_OK);
                return true;
            });
            form->add_close_handler([](std::shared_ptr<mado::form>) {
                return MessageBox(nullptr, _T("hoge"), _T("hoge"), MB_OKCANCEL) == IDOK;
            });
            form->title(_T("hoge"));
            form->show();
            form->create();
            form->title(_T("foo"));
            mado::application<mado::blocking>::run(form);
        } catch (std::exception const& e) {
            auto message = e.what();
            (void)message;
        }
    }

    void operator()(std::error_code code) const
    {
        auto message = code.message();
    }
};

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    //auto const form = mado::form_builder{}.title(_T("hoge")).build();
    auto const form = mado::make_form();
    std::visit(main_form{}, form);
    return 0;
}
