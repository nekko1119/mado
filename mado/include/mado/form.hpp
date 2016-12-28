#ifndef MADO_FORM_HPP
#define MADO_FORM_HPP

#include <mado/detail/make_error_code.hpp>
#include <mado/detail/type.hpp>
#include <mado/utility/tstring.hpp>
#include <mado/window.hpp>
#include <unordered_set>
#include <utility>
#include <variant>

namespace mado
{
    class form
        : public window
    {
        WNDCLASSEX wc_;

    protected:
        form();
        form(WNDCLASSEX const& wc, window_property const& property);

    public:
        virtual ~form() = default;
        void create();
        void show();
        void hide();

        template <typename Form, typename ...Args>
        friend std::variant<std::error_code, std::shared_ptr<form>> make_form(Args&&... args);
    };

    template <typename Form, typename ...Args>
    std::variant<std::error_code, std::shared_ptr<form>> make_form(Args&&... args)
    {
        try {
            // privateなコンストラクタを持ち、かつformは継承されうるためmake_sharedは使えない
            auto form = std::shared_ptr<Form>(new Form(std::forward<Args>(args)...));
            form->create();
            return std::static_pointer_cast<class form>(form);
        } catch (std::system_error const& ec) {
            return ec.code();
        }
    }
}

#endif
