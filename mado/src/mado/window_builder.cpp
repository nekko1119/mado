#include <mado/window_builder.hpp>

#include <mado/detail/make_error_code.hpp>
#include <mado/utility/random_generator.hpp>

namespace mado
{
    window_builder& window_builder::add_class_styles(std::initializer_list<class_style> styles)
    {
        for (auto const& s : styles) {
            class_styles_.emplace(s);
        }
        return *this;
    }

    window_builder& window_builder::remove_class_styles(std::initializer_list<class_style> styles)
    {
        for (auto const& s : styles) {
            class_styles_.erase(s);
        }
        return *this;
    }

    window_builder& window_builder::procedure(WNDPROC procedure) noexcept
    {
        procedure_ = procedure;
        return *this;
    }

    window_builder& window_builder::title(tstring_view title) noexcept
    {
        title_ = std::move(title);
        return *this;
    }

    window_builder& window_builder::add_window_style(std::initializer_list<window_style> styles)
    {
        for (auto const& s : styles) {
            window_styles_.emplace(s);
        }
        return *this;
    }

    window_builder& window_builder::remove_window_style(std::initializer_list<window_style> styles)
    {
        for (auto const& s : styles) {
            window_styles_.erase(s);
        }
        return *this;
    }

    window_builder& window_builder::position(int x, int y) noexcept
    {
        position_ = std::make_pair(x, y);
        return *this;
    }

    window_builder& window_builder::size(int x, int y) noexcept
    {
        size_ = std::make_pair(x, y);
        return *this;
    }

    window_builder& window_builder::parent(HWND parent) noexcept
    {
        parent_ = parent;
        return *this;
    }

    std::variant<std::error_code, HWND> window_builder::build() const
    {
        WNDCLASSEX wc;
        auto const class_name = generate_random_string(32);
        UINT class_style{};
        if (class_styles_.empty()) {
            class_style = class_style::hredraw | class_style::vredraw;
        } else {
            for (auto const& cs : class_styles_) {
                class_style |= cs;
            }
        }
        DWORD window_style{};
        if (window_styles_.empty()) {
            window_style = static_cast<DWORD>(window_style::overlapped_window);
        } else {
            for (auto const& ws : window_styles_) {
                window_style |= ws;
            }
        }
        wc.cbSize = sizeof(wc);
        wc.style = class_style;
        wc.lpfnWndProc = procedure_;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = ::GetModuleHandle(nullptr);
        wc.hIcon = static_cast<HICON>(::LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        wc.hCursor = static_cast<HCURSOR>(::LoadImage(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = class_name.data();
        wc.hIconSm = static_cast<HICON>(LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        if (!::RegisterClassEx(&wc)) {
            return make_error_code();
        }
        auto hwnd = ::CreateWindowEx(
            WS_EX_OVERLAPPEDWINDOW,
            class_name.data(),
            title_.data(),
            WS_OVERLAPPEDWINDOW,
            position_.first,
            position_.second,
            size_.first,
            size_.second,
            parent_,
            nullptr,
            ::GetModuleHandle(nullptr),
            nullptr
        );
        if (!hwnd) {
            return make_error_code();
        }
        return hwnd;
    }
}
