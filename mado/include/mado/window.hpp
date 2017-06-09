#ifndef MADO_WINDOW_HPP
#define MADO_WINDOW_HPP

#include <mado/detail/window_property.hpp>
#include <Windows.h>
#include <functional>
#include <memory>
#include <utility>

namespace mado
{
    template <typename T>
    class window
    {
    public:
        using should_create_handler_type = std::function<bool (T&)>;
        using should_close_handler_type = std::function<bool (T&)>;
        using on_create_handler_type = std::function<void (T&)>;
        using on_close_handler_type = std::function<void (T&)>;

        static LRESULT CALLBACK window_procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
        {
            T* wnd = nullptr;
            if (msg == WM_NCCREATE) {
                auto const cs = reinterpret_cast<CREATESTRUCT const*>(lp);
                wnd = static_cast<T*>(cs->lpCreateParams);
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
        static bool default_comfirm_callback(T&)
        {
            return true;
        }

        static void default_callback(T&)
        {
        }

        should_create_handler_type should_create_handler_ = default_comfirm_callback;
        should_close_handler_type should_close_handler_ = default_comfirm_callback;
        on_create_handler_type on_create_handler_ = default_callback;
        on_close_handler_type on_close_handler_ = default_callback;

        LRESULT procedure(UINT msg, WPARAM wp, LPARAM lp)
        {
            auto& wnd = static_cast<T&>(*this);
            switch (msg) {
                case WM_CREATE: {
                    auto const should_create = should_create_handler_(wnd);
                    if (should_create) {
                        on_create_handler_(wnd);
                    }
                    created_ = should_create;
                    rejected_creation_ = !created_;
                    return created_ ? 0L : -1L;
                }
                case WM_CLOSE: {
                    auto const closed = should_close_handler_(wnd);
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

    protected:
        HWND hwnd_ = nullptr;
        tstring class_name_;
        window_property property_;
        bool rejected_creation_ = false;
        bool created_ = false;

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

        bool is_created() const
        {
            return created_;
        }

        void show()
        {
            if (!created_) {
                property_.window_style |= WS_VISIBLE;
                return;
            }
            ::ShowWindow(hwnd_, SW_SHOW);
        }

        void hide()
        {
            if (!created_) {
                property_.window_style &= ~WS_VISIBLE;
                return;
            }
            ::ShowWindow(hwnd_, SW_HIDE);
        }

        bool is_visible() const
        {
            if (!created_) {
                return property_.style & WS_VISIBLE;
            }
            return ::IsWindowVisible(hwnd_);
        }

        void title(tstring_view title)
        {
            if (!created_) {
                property_.title = title.data();
                return;
            }
            ::SetWindowText(hwnd_, title.data());
        }

        void set_should_create_handler(should_create_handler_type const& handler)
        {
            should_create_handler_ = handler;
        }

        void set_should_close_handler(should_close_handler_type const& handler)
        {
            should_close_handler_ = handler;
        }

        void set_on_create_handler(on_create_handler_type const& handler)
        {
            on_create_handler_ = handler;
        }

        void set_on_close_handler(on_create_handler_type const& handler)
        {
            on_close_handler_ = handler;
        }

    private:
        template <typename T, typename ...Args>
        static std::unique_ptr<T> make(Args&&... args) {
            return std::unique_ptr<T>{new T{std::forward<Args>(args)...}};
        }

        template <typename T, typename ...Args>
        friend std::unique_ptr<T> make(Args&&... args);
    };

    template <typename T, typename ...Args>
    std::unique_ptr<T> make(Args&&... args) {
        return window<T>::make<T>(std::forward<Args>(args)...);
    }
}

#endif
