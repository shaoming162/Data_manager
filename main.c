#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include "datamgr.h"

_Static_assert(SET_MIN_TEMP, "SET_MIN_TEMP is not set.");
_Static_assert(SET_MAX_TEMP, "SET_MAX_TEMP is not set.");
_Static_assert(SET_MIN_TEMP < SET_MAX_TEMP, "SET_MIN_TEMP should be smaller than SET_MAX_TEMP.");

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
    int i;
    for (i = 0; i < NUM_AVG; i++) {
        ((sensor_node_t*)*dest_element)->rencent_measurements[i] = ((sensor_node_t*)src_element)->rencent_measurements[i];
    }
    ((sensor_node_t*)*dest_element)->num_of_measurements = ((sensor_node_t*)src_element)->num_of_measurements;
}


/*
 * Clean up element, including freeing memory if needed
 */
void element_free(element_ptr_t *element)
{
    free(*element);
    *element = NULL;
}

/*
 * Print 1 element to stdout.
 */
void element_print(element_ptr_t element)
{
    printf("Sensor ID: %" PRIu16 " Room ID: %" PRIu16 " Avg Temp: %g Last modified: %ld \n", ((sensor_node_t*)element)->sensor_id, ((sensor_node_t*)element)->room_id, ((sensor_node_t*)element)->running_avg, (long)((sensor_node_t*)element)->last_modified);
}

/*
 * Compare two element elements; returns -1, 0 or 1
 */
int element_compare(element_ptr_t x, element_ptr_t y)
{
    return 0;
}

int main(int argc, char const *argv[])
{
    list_ptr_t list = list_create( &element_copy, &element_free, &element_compare, &element_print );
    initialize_pointer_list(list);
    read_data(list);

    list_free(&list);

    return 0;
}
