#include <mado/window.hpp>

namespace mado
{
    LRESULT CALLBACK window::do_procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
    {
        switch (msg) {
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
        return do_procedure(hwnd, msg, wp, lp);
    }
}
