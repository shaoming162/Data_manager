#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "datamgr.h"
#include "list.h"

struct data
{
	uint16_t sensor_id;
	uint16_t room_id;
	double running_avg;
	time_t last_modified;
};

// Read from MAP_FILE and populate the list
list_ptr_t initialize_pointer_list( list_ptr_t list )
{
	FILE* fp;
	fp = fopen("room_sensor.map", "r");	// r for read, b for binary
	if(fp == NULL) {
		printf("Couldn't open sensor_data\n");
	    exit(EXIT_FAILURE);
	}
	uint16_t room_id, sensor_id;
	while (!feof(fp)) {
		fscanf(fp, "%" SCNu16 " %" SCNu16, &room_id, &sensor_id);
		printf("%" PRIu16 " %" PRIu16 "\n", room_id, sensor_id);
	}

	return list;
}

// Read data from DATA_FILE and insert data into the list
list_ptr_t read_data( list_ptr_t list ){

}