#ifndef MADO_FORM_HPP
#define MADO_FORM_HPP

#include <mado/detail/make_error_code.hpp>
#include <mado/detail/window_property.hpp>
#include <mado/utility/tstring.hpp>
#include <mado/window.hpp>
#include <unordered_set>
#include <utility>

namespace mado
{
    class form
        : public window<form>
    {
        WNDCLASSEX wc_;

        void enable_window_style(LONG style);
        void disable_window_style(LONG style);
        bool is_enabled_window_style(LONG style) const;

    public:
        form();
        form(WNDCLASSEX const& wc, window_property const& property);

        virtual ~form() = default;
        void create();
        void enable_maximizebox();
        void disable_maximizebox();
        bool is_enabled_maximizebox() const;
        void enable_minimizebox();
        void disable_minimizebox();
        bool is_enabled_minimizebox() const;
    };
}

#endif
