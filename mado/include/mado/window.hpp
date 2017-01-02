#ifndef MADO_WINDOW_HPP
#define MADO_WINDOW_HPP

#include <mado/detail/type.hpp>
#include <Windows.h>
#include <functional>
#include <memory>

namespace mado
{
    template <typename T>
    class window
        : public std::enable_shared_from_this<window<T>>
    {
    public:
        using create_handler_type = std::function<bool(std::shared_ptr<T>)>;
        using close_handler_type = std::function<bool(std::shared_ptr<T>)>;

        static LRESULT CALLBACK window_procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
        {
            T* wnd = nullptr;
            if (msg == WM_NCCREATE) {
                auto const cs = reinterpret_cast<CREATESTRUCT const*>(lp);
                wnd = reinterpret_cast<T*>(cs->lpCreateParams);
                ::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd));
                wnd->hwnd_ = hwnd;
            } else {
                wnd = reinterpret_cast<T*>(::GetWindowLongPtr(hwnd, GWLP_USERDATA));
            }
            if (wnd) {
                return wnd->procedure(msg, wp, lp);
            }
            return ::DefWindowProc(hwnd, msg, wp, lp);
        }

    private:
        static bool default_callback(std::shared_ptr<T>) { return true; }

        create_handler_type create_handler_ = default_callback;
        close_handler_type close_handler_ = default_callback;

    protected:
        HWND hwnd_ = nullptr;
        tstring class_name_;
        window_property property_;
        bool rejected_create = false;

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

        void add_create_handler(create_handler_type const& handler)
        {
            create_handler_ = handler;
        }

        void add_close_handler(close_handler_type const& handler)
        {
            close_handler_ = handler;
        }

        LRESULT procedure(UINT msg, WPARAM wp, LPARAM lp)
        {
            auto wnd = std::static_pointer_cast<T>(shared_from_this());
            switch (msg) {
                case WM_CREATE: {
                    auto const created = create_handler_(wnd);
                    if (!created) {
                        rejected_create = true;
                    }
                    return created ? 0L : -1L;
                }
                case WM_CLOSE: {
                    auto const closed = close_handler_(wnd);
                    if (closed) {
                        ::DestroyWindow(hwnd_);
                    }
                    return 0L;
                }
                case WM_DESTROY: {
                    ::PostQuitMessage(0);
                    return 0L;
                }
            }
            return ::DefWindowProc(hwnd_, msg, wp, lp);
        }
    };
}

#endif
