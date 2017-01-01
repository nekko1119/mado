#include <mado/form.hpp>

#include <mado/utility/random_generator.hpp>
#include <functional>
#include <numeric>

namespace mado
{
    form::form()
        : window{generate_random_string(32U)}
    {
        wc_.cbSize = sizeof(wc_);
        wc_.style = CS_HREDRAW | CS_VREDRAW;
        wc_.lpfnWndProc = window::window_procedure;
        wc_.cbClsExtra = 0;
        wc_.cbWndExtra = 0;
        wc_.hInstance = ::GetModuleHandle(nullptr);
        wc_.hIcon = static_cast<HICON>(::LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        wc_.hCursor = static_cast<HCURSOR>(::LoadImage(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        wc_.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
        wc_.lpszMenuName = nullptr;
        wc_.lpszClassName = class_name_.c_str();
        wc_.hIconSm = static_cast<HICON>(LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
    }

    form::form(WNDCLASSEX const& wc, window_property const& property)
        : window{wc.lpszClassName, property}, wc_{wc}
    {
    }

    void form::create()
    {
        if (!::RegisterClassEx(&wc_)) {
            throw std::system_error{make_error_code()};
        }

        property_.create_params = this;
        hwnd_ = property_.create();
        if (rejected_create) {
            return;
        }
        if (!hwnd_) {
            throw std::system_error{make_error_code()};
        }
    }

    void form::show()
    {
        ::ShowWindow(hwnd_, SW_SHOW);
    }

    void form::hide()
    {
        ::ShowWindow(hwnd_, SW_HIDE);
    }
}
