/*
:: MIT License

:: Copyright (c) 2023 Saï 才 <git@onyle.com>

:: Permission is hereby granted, free of charge, to any person obtaining a copy
:: of this software and associated documentation files (the "Software"), to deal
:: in the Software without restriction, including without limitation the rights
:: to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
:: copies of the Software, and to permit persons to whom the Software is
:: furnished to do so, subject to the following conditions:

:: The above copyright notice and this permission notice shall be included in
:: all copies or substantial portions of the Software.

:: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
:: IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
:: FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
:: AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
:: LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
:: OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
:: SOFTWARE.
*/

#ifndef CAN_CAN_H
#define CAN_CAN_H

#include <stddef.h>
#include <assert.h>
#include <iso646.h>

#if not defined(__GNUC__)                                                       \
    or  defined(__clang__)                                                      \
    or  __GNUC__ <  4                                                           \
    or (__GNUC__ == 4 and __GNUC_MINOR__ < 9)
#   include <can requires gnu c dialect, gcc compiler 4.9 or above>
#endif

#define optimized                                                               \
    inline __attribute__((always_inline))

#define scoped(function)                                                        \
    __attribute__((cleanup(function)))

#define auto                                                                    \
    __auto_type

#define pointer(something)                                                      \
    typeof(typeof(something)*)

#define coalescing(pointer)                                                     \
    not (pointer) ? 0

#define function(signature, body)                                               \
    ({typeof(signature) _ body _;})

#define array_last(array)                                                       \
    (array_size(array) - 1)

#define array_size(array)                                                       \
    ({                                                                          \
    static_assert                                                               \
        (not __builtin_types_compatible_p                                       \
                (typeof(array), typeof(&array[0]))                              \
        , "[can] requires array type"                                           \
        );                                                                      \
    (sizeof(array) / sizeof(array[0]));                                         \
    })

#define assertion(condition, message)                                           \
    ({                                                                          \
    static_assert                                                               \
        (   __builtin_constant_p                                                \
                (message)                                                       \
        and __builtin_types_compatible_p                                        \
                (typeof(message), typeof(char[sizeof(message)]))                \
        , "[can] requires string literal message"                               \
        );                                                                      \
    (not (condition) ? assert(not message) : (void)0);                          \
    })

#define move(something)                                                         \
    ((typeof(something))(move)(&something))

#define move_unchecked(something)                                               \
    ((move)(&something))

optimized
pointer(void) (move)(reference)
    pointer(void) reference;
    {
    pointer(pointer(void)) handle = reference;
    pointer(void)          object = NULL;
    coalescing(handle):coalescing(*handle):
        (object = *handle, *handle = NULL);
    return object;
    }

#endif
