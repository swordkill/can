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

#ifndef CAN_LIST_H
#define CAN_LIST_H

#include <can/link.h>
#include <can/memory.h>

#define list_new(something)                                                     \
    ({                                                                          \
    list(something) unrolled;                                                   \
    auto instance = memory_new(unrolled);                                       \
    list_check(instance);                                                       \
    })

#define list(something)                                                         \
    typeof                                                                      \
    (                                                                           \
    struct head                                                                 \
        {                                                                       \
        struct link super;                                                      \
        size_t length;                                                          \
        struct node                                                             \
            {                                                                   \
            struct link super;                                                  \
            typeof(something) data;                                             \
            }                                                                   \
            *iterator;                                                          \
                                                                                \
        pointer(size_t       (struct head *)) size;                             \
        pointer(void         (struct head *)) reset;                            \
        pointer(struct node *(struct head *)) forward;                          \
        pointer(struct node *(struct head *)) backward;                         \
        pointer(struct node *(struct head *)) append;                           \
        pointer(struct node *(struct head *)) prepend;                          \
        pointer(struct node *(struct head *)) extract;                          \
        }                                                                       \
    )

#define list_check(instance)                                                    \
    ({                                                                          \
    auto unrolled = instance;                                                   \
                                                                                \
    typedef typeof(*unrolled)           list;                                   \
    typedef typeof(*unrolled->iterator) node;                                   \
                                                                                \
    unrolled->size = function(size_t, (head)                                    \
        pointer(list) head;                                                     \
        {                                                                       \
        assert(head);                                                           \
        return head->length;                                                    \
        });                                                                     \
                                                                                \
    unrolled->reset = function(void, (head)                                     \
        pointer(list) head;                                                     \
        {                                                                       \
        assert(head);                                                           \
        head->iterator = NULL;                                                  \
        });                                                                     \
                                                                                \
    unrolled->forward = function(pointer(node), (head)                          \
        pointer(list) head;                                                     \
        {                                                                       \
        assert(head);                                                           \
        if (head->iterator)                                                     \
                head->iterator = (pointer(node)) link_forward(head->iterator);  \
        else    head->iterator = (pointer(node)) link_forward(head);            \
        return  head->iterator;                                                 \
        });                                                                     \
                                                                                \
    unrolled->backward = function(pointer(node), (head)                         \
        pointer(list) head;                                                     \
        {                                                                       \
        assert(head);                                                           \
        if (head->iterator)                                                     \
                head->iterator = (pointer(node)) link_backward(head->iterator); \
        else    head->iterator = (pointer(node)) link_backward(head);           \
        return  head->iterator;                                                 \
        });                                                                     \
                                                                                \
    unrolled->append = function(pointer(node), (head)                           \
        pointer(list) head;                                                     \
        {                                                                       \
        assert(head);                                                           \
        auto novel = memory_new(*head->iterator);                               \
        if (head->length)                                                       \
                {                                                               \
                link_set_backward(              novel, link_backward(head));    \
                link_set_forward (link_backward(head), novel              );    \
                }                                                               \
        else    link_set_forward (head , novel);                                \
                link_set_backward(head , novel);                                \
        return  (head->length ++, novel);                                       \
        });                                                                     \
                                                                                \
    unrolled->prepend = function(pointer(node), (head)                          \
        pointer(list) head;                                                     \
        {                                                                       \
        assert(head);                                                           \
        auto novel = memory_new(*head->iterator);                               \
        if (head->length)                                                       \
                {                                                               \
                link_set_forward (             novel, link_forward(head));      \
                link_set_backward(link_forward(head), novel             );      \
                }                                                               \
        else    link_set_backward(head , novel);                                \
                link_set_forward (head , novel);                                \
        return  (head->length ++, novel);                                       \
        });                                                                     \
                                                                                \
    unrolled->extract = function(pointer(node), (head)                          \
        pointer(list) head;                                                     \
        {                                                                       \
        assert(head);                                                           \
        auto i = head->iterator;                                                \
        if (i)                                                                  \
            {                                                                   \
            if (link_backward(i))                                               \
                    link_set_forward(link_backward(i), link_forward (i));       \
            else    link_set_forward(            head, link_forward (i));       \
            if (link_forward (i))                                               \
                    link_set_backward(link_forward(i), link_backward(i));       \
            else    link_set_backward(           head, link_backward(i));       \
            if (link_backward(i))                                               \
                    head->iterator = (pointer(node)) link_backward(i);          \
            else    head->iterator = (pointer(node)) link_forward (i);          \
            link_set_backward(i, NULL);                                         \
            link_set_forward (i, NULL);                                         \
            head->length --;                                                    \
            }                                                                   \
        return i;                                                               \
        });                                                                     \
                                                                                \
    unrolled;                                                                   \
    })

#define node_data(    node) (node->data          )
#define list_size(    list) (list->size    (list))
#define list_reset(   list) (list->reset   (list))
#define list_append(  list) (list->append  (list))
#define list_prepend( list) (list->prepend (list))
#define list_extract( list) (list->extract (list))
#define list_forward( list) (list->forward (list))
#define list_backward(list) (list->backward(list))

#define scoped_list                                                             \
    auto scoped(list_free)

optimized
void (list_free)(reference)
    pointer(void) reference;
    {
    pointer(pointer(void)) handle = reference;
    pointer(link)          mark   = *handle;
    while (mark)
        {
        pointer(link) next = link_forward(mark);
        free(mark);
        mark = next;
        }
    }

#endif
