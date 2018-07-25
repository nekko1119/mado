#include <mado/button.hpp>

#include <mado/detail/make_error_code.hpp>

#include <tchar.h>

namespace mado
{
    button::button(HWND parent, tstring_view title)
        : window{_T("BUTTON"), {}}
    {
        property_.title = title;
        property_.parent = parent;
        property_.window_style = WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE;
        property_.window_style_ex = WS_EX_LEFT;
        property_.size = {120, 24};
        property_.position = {8, 8};
    }

    void button::create()
    {
        if (is_created()) {
            return;
        }
        property_.create_params = this;
        hwnd_ = property_.create();
        window_procedure_ = reinterpret_cast<window::procedure_type>(::GetWindowLongPtr(hwnd_, GWL_WNDPROC));
        if (!window_procedure_) {
            throw std::system_error{make_error_code()};
        }
        ::SetWindowLongPtr(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        ::SetWindowLongPtr(hwnd_, GWL_WNDPROC, reinterpret_cast<LONG_PTR>(&window::window_procedure));
        // test code
        ::SendMessage(hwnd_, WM_SETFONT, (LPARAM) ::GetStockObject(DEFAULT_GUI_FONT), true);
    }
}
