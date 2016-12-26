#include <mado/window.hpp>

namespace mado
{
    void window::on_create(std::shared_ptr<window>)
    {
    }

    LRESULT CALLBACK window::procedure_impl(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
    {
        switch (msg) {
            case WM_CREATE:
            {
                on_create(shared_from_this());
                return 0L;
            }
            case WM_DESTROY:
            {
                ::PostQuitMessage(0);
                return 0L;
            }
            default:
                return ::DefWindowProc(hwnd, msg, wp, lp);
        }
        // ここには来ない
        return 0L;
    }

    LRESULT CALLBACK window::procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
    {
        return procedure_impl(hwnd, msg, wp, lp);
    }
}
