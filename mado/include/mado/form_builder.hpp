#ifndef MADO_WINDOW_CLASS_BUILDER_HPP
#define MADO_WINDOW_CLASS_BUILDER_HPP

#include <mado/config.hpp>
#include <mado/detail/window_property.hpp>
#include <mado/form.hpp>
#include <mado/utility/tstring.hpp>
#include <initializer_list>

namespace mado
{
    class form_builder
    {
        window_property property_;

    public:
        form_builder& title(tstring_view title) noexcept;
        form_builder& position(int x, int y) noexcept;
        form_builder& size(int x, int y) noexcept;
        form_builder& parent(HWND parent) noexcept;

        std::variant<std::error_code, std::shared_ptr<form>> build() const;
    };
}

#endif

