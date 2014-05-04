
#pragma once

#if defined(WIN32) || defined(_WIN32)

    #ifndef MONTE_CARLO_LIB
        #define MONTE_CARLO_EXPORT __declspec(dllimport)
    #else
        #define MONTE_CARLO_EXPORT __declspec(dllexport)
    #endif

#else

    #define MONTE_CARLO_EXPORT

#endif