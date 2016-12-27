#include <mado/application.hpp>
#include <mado/form_builder.hpp>

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
    //auto const result = mado::form_builder{}.title(_T("hoge")).build();
    //std::visit(main_form{}, result);
    auto const form = std::get<std::shared_ptr<mado::form>>(mado::make_form());
    mado::application<mado::blocking>::run(form);
    return 0;
}
