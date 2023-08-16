#include "list_ops.h"

list_t *new_list(size_t length, list_element_t elements[])
{
    list_t *new_list = malloc(sizeof(list_t) + sizeof(list_element_t) * length);
    
    if (!new_list) return NULL;
    
    new_list->length = length;
    for (size_t i = 0; i < length; i++)
        new_list->elements[i] = elements[i];

    return new_list;
}

list_t *append_list(list_t *list1, list_t *list2)
{
    size_t new_length = list1->length + list2-> length;
    list_element_t *new_elements = malloc(sizeof(list_element_t) * new_length);

    size_t idx = 0;
    for(; idx < list1->length; idx++)
        new_elements[idx] = list1->elements[idx];
    
    for(size_t i = 0; idx < new_length; idx++, i++)
        new_elements[idx] = list2->elements[i];

    return new_list(new_length, new_elements);
}

list_t *filter_list(list_t *list, bool (*filter)(list_element_t))
{
    size_t i, j;
    list_element_t *filtered = malloc(sizeof(list_element_t) * list->length);

    for (i = 0, j = 0; i < list->length; i++)
        if (filter(list->elements[i])) 
            filtered[j++] = list->elements[i];

    return new_list(j, filtered);
}

size_t length_list(list_t *list)
{
    return list->length;
}

list_t *map_list(list_t *list, list_element_t (*map)(list_element_t))
{
    list_element_t *mapped = malloc(sizeof(list_element_t) * list->length);

    for (size_t i = 0; i < list->length; i++)
        mapped[i] = map(list->elements[i]);

    return new_list(list->length, mapped);
}

list_element_t foldl_list(list_t *list, list_element_t initial, 
                          list_element_t (*foldl)(list_element_t, list_element_t))
{
    for (size_t i = 0; i < list->length; i++)
        initial = foldl(initial, list->elements[i]);

    return initial;
}

list_element_t foldr_list(list_t *list, list_element_t initial, 
                          list_element_t (*foldr)(list_element_t, list_element_t))
{
    for (size_t i = list->length; i-- > 0; )
        initial = foldr(list->elements[i], initial);

    return initial;
}

list_t *reverse_list(list_t *list)
{
    list_element_t *reversed = malloc(sizeof(list_element_t) * list->length);

    for (size_t i = 0; i < list->length; i++)
        reversed[i] = list->elements[list->length - 1 - i];

    return new_list(list->length, reversed);
}

void delete_list(list_t *list)
{
    free(list);
}

