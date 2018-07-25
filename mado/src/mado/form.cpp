#include <mado/detail/make_error_code.hpp>
#include <mado/form.hpp>
#include <mado/utility/random_generator.hpp>

#include <functional>
#include <utility>

namespace mado {
    namespace {
        template <typename StyleSetter, typename Op>
        void toggle_window_style(form const& form, LONG style, StyleSetter&& setter, Op&& op) {
            if (!form.is_created()) {
                setter(style);
                return;
            }
            auto const current_style = ::GetWindowLongPtr(form.hwnd(), GWL_STYLE);
            if (current_style == 0UL) {
                throw std::system_error{make_error_code()};
            }
            ::SetLastError(0UL);
            ::SetWindowLongPtr(form.hwnd(), GWL_STYLE, op(current_style, style));
            if (::GetLastError() != 0UL) {
                throw std::system_error{make_error_code()};
            }
        }

        template <typename StyleSetter>
        void enable_window_style(form const& form, LONG style, StyleSetter&& setter) {
            toggle_window_style(form, style, std::forward<StyleSetter>(setter), std::bit_or<>{});
        }

        template <typename StyleSetter>
        void disable_window_style(form const& form, LONG style, StyleSetter&& setter) {
            toggle_window_style(form, style, std::forward<StyleSetter>(setter), std::bit_and<>{});
        }

        bool is_enabled_window_style(form const& form, DWORD window_style, LONG style) {
            if (!form.is_created()) {
                return window_style & style;
            }
            auto const current_style = ::GetWindowLongPtr(form.hwnd(), GWL_STYLE);
            if (current_style == 0UL) {
                throw std::system_error{make_error_code()};
            }
            return current_style & style;
        }
    }

    form::form() : window{generate_random_string(32U)} {
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

    form::form(WNDCLASSEX const& wc, window_property const& property) : window{wc.lpszClassName, property}, wc_{wc} {}

    void form::enable_window_style(LONG style) {
        mado::enable_window_style(*this, style, [this](LONG style) { property_.window_style |= style; });
    }

    void form::disable_window_style(LONG style) {
        mado::disable_window_style(*this, ~style, [this](LONG style) { property_.window_style &= style; });
    }

    bool form::is_enabled_window_style(LONG style) const {
        return mado::is_enabled_window_style(*this, property_.window_style, style);
    }

    void form::create() {
        if (is_created()) {
            return;
        }
        if (!::RegisterClassEx(&wc_)) {
            throw std::system_error{make_error_code()};
        }
        property_.create_params = this;
        hwnd_ = property_.create();
        if (rejected_creation_) {
            return;
        }
    }

    void form::enable_maximizebox() {
        enable_window_style(WS_MAXIMIZEBOX);
    }

    void form::disable_maximizebox() {
        disable_window_style(WS_MAXIMIZEBOX);
    }

    bool form::is_enabled_maximizebox() const {
        return is_enabled_window_style(WS_MAXIMIZEBOX);
    }

    void form::enable_minimizebox() {
        enable_window_style(WS_MINIMIZEBOX);
    }

    void form::disable_minimizebox() {
        disable_window_style(WS_MINIMIZEBOX);
    }

    bool form::is_enabled_minimizebox() const {
        return is_enabled_window_style(WS_MINIMIZEBOX);
    }

    void form::enable_close_button() {
        if (!created_) {
            return;
        }
        auto const menu = ::GetSystemMenu(hwnd_, false);
        ::EnableMenuItem(menu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
    }

    void form::disable_close_button() {
        if (!created_) {
            return;
        }
        auto const menu = ::GetSystemMenu(hwnd_, false);
        ::EnableMenuItem(menu, SC_CLOSE, MF_BYCOMMAND | MF_DISABLED);
    }

    bool form::is_enabled_close_button() const {
        if (!created_) {
            return false;
        }
        auto const menu = ::GetSystemMenu(hwnd_, false);
        MENUITEMINFO info{};
        info.cbSize = sizeof(info);
        info.fMask = MIIM_STATE;
        if (!::GetMenuItemInfo(menu, SC_CLOSE, MF_BYCOMMAND, &info)) {
            throw std::system_error{make_error_code()};
        }
        return info.fState == MF_ENABLED;
    }
}
