#ifndef MADO_WINDOW_HPP
#define MADO_WINDOW_HPP

#include <Windows.h>

namespace mado
{
    class window
    {
    private:
        virtual LRESULT CALLBACK do_procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

    protected:
        HWND hwnd_ = nullptr;
        constexpr window(HWND hwnd) : hwnd_{hwnd} {}
        ~window() = default;
        window(window const&) = delete;
        window& operator=(window const&) = delete;

    public:
        HWND hwnd() const
        {
            return hwnd_;
        }

        LRESULT CALLBACK procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
    };
}

#endif
