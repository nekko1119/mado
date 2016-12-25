#include <mado/detail/make_error_code.hpp>

#include <Windows.h>

namespace mado
{
    std::error_code make_error_code() noexcept
    {
        return {static_cast<int>(::GetLastError()), std::system_category()};
    }
}