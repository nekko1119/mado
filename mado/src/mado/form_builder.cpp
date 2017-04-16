#include <mado/form_builder.hpp>

#include <mado/detail/make_error_code.hpp>
#include <mado/utility/random_generator.hpp>
#include <functional>
#include <numeric>

namespace mado
{
    form_builder& form_builder::title(tstring_view title) noexcept
    {
        property_.title = std::move(title);
        return *this;
    }

    form_builder& form_builder::position(int x, int y) noexcept
    {
        property_.position = std::make_pair(x, y);
        return *this;
    }

    form_builder& form_builder::size(int x, int y) noexcept
    {
        property_.size = std::make_pair(x, y);
        return *this;
    }

    form_builder& form_builder::parent(HWND parent) noexcept
    {
        property_.parent = parent;
        return *this;
    }

    std::shared_ptr<form> form_builder::build() const
    {
        auto const class_name = generate_random_string(32U);
        WNDCLASSEX wc;
        wc.cbSize = sizeof(wc);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = window<form>::window_procedure;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = ::GetModuleHandle(nullptr);
        wc.hIcon = static_cast<HICON>(::LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        wc.hCursor = static_cast<HCURSOR>(::LoadImage(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = class_name.c_str();
        wc.hIconSm = static_cast<HICON>(LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        auto form = make_form(wc, property_);
        form->create();
        return form;
    }
}
