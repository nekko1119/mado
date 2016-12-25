#include <mado/window_class_builder.hpp>
#include <Windows.h>

namespace mado
{
    window_class_builder& window_class_builder::style(std::initializer_list<class_style> styles) noexcept
    {
        UINT style = 0U;
        for (auto const& s : styles) {
            style |= s;
        }
        style_ = style;
        return *this;
    }

    WNDCLASSEX window_class_builder::build() const
    {
        WNDCLASSEX wc;
        wc.cbSize = sizeof(wc);
        wc.style = style_;
        wc.lpfnWndProc = ::DefWindowProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = ::GetModuleHandle(nullptr);
        wc.hIcon = static_cast<HICON>(::LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        wc.hCursor = static_cast<HCURSOR>(::LoadImage(nullptr, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = L"";
        wc.hIconSm = static_cast<HICON>(LoadImage(nullptr, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED));
        return wc;
    }
}
