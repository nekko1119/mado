#ifndef MADO_UTILITY_TSTRING_HPP
#define MADO_UTILITY_TSTRING_HPP

#include <tchar.h>
#include <string>
#include <string_view>
#include <sstream>

namespace mado
{
    using tstring = std::basic_string<TCHAR>;
    using tstring_view = std::basic_string_view<TCHAR>;
    using tostringstream = std::basic_ostringstream<TCHAR>;
    using tistringstream = std::basic_istringstream<TCHAR>;
}

#endif
