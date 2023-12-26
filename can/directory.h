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

#ifndef CAN_DIRECTORY_H
#define CAN_DIRECTORY_H

#include <can/can.h>
#include <can/memory.h>

#include <dirent.h>
#include <string.h>

#define scoped_directory                                                        \
    pointer(DIR) scoped(directory_close)

#define directory_entry                                                         \
    pointer(struct dirent)

#define directory_names(path)                                                   \
    directory_names_callback(directory_count(path))(path)

#define directory_names_callback(count)                                         \
    ({                                                                          \
    pointer (char *(*(char*))[count]) callback =                                \
    function(char *(*       )[count], (char *path)                              \
    {                                                                           \
    scoped_directory handle = directory_open(path);                             \
    directory_entry  entry  = NULL;                                             \
                                                                                \
    char *(*names)[count] = memory_new(*names);                                 \
    size_t  max           = array_size(*names);                                 \
    size_t  i             = 0;                                                  \
                                                                                \
    while ((entry = directory_read(handle)) and i < max)                        \
        {                                                                       \
        (*names)[i] = strdup(entry->d_name);                                    \
        i ++;                                                                   \
        }                                                                       \
    return names;                                                               \
    });                                                                         \
    callback;                                                                   \
    })

#define directory_names_free(array)                                             \
    directory_names_free_callback(array)(array)

#define directory_names_free_callback(array)                                    \
    ({                                                                          \
    pointer (void  (typeof(array)         )) callback =                         \
    function(void, (typeof(array) pointers)                                     \
        {                                                                       \
        if (pointers)                                                           \
            {                                                                   \
            size_t n = array_size(*pointers);                                   \
            while (n --> 0)                                                     \
                free((*pointers)[n]);                                           \
            free(pointers);                                                     \
            }                                                                   \
        });                                                                     \
    callback;                                                                   \
    })

#define directory_read(directory)                                               \
    readdir(directory)

optimized
void (directory_close)(handler)
    pointer(pointer(DIR)) handler;
    {
    coalescing(handler):coalescing(*handler):
        (closedir(*handler), *handler = NULL);
    }

optimized
pointer(DIR) (directory_open)(path)
    char *path;
    {
    pointer(DIR) handle = opendir(path);
    assertion(handle, "[can] directory access failed");
    return handle;
    }

optimized
size_t (directory_count)(path)
    char *path;
    {
    scoped_directory handle = directory_open(path);
    directory_entry  entry  = NULL;
    size_t           size   = 0;

    while ((entry = directory_read(handle)))
        size ++;

    return size;
    }

#endif
