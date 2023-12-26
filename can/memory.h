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

#ifndef CAN_MEMORY_H
#define CAN_MEMORY_H

#include <can/can.h>

#include <stdlib.h>

#define scoped_pointer                                                          \
    auto scoped(memory_free)

#define memory_new(something)                                                   \
    ((pointer(something))(memory_new)(sizeof(something)))

optimized
pointer(void) (memory_new)(size)
    size_t size;
    {
    pointer(void) space = calloc(1, size);
    assertion(space, "[can] memory allocation failed");
    return space;
    }

optimized
void (memory_free)(reference)
    pointer(void) reference;
    {
    pointer(pointer(void)) handle = reference;
    coalescing(handle):coalescing(*handle):
        (free(*handle), *handle = NULL);
    }

#endif
