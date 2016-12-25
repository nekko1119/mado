#ifndef MADO_DETAIL_GLOBAL_WINDOW_PROCEDURE_HPP
#define MADO_DETAIL_GLOBAL_WINDOW_PROCEDURE_HPP

#include <mado/window.hpp>
#include <Windows.h>
#include <memory>
#include <unordered_map>

namespace mado
{
    extern std::unordered_map<HWND, std::shared_ptr<window>> windows;
    LRESULT CALLBACK global_window_procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
}

#endif
