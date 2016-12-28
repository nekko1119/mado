#include <mado/utility/random_generator.hpp>

#include <tchar.h>
#include <random>

namespace
{
// コンパイラの未熟な実装により出る警告を抑止する
#pragma warning(push)
#pragma warning(disable: 4592)
    mado::tstring_view const string_set = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
#pragma warning(pop)
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
