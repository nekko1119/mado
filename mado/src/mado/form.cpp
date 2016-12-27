#include <mado/form.hpp>

#include <mado/utility/random_generator.hpp>
#include <functional>
#include <numeric>

namespace mado
{
    form::form()
    {
        auto const class_name = generate_random_string(32U);
        WNDCLASSEX wc;
        wc.cbSize = sizeof(wc);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = global_window_procedure;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = ::GetModuleHandle(nullptr);
        wc.hIcon = static_cast<HICON>(::LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        wc.hCursor = static_cast<HCURSOR>(::LoadImage(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = class_name.c_str();
        wc.hIconSm = static_cast<HICON>(LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));

        initialize(wc);
    }

    form::form(WNDCLASSEX const& wc, window_property const& property)
        : window{property}
    {
        initialize(wc);
    }

    void form::initialize(WNDCLASSEX const& wc)
    {
        if (!::RegisterClassEx(&wc)) {
            throw std::system_error{make_error_code()};
        }

        property_.class_name = wc.lpszClassName;
        hwnd_ = property_.create();
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
