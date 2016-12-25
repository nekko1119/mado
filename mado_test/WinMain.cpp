#include <mado/application.hpp>
#include <mado/form.hpp>
#include <Windows.h>
#include <codecvt>

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    auto result = mado::make_form(mado::window_builder());
    if (auto form = std::get_if<std::shared_ptr<mado::form>>(&result)) {
        (*form)->visible();
        mado::application<mado::blocking>::run(*form);
    } else {
        auto message = std::get<std::error_code>(result).message();
    }
    return 0;
}
