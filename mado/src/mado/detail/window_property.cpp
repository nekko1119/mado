#include <mado/detail/window_property.hpp>

#include <mado/window.hpp>
#include <functional>

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
        auto const cs = to_createstruct();
        return ::CreateWindowEx(
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
    }
}