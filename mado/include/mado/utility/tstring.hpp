#ifndef MADO_UTILITY_TSTRING_HPP
#define MADO_UTILITY_TSTRING_HPP

#include <tchar.h>
#include <string>
#include <string_view>

namespace mado
{
    using tstring = std::basic_string<TCHAR>;
    using tstring_view = std::basic_string_view<TCHAR>;
}

#endif
