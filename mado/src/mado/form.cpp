#include <mado/form.hpp>

#include <mado/detail/global_window_procedure.hpp>

namespace mado
{
    std::variant<std::error_code, std::shared_ptr<form>> make_form(window_builder builder)
    {
        // private コンストラクタ対策で、
        // 関数内でサブクラスを作りそのサブクラスのshare_ptrオブジェクトを作成する
        struct sub : form {
            sub(HWND hwnd) : form{hwnd} {}
        };
        builder.procedure(global_window_procedure);
        auto const built_result = builder.build();
        if (auto code = std::get_if<std::error_code>(&built_result)) {
            return *code;
        }
        auto frm = std::make_shared<sub>(std::get<HWND>(built_result));
        windows.emplace(frm->hwnd(), std::shared_ptr<window>(frm, static_cast<window*>(frm.get())));
        return std::dynamic_pointer_cast<form>(frm);
    }

    form::form(HWND hwnd)
        : window{hwnd}
    {
    }

    void form::visible()
    {
        ::ShowWindow(hwnd_, SW_SHOW);
    }

    void form::invisible()
    {
        ::ShowWindow(hwnd_, SW_HIDE);
    }
}
