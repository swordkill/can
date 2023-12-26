/*
::  ##  Reads a directory
::      Builds an array with the element's names

::  __  [note] The built array length equals the count of found elements

::  __  [note] This demonstrates how to return a VLA
::             using generics with a scalar parameter
*/

#include <can/directory.h>

#include <stdio.h>

int (main)(void)
    {
    auto tab = directory_names(".");

    for ( size_t i = 0
        ; i < array_size(*tab)
        ; i ++ )
        printf("%s\n", (*tab)[i]);

    directory_names_free(tab);

    return EXIT_SUCCESS;
    }
