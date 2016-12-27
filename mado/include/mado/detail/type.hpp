#ifndef MADO_DETAIL_TYPE_HPP
#define MADO_DETAIL_TYPE_HPP

#include <mado/utility/tstring.hpp>
#include <Windows.h>
#include <memory>
#include <type_traits>
#include <unordered_set>
#include <utility>

#define DEFILE_ENUM_LOGICAL_OPERATOR(type)\
constexpr std::underlying_type_t<type> operator|=(std::underlying_type_t<type> left, type right) noexcept\
{\
    return left |= static_cast<std::underlying_type_t<type>>(right);\
}\
\
constexpr std::underlying_type_t<type> operator|(type left, type right) noexcept\
{\
    return static_cast<std::underlying_type_t<type>>(left) |= right;\
}\
\
constexpr std::underlying_type_t<type> operator|(std::underlying_type_t<type> left, type right) noexcept\
{\
    return left |= right;\
}\
\
constexpr std::underlying_type_t<type> operator|(type left, std::underlying_type_t<type> right) noexcept\
{\
    return right |= left;\
}\
\
constexpr std::underlying_type_t<type> operator&=(std::underlying_type_t<type> left, type right) noexcept\
{\
    return left &= static_cast<std::underlying_type_t<type>>(right);\
}\
\
constexpr std::underlying_type_t<type> operator&(type left, type right) noexcept\
{\
    return static_cast<std::underlying_type_t<type>>(left) &= right;\
}\
\
constexpr std::underlying_type_t<type> operator&(std::underlying_type_t<type> left, type right) noexcept\
{\
    return left &= right;\
}\
\
constexpr std::underlying_type_t<type> operator&(type left, std::underlying_type_t<type> right) noexcept\
{\
    return right &= left;\
}\
\
constexpr std::underlying_type_t<type> operator~(type t) noexcept\
{\
    return ~static_cast<std::underlying_type_t<type>>(t);\
}

namespace mado
{
    enum class class_style : UINT
    {
        byte_align_client = CS_BYTEALIGNCLIENT,
        byte_align_window = CS_BYTEALIGNWINDOW,
        class_dc = CS_CLASSDC,
        db_clicks = CS_DBLCLKS,
        drop_shadow = CS_DROPSHADOW,
        global_class = CS_GLOBALCLASS,
        hredraw = CS_HREDRAW,
        no_close = CS_NOCLOSE,
        own_dc = CS_OWNDC,
        parent_dc = CS_PARENTDC,
        save_bits = CS_SAVEBITS,
        vredraw = CS_VREDRAW
    };

    enum class window_style : DWORD
    {
        border = WS_BORDER,
        caption = WS_CAPTION,
        child = WS_CHILD, // WS_CHILDWINDOW も同じ値
        clip_children = WS_CLIPCHILDREN,
        clip_siblings = WS_CLIPSIBLINGS,
        disabled = WS_DISABLED,
        dialog_frame = WS_DLGFRAME,
        group = WS_GROUP,
        hscroll = WS_HSCROLL,
        maximize = WS_MAXIMIZE,
        maximize_box = WS_MAXIMIZEBOX,
        minimize = WS_MINIMIZE, // WS_ICONIC も同じ値
        minimize_box = WS_MINIMIZEBOX,
        overlapped = WS_OVERLAPPED, // WS_TILED も同じ値
        overlapped_window = WS_OVERLAPPEDWINDOW, // WS_TILEDWINDOW も同じ値
        popup = WS_POPUP,
        popup_window = WS_POPUPWINDOW,
        sysmenu = WS_SYSMENU,
        tabstop = WS_TABSTOP,
        thick_frame = WS_THICKFRAME, // WS_SIZEBOX も同じ値
        tiled_window = WS_TILEDWINDOW,
        visible = WS_VISIBLE,
        vscroll = WS_VSCROLL
    };

    enum class window_ex_style : DWORD
    {
        overlapped_window = WS_EX_OVERLAPPEDWINDOW
    };

DEFILE_ENUM_LOGICAL_OPERATOR(class_style)
DEFILE_ENUM_LOGICAL_OPERATOR(window_style)
DEFILE_ENUM_LOGICAL_OPERATOR(window_ex_style)

    struct window_property
    {
        std::unordered_set<window_ex_style> window_ex_styles = {window_ex_style::overlapped_window};
        std::unordered_set<window_style> window_styles = {window_style::overlapped_window};
        tstring class_name;
        tstring title = _T("");
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
