#include <stdio.h>
#include <inttypes.h>
#include "datamgr.h"
#include "list.h"


// Read from MAP_FILE and populate the list
list_ptr_t initialize_pointer_list( list_ptr_t list )
{
	sensor_node_t* sensor_node = (sensor_node_t*)malloc(sizeof(sensor_node_t));
	// printf("snesor id: %" PRIu16 "  room id %" PRIu16 " running avg: %f last_modified time: %d", sensor_node->sensor_id, sensor_node->room_id, sensor_node->running_avg, sensor_node->last_modified);

	FILE* fp;
	fp = fopen(MAP_FILE, "r");	// r for read
	if(fp == NULL) {
		printf("Couldn't open MAP_FILE\n");
	    exit(EXIT_FAILURE);
	}
	uint16_t room_id, sensor_id;
	while(!feof(fp)) {
		if(fscanf(fp, "%" SCNu16 " %" SCNu16, &room_id, &sensor_id) == 2) {
			// printf("%" PRIu16 " %" PRIu16 "\n", room_id, sensor_id);
			sensor_node->sensor_id = sensor_id;
			sensor_node->room_id = room_id;
			list_insert_at_index(list, sensor_node, 0);
		}
	}

	free(sensor_node);

	return list;
}

// Read data from DATA_FILE and update the sensor_node list
list_ptr_t read_data( list_ptr_t list ){
	FILE* fp;
	fp = fopen(DATA_FILE, "rb");
	if (!fp) {
		printf("Couldn't open DATA_FILE\n");
		exit(EXIT_FAILURE);
	}
	uint16_t sensor_id;
	double temp;
	time_t timestamp;

	while(!feof(fp)) {
		fread(&sensor_id, sizeof(uint16_t), 1, fp);
		printf("sensor id: %" PRIu16 "\t", sensor_id);

		fread(&temp, sizeof(double), 1, fp);
		printf("temperature: %g\t", temp);

		fread(&timestamp, sizeof(time_t), 1, fp);
		printf("timestamp: %ld\n", timestamp);
	}

	// fread(&sensor_id_2, sizeof(uint16_t), 1, fp);
	// printf("sensor id: %" PRIu16 "\n", sensor_id_2);


	return list;
}