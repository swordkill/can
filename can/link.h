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

#ifndef CAN_LINK_H
#define CAN_LINK_H

#include <can/can.h>

typedef struct link
    {
    pointer(struct link) forward;
    pointer(struct link) backward;
    }
    link;

optimized
pointer(link) (link_forward)(source)
    pointer(link) source;
    {
    return coalescing(source):
        source->forward;
    }

optimized
pointer(link) (link_backward)(source)
    pointer(link) source;
    {
    return coalescing(source):
        source->backward;
    }

optimized
void (link_set_forward)(source, destination)
    pointer(link) source;
    pointer(link) destination;
    {
    coalescing(source):
        (source->forward = destination);
    }

optimized
void (link_set_backward)(source, destination)
    pointer(link) source;
    pointer(link) destination;
    {
    coalescing(source):
        (source->backward = destination);
    }

#define link_forward(source)                                                    \
    (link_forward((pointer(link)) source))

#define link_backward(source)                                                   \
    (link_backward((pointer(link)) source))

#define link_set_forward(source, destination)                                   \
    (link_set_forward((pointer(link)) source, (pointer(link)) destination))

#define link_set_backward(source, destination)                                  \
    (link_set_backward((pointer(link)) source, (pointer(link)) destination))

#endif
