#include <mado/application.hpp>
#include <mado/form_builder.hpp>

struct my_form : mado::form
{
    using form::form;
    void on_create(window&) override
    {
        MessageBox(nullptr, _T("oncreate"), _T(""), MB_OK);
    }
};

struct main_form
{
    void operator()(std::shared_ptr<mado::form> form) const {
        mado::application<mado::blocking>::run(form);
    }

    void operator()(std::error_code code) const {
        auto message = code.message();
    }
};

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    //auto const form = mado::form_builder{}.title(_T("hoge")).build();
    auto const form = mado::make_form<my_form>();
    std::visit(main_form{}, form);
    return 0;
}
