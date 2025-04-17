#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_lists.h"

struct thread_safe_list *init_list() {

	struct thread_safe_list *list = (struct thread_safe_list *)malloc(sizeof(struct thread_safe_list));
	
	if (list == NULL) {
		return NULL;
	}

	list->sentinel = malloc(sizeof(struct list_node));
	if (list->sentinel == NULL) {
		free(list);
		return NULL;
	}

	/* The next pointer of the sentinel is initialized to point to
	 * itself (the list should be circular even when empty */
	list->sentinel->next = list->sentinel;
	list->list_size = 0;
	pthread_mutex_init(&list->mtx, NULL);
	return list;

}

void destroy_list(struct thread_safe_list *list) {
	if(list == NULL){
		return ;
	}
	pthread_mutex_lock(&list->mtx);

	struct list_node *current_node = list->sentinel->next;
	while (current_node != list->sentinel) {
		struct list_node *tmp = current_node;
		current_node = current_node->next;
		free(tmp);
	}
	pthread_mutex_unlock(&list->mtx);
	pthread_mutex_destroy(&list->mtx);
	free(list->sentinel);
	free(list);
}

void insert_node (struct thread_safe_list *list,size_t index, void *input_data) {
	if(index > list->list_size){
		return ;
	}

	pthread_mutex_lock(&list->mtx);
	struct list_node *current_node = list->sentinel;
	
	for(size_t i=0; i<index; i++){
		current_node = current_node->next;
	}

	struct list_node *new_node; 
	new_node = (struct list_node *)malloc(sizeof(struct list_node));
	if (new_node == NULL) {
		return ;
	}

	new_node->data = input_data;

	new_node->next = current_node->next;
	current_node->next = new_node;
    
	list->list_size++;
   	
	pthread_mutex_unlock(&list->mtx);
}

void delete_node (struct thread_safe_list *list,size_t index) {
	if(index >= list->list_size){
		return ;
	}

	pthread_mutex_lock(&list->mtx);

	struct list_node *current_node ,*previus_node;

	previus_node = list->sentinel;
	current_node = previus_node->next;

	for(size_t i = 0; i<index; i++){
		previus_node = current_node;
		current_node = current_node->next;
	}
	
	previus_node->next = current_node->next;
    list->list_size--;
	free(current_node);
   	pthread_mutex_unlock(&list->mtx);
}

void *retrieve_data(struct thread_safe_list *list,size_t index) {
	if(index >= list->list_size){
		return NULL;
	}

	pthread_mutex_lock(&list->mtx);

	struct list_node *current_node = list->sentinel->next;

	for(size_t i=0; i<index; i++){
		current_node = current_node->next;
	}
   	
	pthread_mutex_unlock(&list->mtx);
	return(current_node->data);
}

void iterate_list(struct thread_safe_list *list, list_iterate_function callback) {
	if (!list || !callback) {
		return;
	}

    pthread_mutex_lock(&list->mtx);
    struct list_node *current_node= list->sentinel->next;
    size_t index = 0;

    while (current_node != list->sentinel) {
        callback(current_node->data,index);
        current_node = current_node->next;
        index++;
    }

    pthread_mutex_unlock(&list->mtx);
}

bool delete_node_by_predication(struct thread_safe_list*list,list_predication_function predicate) {

	if (!list || !predicate) {
		return false;
	}

	pthread_mutex_lock(&list->mtx);

	struct list_node *previus_node = list->sentinel;
	struct list_node *current_node = previus_node->next;
	
	while (current_node != list->sentinel) { 			//check if we returned to root 
		if(predicate(current_node->data)) {			//if we found what we are looking for
			previus_node->next = current_node->next;
			free(current_node);
			list->list_size--;
			pthread_mutex_unlock(&list->mtx);
			return true;
		}
		previus_node = current_node;
		current_node = current_node ->next;
	}

	pthread_mutex_unlock(&list->mtx);
	return false;
}

bool find_node_by_predication(struct thread_safe_list *list, list_predication_function predicate)
{
	if (!list || !predicate) {
		return false;
	}

    pthread_mutex_lock(&list->mtx);

    struct list_node *current_node = list->sentinel->next;
    while (current_node != list->sentinel) {
        if (predicate(current_node->data)) {
            pthread_mutex_unlock(&list->mtx);
            return true;
        }
        current_node = current_node->next;
    }
    pthread_mutex_unlock(&list->mtx);
    return false;
}

void change_nodes_data(struct thread_safe_list *list,list_operation_function function) {

	if(list == NULL){
		return ;
	}

	pthread_mutex_lock(&list->mtx);

	struct list_node *current_node = list->sentinel->next;

	while (current_node != list->sentinel) {
		function(current_node->data);
		current_node = current_node->next;
	}
	pthread_mutex_unlock(&list->mtx);
}

