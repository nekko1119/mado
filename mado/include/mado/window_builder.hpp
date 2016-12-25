#ifndef MADO_WINDOW_CLASS_BUILDER_HPP
#define MADO_WINDOW_CLASS_BUILDER_HPP

#include <mado/config.hpp>
#include <mado/utility/tstring.hpp>
#include <tchar.h>
#include <Windows.h>
#include <initializer_list>
#include <system_error>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <variant>

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

DEFILE_ENUM_LOGICAL_OPERATOR(class_style)
DEFILE_ENUM_LOGICAL_OPERATOR(window_style)

    class window_builder
    {
        std::unordered_set<class_style> class_styles_;
        tstring_view title_ = _T("");
        std::unordered_set<window_style> window_styles_;
        std::pair<int, int> position_ = {CW_USEDEFAULT, CW_USEDEFAULT};
        std::pair<int, int> size_ = {CW_USEDEFAULT, CW_USEDEFAULT};
        HWND parent_ = nullptr;

    public:
        window_builder& add_class_styles(std::initializer_list<class_style> styles) noexcept;
        window_builder& remove_class_styles(std::initializer_list<class_style> styles) noexcept;
        window_builder& title(tstring_view title) noexcept;
        window_builder& add_window_style(std::initializer_list<window_style> styles) noexcept;
        window_builder& remove_window_style(std::initializer_list<window_style> styles) noexcept;
        window_builder& position(int x, int y) noexcept;
        window_builder& size(int x, int y) noexcept;
        window_builder& parent(HWND parent) noexcept;

        std::variant<std::error_code, HWND> build() const;
    };
}

#endif

