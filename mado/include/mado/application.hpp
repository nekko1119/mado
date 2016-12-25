#ifndef MADO_APPLICATION_HPP
#define MADO_APPLICATION_HPP

#include <mado/config.hpp>
#include <mado/detail/make_error_code.hpp>
#include <Windows.h>
#include <memory>
#include <optional>

namespace mado
{
    struct blocking
    {
        static std::optional<std::error_code> process()
        {
            ::MSG msg;
            while (true) {
                auto const state = ::GetMessage(&msg, nullptr, 0U, 0U);
                // WM_QUIT が呼ばれた
                if (state == 0) {
                    return std::nullopt;
                }
                // 何かエラーが起きた
                if (state == -1) {
                    return make_error_code();
                }
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
    };

    struct peeking
    {
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
                    std::forward<F>(f)();
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
        static std::optional<std::error_code> run(std::shared_ptr<Form> main_form)
        {
            return blocking::process();
        }
    };

    template <>
    class application<peeking> final
    {
    public:
        application() = delete;

        template <typename Form, typename F>
        static void run(std::shared_ptr<Form> main_form, F&& f)
        {
            peeking::process(std::forward<F>(f));
        }
    };
}

#endif

