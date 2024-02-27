#include "list.h"

struct linked_list_node
{
    int data;
    struct linked_list_node *next;
};

struct list_instance_t
{
    struct linked_list_node *head;
};

