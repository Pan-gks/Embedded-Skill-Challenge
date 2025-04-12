#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_lists.h"

// function: increases each node's value by 1
void nodes_change(void *data){
	(*(uint8_t *)data) +=1;
}

// Predicate: match value == 4
bool data_find(void *data){
	return (*(uint8_t *)data) == 4;
}

//Callback: print each node during iteration
void print_list_node(void *list_data, size_t index){
	printf("Node[%zu] = %u",index,*(uint8_t*)list_data);
}

int main(void) {

	struct thread_safe_list *new_list = init_list();
	if(!new_list){
		return 1;
	}

	uint8_t user_data []= {1,2,3,4,5,6};

	for(uint8_t i=0; i<(sizeof(user_data)/sizeof(user_data[0])); i++) {  //insert nodes in specific order
		insert_node(new_list,i,&user_data[i]);
	}

	uint8_t new_data = 3;
	size_t user_defined_index = 5;
	insert_node(new_list,user_defined_index,&new_data); // insert data to list to an user defined node

	user_defined_index = 5;
	void *retrieved_data = retrieve_data(new_list,user_defined_index);
	if (retrieved_data) {
		printf("Retrieved data %u from Node %zu\n", *(uint8_t *)retrieved_data,user_defined_index);
	}

	printf("List before changing and deleting nodes");
	iterate_list(new_list,print_list_node);	
	printf("\n");

	change_nodes_data(new_list,nodes_change);

	if(delete_node_by_predication(new_list,data_find)) {
		printf("4 value found in node and deleted\n");
	}
	else {
		printf("4 value not found in any node \n");
	}

	printf("List after changing and deleting nodes");
	iterate_list(new_list,print_list_node);	
	printf("\n");

	destroy_list(new_list);
}