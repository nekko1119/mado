#include <mado/utility/random_generator.hpp>

#include <mado/utility/tstring.hpp>
#include <tchar.h>
#include <random>

namespace
{
    mado::tstring_view string_set = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
}

namespace mado
{
    tstring generate_random_string(std::size_t length)
    {
        std::mt19937 engine{std::random_device{}()};
        std::uniform_int_distribution<std::size_t> dist{0U, string_set.size() - 1U};
        return generate_random_string(length, [&]() { return string_set[dist(engine)]; });
    };
}
