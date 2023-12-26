/*
::  ## ISO C
::      Lists are implemented with data as void pointer
::      giving responsability to the user to cast it
::      into the appropriate type

::  ## GNU C
::      Using generics the data field is typed
*/

#include <can/list.h>

#include <stdio.h>

typedef struct
    {
    int x;
    int y;
    }
    Point;

pointer(list(Point)) (create_list_of_points)(void)
    {
    scoped_list points = list_new(Point);

    for (int i = 10; i --> 0;)
        {
        auto p = list_prepend(points);
        node_data(p).x = i;
        node_data(p).y = i;
        }

    return move_unchecked(points);
    }

int (main)(void)
    {
    scoped_list points = list_check(create_list_of_points());

    auto next = list_forward(points);
    while (next)
        {
        printf("(%i, %i) "
            , node_data(next).x
            , node_data(next).y);
        next = list_forward(points);
        }
    printf("\n");

    return EXIT_SUCCESS;
    }
