#ifndef MADO_FORM_HPP
#define MADO_FORM_HPP

#include <mado/window.hpp>
#include <mado/window_builder.hpp>
#include <Windows.h>
#include <memory>
#include <variant>

namespace mado
{
    class form
        : window
    {
        friend std::variant<std::error_code, std::shared_ptr<form>> make_form(window_builder builder);
        explicit form(HWND hwnd);

    public:
        virtual ~form() = default;
        void visible();
        void invisible();
    };
}

#endif
