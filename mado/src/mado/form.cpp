#include <mado/form.hpp>

#include <mado/utility/random_generator.hpp>

namespace mado
{
    form::form()
        : window{nullptr}
    {
        auto const class_name = generate_random_string(32);
        UINT class_style{};
        for (auto const& cs : class_styles_) {
            class_style |= cs;
        }
        DWORD window_style{};
        for (auto const& ws : window_styles_) {
            window_style |= ws;
        }
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
        wc.lpszClassName = class_name.data();
        wc.hIconSm = static_cast<HICON>(LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));

        CREATESTRUCT cs;
        cs.dwExStyle = WS_EX_OVERLAPPEDWINDOW;
        cs.lpszClass = class_name.data();
        cs.lpszName = title_.data();
        cs.style = WS_OVERLAPPEDWINDOW;
        cs.x = position_.first;
        cs.y = position_.second;
        cs.cx = size_.first;
        cs.cy = size_.second;
        cs.hwndParent = parent_;
        cs.hMenu = nullptr;
        cs.hInstance = ::GetModuleHandle(nullptr);
        cs.lpCreateParams = nullptr;

        initialize(wc, cs);

    }

    form::form(HWND hwnd)
        : window{hwnd}
    {
    }

    form::form(WNDCLASSEX const& wc, CREATESTRUCT const& cs)
        : window{nullptr}
    {
        initialize(wc, cs);
    }

    void form::initialize(WNDCLASSEX const& wc, CREATESTRUCT const& cs)
    {
        if (!::RegisterClassEx(&wc)) {
            throw make_error_code();
        }
        hwnd_ = ::CreateWindowEx(
            cs.dwExStyle,
            cs.lpszClass,
            cs.lpszName,
            cs.style,
            cs.x,
            cs.y,
            cs.cx,
            cs.cy,
            cs.hwndParent,
            cs.hMenu,
            cs.hInstance,
            cs.lpCreateParams
        );
        if (!hwnd_) {
            throw make_error_code();
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
