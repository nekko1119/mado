#ifndef MADO_CONFIG_HPP
#define MADO_CONFIG_HPP

#if !defined(_MSC_VER)
#   error "this compiler is not supported"
#endif

#if _MSC_VER < 1900
#   error "this msvc version is not supported"
#endif

#if defined(_M_IX86)
#   define MADORX_LIB_TARGET "_x86"
#elif defined(_M_X64)
#   define MADORX_LIB_TARGET "_x64"
#endif

#if defined(_DEBUG)
#   define MADORX_LIB_CONFIGURATION "_Debug"
#else
#   define MADORX_LIB_CONFIGURATION "_Release"
#endif

#if defined(MADORX_LIB_TARGET) &&\
    defined(MADORX_LIB_CONFIGURATION)
#  pragma comment(lib, "mado" MADORX_LIB_TARGET MADORX_LIB_CONFIGURATION ".lib")
#endif

#endif
#pragma once
