#ifndef LISTS_H
#define LISTS_H

#include <pthread.h>
#include <stdbool.h>

struct list_node
{
    void *data;
    struct list_node  *next;
};

struct thread_safe_list {
    struct list_node *sentinel;  // Sentinel
    size_t list_size;
    pthread_mutex_t mtx;
};

typedef void (*list_iterate_function)(void *data,size_t index);
typedef bool (*list_predication_function)(void *data);
typedef void (*list_operation_function)(void *data);

struct thread_safe_list *init_list(void);
void destroy_list(struct thread_safe_list *list);
void insert_node (struct thread_safe_list *list,size_t index, void *input_data) ;
void delete_node (struct thread_safe_list *list,size_t index);
void *retrieve_data(struct thread_safe_list *list,size_t index);
void iterate_list(struct thread_safe_list *list, list_iterate_function callback); // Iterates over the list and calls the callback on each element.
bool delete_node_by_predication (struct thread_safe_list *list,list_predication_function predicate);
bool find_node_by_predication (struct thread_safe_list *list,list_predication_function predicate);
void change_nodes_data(struct thread_safe_list *list,list_operation_function function);

#endif // LISTS_H