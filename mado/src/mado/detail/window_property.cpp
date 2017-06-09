#include <mado/detail/window_property.hpp>

#include <mado/window.hpp>
#include <functional>
#include <stdexcept>

namespace mado
{
    window_property::window_property(tstring_view class_name)
        : class_name{class_name}
    {
    }

    std::unique_ptr<CREATESTRUCT> window_property::to_createstruct() const
    {
        auto cs = std::make_unique<CREATESTRUCT>();
        cs->dwExStyle = WS_EX_OVERLAPPEDWINDOW;
        cs->lpszClass = class_name.c_str();
        cs->lpszName = title.c_str();
        cs->style = window_style;
        cs->x = position.first;
        cs->y = position.second;
        cs->cx = size.first;
        cs->cy = size.second;
        cs->hwndParent = parent;
        cs->hMenu = hmenu;
        cs->hInstance = hInstance;
        cs->lpCreateParams = create_params;
        return cs;
    }
    HWND window_property::create() const
    {
        if (created_) {
            throw std::logic_error{"window is already created"};
        }
        auto const cs = to_createstruct();
        auto const hwnd = ::CreateWindowEx(
            cs->dwExStyle,
            cs->lpszClass,
            cs->lpszName,
            cs->style,
            cs->x,
            cs->y,
            cs->cx,
            cs->cy,
            cs->hwndParent,
            cs->hMenu,
            cs->hInstance,
            cs->lpCreateParams
        );
        created_ = true;
        return hwnd;
    }
}