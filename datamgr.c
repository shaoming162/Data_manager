#include <stdio.h>
// #include <stdlib.h>
#include <inttypes.h>
#include "datamgr.h"
#include "list.h"

// struct sensor_node
// {
// 	uint16_t sensor_id;
// 	uint16_t room_id;
// 	double running_avg;
// 	time_t last_modified;
// };

// Read from MAP_FILE and populate the list
list_ptr_t initialize_pointer_list( list_ptr_t list )
{
	sensor_node_t* sensor_node = (sensor_node_t*)malloc(sizeof(sensor_node_t));
	// printf("snesor id: %" PRIu16 "  room id %" PRIu16 " running avg: %f last_modified time: %d", sensor_node->sensor_id, sensor_node->room_id, sensor_node->running_avg, sensor_node->last_modified);

	FILE* fp;
	fp = fopen(MAP_FILE, "r");	// r for read
	if(fp == NULL) {
		printf("Couldn't open sensor_data\n");
	    exit(EXIT_FAILURE);
	}
	uint16_t room_id, sensor_id;
	while (!feof(fp)) {
		if(fscanf(fp, "%" SCNu16 " %" SCNu16, &room_id, &sensor_id) == 2) {
			// printf("%" PRIu16 " %" PRIu16 "\n", room_id, sensor_id);
			sensor_node->sensor_id = sensor_id;
			sensor_node->room_id = room_id;
			list_insert_at_index(list, sensor_node, 0);
		}
	}

	return list;
}

// Read data from DATA_FILE and update the sensor_node list
list_ptr_t read_data( list_ptr_t list ){

}