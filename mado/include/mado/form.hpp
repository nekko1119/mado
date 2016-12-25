#ifndef MADO_FORM_HPP
#define MADO_FORM_HPP

#include <mado/detail/global_window_procedure.hpp>
#include <mado/detail/make_error_code.hpp>
#include <mado/detail/type.hpp>
#include <mado/utility/tstring.hpp>
#include <mado/window.hpp>
#include <tchar.h>
#include <Windows.h>
#include <memory>
#include <unordered_set>
#include <utility>
#include <variant>

namespace mado
{
    class form
        : public window
    {
        std::unordered_set<class_style> class_styles_;
        tstring_view title_ = _T("form");
        std::unordered_set<window_style> window_styles_;
        std::pair<int, int> position_ = {CW_USEDEFAULT, CW_USEDEFAULT};
        std::pair<int, int> size_ = {CW_USEDEFAULT, CW_USEDEFAULT};
        HWND parent_ = nullptr;

        form();
        explicit form(HWND hwnd);
        form(WNDCLASSEX const& wc, CREATESTRUCT const& cs);

        void initialize(WNDCLASSEX const& wc, CREATESTRUCT const& cs);

    public:
        virtual ~form() = default;
        void show();
        void hide();

        template <typename ...Args>
        friend std::variant<std::error_code, std::shared_ptr<form>> make_form(Args&&... args);
    };

    template <typename ...Args>
    std::variant<std::error_code, std::shared_ptr<form>> make_form(Args&&... args)
    {
        // private コンストラクタ対策で、
        // 関数内でサブクラスを作りそのサブクラスのshare_ptrオブジェクトを作成する
        struct sub : form {
            sub() : form{} {}
            sub(HWND hwnd) : form{hwnd} {}
            sub(WNDCLASSEX const& wc, CREATESTRUCT const& cs) : form{wc, cs} {}
        };
        try {
            auto frm = std::make_shared<sub>(std::forward<Args>(args)...);
            windows.emplace(frm->hwnd(), std::static_pointer_cast<window>(frm));
            return std::static_pointer_cast<form>(frm);
        } catch (std::system_error const& ec) {
            return ec.code();
        }
    }
}

#endif
