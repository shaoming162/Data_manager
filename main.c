#include <stdio.h>
#include <inttypes.h>
#include "datamgr.h"
// #include "list.h"

int list_errno;

/*
 * Copy the 'content' of src_element to dst_element.
 */
void element_copy(element_ptr_t *dest_element, element_ptr_t src_element)
{
	*dest_element = malloc(sizeof(sensor_node_t));
	((sensor_node_t*)*dest_element)->sensor_id = ((sensor_node_t*)src_element)->sensor_id;
	((sensor_node_t*)*dest_element)->room_id = ((sensor_node_t*)src_element)->room_id;
	((sensor_node_t*)*dest_element)->running_avg = ((sensor_node_t*)src_element)->running_avg;
	((sensor_node_t*)*dest_element)->last_modified = ((sensor_node_t*)src_element)->last_modified;
}


/*
 * Clean up element, including freeing memory if needed
 */
void element_free(element_ptr_t *element)
{

}

/*
 * Print 1 element to stdout. 
 */
void element_print(element_ptr_t element)
{
	printf("Sensor ID: %" PRIu16 " Room ID: %" PRIu16 " Avg Temp: %f Last modified: %d\n", ((sensor_node_t*)element)->sensor_id, ((sensor_node_t*)element)->room_id, ((sensor_node_t*)element)->running_avg, ((sensor_node_t*)element)->last_modified);
}

/*
 * Compare two element elements; returns -1, 0 or 1 
 */
int element_compare(element_ptr_t x, element_ptr_t y)
{

}

int main(int argc, char const *argv[])
{
	list_ptr_t list = list_create( &element_copy, &element_free, &element_compare, &element_print );
	initialize_pointer_list(list);
	list_print(list);
	// sensor_node_t* e = (sensor_node_t*)list_get_element_at_index(list, 0);
	// printf("Sensor ID: %" PRIu16 "\n", e->sensor_id);


	return 0;
}