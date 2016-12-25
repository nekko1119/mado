#ifndef MADO_WINDOW_CLASS_BUILDER_HPP
#define MADO_WINDOW_CLASS_BUILDER_HPP

#include <mado/config.hpp>
#include <mado/utility/tstring.hpp>
#include <Windows.h>
#include <initializer_list>

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
        hredoraw = CS_HREDRAW,
        no_close = CS_NOCLOSE,
        own_dc = CS_OWNDC,
        parent_dc = CS_PARENTDC,
        save_bits = CS_SAVEBITS,
        vredraw = CS_VREDRAW
    };

    constexpr UINT operator|=(UINT left, class_style right)
    {
        return left |= static_cast<UINT>(right);
    }

    constexpr UINT operator|(class_style left, class_style right)
    {
        return static_cast<UINT>(left) |= right;
    }

    class window_class_builder
    {
        UINT style_;

    public:
        window_class_builder()
        {}

        window_class_builder& style(std::initializer_list<class_style> styles) noexcept;

        WNDCLASSEX build() const;
    };
}

#endif

