#ifndef MADO_WINDOW_HPP
#define MADO_WINDOW_HPP

#include <mado/detail/type.hpp>
#include <Windows.h>
#include <memory>

namespace mado
{
    class window
        : std::enable_shared_from_this<window>
    {
    private:
        virtual LRESULT CALLBACK procedure_impl(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
        virtual void on_create(std::shared_ptr<window> window);

    protected:
        HWND hwnd_ = nullptr;
        window_property property_;
        window() = default;
        explicit window(window_property const& property);
        ~window() = default;
        window(window const&) = delete;
        window& operator=(window const&) = delete;

    public:
        HWND hwnd() const
        {
            return hwnd_;
        }

        window_property const& property() const
        {
            return property_;
        }

        LRESULT CALLBACK procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
    };
}

#endif
