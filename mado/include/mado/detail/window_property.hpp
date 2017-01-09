#ifndef MADO_DETAIL_WINDOW_PROPERTY_HPP
#define MADO_DETAIL_WINDOW_PROPERTY_HPP

#include <mado/utility/tstring.hpp>
#include <Windows.h>
#include <memory>
#include <type_traits>
#include <utility>

namespace mado
{
    struct window_property
    {
        tstring class_name;
        tstring title;
        std::pair<int, int> position = {CW_USEDEFAULT, CW_USEDEFAULT};
        std::pair<int, int> size = {CW_USEDEFAULT, CW_USEDEFAULT};
        HWND parent = nullptr;
        HMENU hmenu = nullptr;
        HINSTANCE hInstance = ::GetModuleHandle(nullptr);
        LPVOID create_params = nullptr;

        window_property() = default;
        explicit window_property(tstring_view class_name);
        std::unique_ptr<CREATESTRUCT> to_createstruct() const;
        HWND create() const;
    };

}

#endif
