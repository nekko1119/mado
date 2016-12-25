#include <mado/detail/global_window_procedure.hpp>
#include <mado/window.hpp>

namespace mado
{
    std::unordered_map<HWND, std::shared_ptr<window>> windows;
    LRESULT CALLBACK global_window_procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
    {
        auto const it = windows.find(hwnd);
        if (it == windows.end()) {
            return ::DefWindowProc(hwnd, msg, wp, lp);
        }
        auto result = it->second->procedure(hwnd, msg, wp, lp);
        if (msg == WM_DESTROY) {
            windows.erase(it);
        }
        return result;
    }
}