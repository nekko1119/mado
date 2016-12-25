#include <mado/form_builder.hpp>

#include <mado/detail/global_window_procedure.hpp>
#include <mado/detail/make_error_code.hpp>
#include <mado/utility/random_generator.hpp>

namespace mado
{
    form_builder& form_builder::add_class_styles(std::initializer_list<class_style> styles)
    {
        for (auto const& s : styles) {
            class_styles_.emplace(s);
        }
        return *this;
    }

    form_builder& form_builder::remove_class_styles(std::initializer_list<class_style> styles)
    {
        for (auto const& s : styles) {
            class_styles_.erase(s);
        }
        return *this;
    }

    form_builder& form_builder::title(tstring_view title) noexcept
    {
        title_ = std::move(title);
        return *this;
    }

    form_builder& form_builder::add_window_style(std::initializer_list<window_style> styles)
    {
        for (auto const& s : styles) {
            window_styles_.emplace(s);
        }
        return *this;
    }

    form_builder& form_builder::remove_window_style(std::initializer_list<window_style> styles)
    {
        for (auto const& s : styles) {
            window_styles_.erase(s);
        }
        return *this;
    }

    form_builder& form_builder::position(int x, int y) noexcept
    {
        position_ = std::make_pair(x, y);
        return *this;
    }

    form_builder& form_builder::size(int x, int y) noexcept
    {
        size_ = std::make_pair(x, y);
        return *this;
    }

    form_builder& form_builder::parent(HWND parent) noexcept
    {
        parent_ = parent;
        return *this;
    }

    std::variant<std::error_code, std::shared_ptr<form>> form_builder::build() const
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

        return make_form(wc, cs);
    }
}
