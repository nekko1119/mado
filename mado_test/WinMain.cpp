#include <mado/application.hpp>
#include <mado/form_builder.hpp>

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    auto result = mado::form_builder{}.title(_T("hoge")).build();
    if (auto form = std::get_if<std::shared_ptr<mado::form>>(&result)) {
        form->get()->show();
        mado::application<mado::blocking>::run(*form);
    } else {
        auto message = std::get<std::error_code>(result).message();
    }
    return 0;
}
