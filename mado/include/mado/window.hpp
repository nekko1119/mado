#ifndef MADO_WINDOW_HPP
#define MADO_WINDOW_HPP

#include <mado/detail/type.hpp>
#include <Windows.h>
#include <memory>

namespace mado
{
    class window
        : private std::enable_shared_from_this<window>
    {
    public:
        static LRESULT CALLBACK window_procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
        {
            window* wnd = nullptr;
            if (msg == WM_NCCREATE) {
                auto const cs = reinterpret_cast<CREATESTRUCT const*>(lp);
                wnd = reinterpret_cast<window*>(cs->lpCreateParams);
                ::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd));
                wnd->hwnd_ = hwnd;
            } else {
                wnd = reinterpret_cast<window*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
            }
            if (wnd) {
                return wnd->procedure(msg, wp, lp);
            }
            return ::DefWindowProc(hwnd, msg, wp, lp);
        }

    private:
        virtual void on_create(window&)
        {
        }

        virtual LRESULT do_procedure(UINT msg, WPARAM wp, LPARAM lp)
        {
            switch (msg) {
                case WM_CREATE: {
                    on_create(*this);
                    return 0L;
                }
                case WM_DESTROY: {
                    ::PostQuitMessage(0);
                    return 0L;
                }
            }
            return ::DefWindowProc(hwnd_, msg, wp, lp);
        }

    protected:
        HWND hwnd_ = nullptr;
        tstring class_name_;
        window_property property_;

        explicit window(tstring_view class_name)
            : window{class_name, {}}
        {
        }

        window(tstring_view class_name, window_property const& property)
            : class_name_{class_name}, property_{property}
        {
            property_.class_name = class_name_.c_str();
        }

        ~window() = default;
        window(window const&) = delete;
        window& operator=(window const&) = delete;

    public:
        HWND hwnd() const
        {
            return hwnd_;
        }

        tstring_view class_name() const
        {
            return class_name_;
        }

        window_property const& property() const
        {
            return property_;
        }

        LRESULT procedure(UINT msg, WPARAM wp, LPARAM lp)
        {
            return do_procedure(msg, wp, lp);
        }
    };
}

#endif
