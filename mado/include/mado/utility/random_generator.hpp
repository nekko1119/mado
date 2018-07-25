#ifndef MADO_UTILITY_RANDOM_GENERATOR_HPP
#define MADO_UTILITY_RANDOM_GENERATOR_HPP

#include <mado/config.hpp>
#include <mado/utility/tstring.hpp>

#include <algorithm>
#include <cstddef>
#include <utility>

namespace mado {
    template <typename F>
    tstring generate_random_string(std::size_t length, F&& supplier) {
        tstring buffer(length, '\0');
        std::generate_n(buffer.begin(), length, std::forward<F>(supplier));
        return buffer;
    }

    tstring generate_random_string(std::size_t length);
}

#endif
