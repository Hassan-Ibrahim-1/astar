#pragma once

#include <iostream>

#define DEBUG_LOG
#define DEBUG_ASSERT
#define DEBUG_ERROR

#ifdef DEBUG_LOG
// printf("\033[33;44myellow on blue\n");

#define DEBUG_YELLOW "\033[33;33m"
#define DEBUG_RESET "\033[0m"

#define LOG(msg, ...) \
    do { \
        printf("%s[%s]%s: ", DEBUG_YELLOW, __PRETTY_FUNCTION__, DEBUG_RESET); \
        printf(msg, ##__VA_ARGS__); \
        printf("\n"); \
    } while (0)

#else
#define LOG(msg, ...) 
#endif // DEBUG_LOG

#ifdef DEBUG_ASSERT
#define DEBUG_RED     "\033[1;31m"
#define DEBUG_RESET   "\033[0m"

#define ASSERT(condition, msg, ...) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "%sAssertion failed in %s:%s %s | ", DEBUG_RED, __PRETTY_FUNCTION__, DEBUG_RESET, #condition); \
            fprintf(stderr, msg, ##__VA_ARGS__); \
            fprintf(stderr, "\n"); \
            std::abort(); \
        } \
    } while (0)

/*std::cerr << DEBUG_RED << "Assertion failed in " << __PRETTY_FUNCTION__ << ": " \*/
/*<< DEBUG_RESET << #condition << ", " << msg << "\n"; \*/
/*std::abort(); \*/
#else
#define ASSERT(condition, msg, ...) 
#endif // DEBUG_ASSERT

#ifdef DEBUG_ERROR
#define DEBUG_RED     "\033[1;31m"
#define DEBUG_RESET   "\033[0m"

#define ERROR(msg, ...) \
    do { \
        fprintf(stderr, "%s[ERROR -> %s]%s: ", DEBUG_RED, __PRETTY_FUNCTION__, DEBUG_RESET); \
        fprintf(stderr, msg, ##__VA_ARGS__); \
        fprintf(stderr, "\n"); \
        std::abort(); \
    } while (0)

#else
#define ERROR(msg, ...)  
#endif // DEBUG_ERROR

