#ifndef MADO_BUTTON_HPP
#define MADO_BUTTON_HPP

#include <mado/window.hpp>

namespace mado
{
    class button
        : public window<button>
    {
    public:
        explicit button(HWND parent, tstring_view title);
        void create();
    };
}

#endif
