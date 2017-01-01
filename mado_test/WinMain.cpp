#include <mado/application.hpp>
#include <mado/form_builder.hpp>

struct main_form
{
    void operator()(std::shared_ptr<mado::form> form) const {
        form->add_create_handler([](std::shared_ptr<mado::form>) {
            MessageBox(nullptr, _T("hoge"), _T("hoge"), MB_OK);
            return true;
        });
        form->create();
        mado::application<mado::blocking>::run(form);
    }

    void operator()(std::error_code code) const {
        auto message = code.message();
    }
};

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    //auto const form = mado::form_builder{}.title(_T("hoge")).build();
    auto const form = mado::make_form();
    std::visit(main_form{}, form);
    return 0;
}
