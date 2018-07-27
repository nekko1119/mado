#ifndef MADO_APPLICATION_HPP
#define MADO_APPLICATION_HPP

#include <mado/config.hpp>
#include <mado/detail/make_error_code.hpp>

#include <Windows.h>

#include <memory>
#include <system_error>

namespace mado {
    struct blocking {
        static void process() {
            ::MSG msg;
            while (true) {
                auto const state = ::GetMessage(&msg, nullptr, 0U, 0U);
                // called WM_QUIT
                if (state == 0) {
                    return;
                }
                // some error occured
                if (state == -1) {
                    throw std::system_error{make_error_code()};
                }
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
    };

    struct peeking {
        template <typename F>
        static void process(F&& f) {
            ::MSG msg;
            while (true) {
                if (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
                    if (msg.message == WM_QUIT) {
                        return;
                    }
                    ::TranslateMessage(&msg);
                    ::DispatchMessage(&msg);
                } else {
                    f();
                }
            }
        }
    };

    template <typename MessageProcess>
    class application;

    template <>
    class application<blocking> final
    {
    public:
        application() = delete;

        template <typename Form>
        static void run(std::unique_ptr<Form> main_form) {
            blocking::process();
        }
    };

    template <>
    class application<peeking> final
    {
    public:
        application() = delete;

        template <typename Form, typename F>
        static void run(std::unique_ptr<Form> main_form, F&& f) {
            main_form->create();
            main_form->show();
            peeking::process(std::forward<F>(f));
        }
    };
}

#endif
