﻿#ifndef MADO_DETAIL_ERROR_CODE_HPP
#define MADO_DETAIL_ERROR_CODE_HPP

#include <system_error>

namespace mado {
    std::error_code make_error_code() noexcept;
}

#endif
