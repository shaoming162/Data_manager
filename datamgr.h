#include <stdlib.h>
#include "list.h"

#ifndef DATAMGR_H_
#define DATAMGR_H_

#define NUM_SENSORS	8
#define NUM_AVG	5
#define NUM_MEASUREMENTS 8

#define MAP_FILE "room_sensor.map"
#define DATA_FILE "sensor_data"
#define LOG_FILE "log"
#define LINE_LENGTH 5
#define MIN_TEMP 17
#define MAX_TEMP 23

typedef struct sensor_node
{
	uint16_t sensor_id;
	uint16_t room_id;
	double running_avg;
	time_t last_modified;
	double temperature[5];
	int index;
} sensor_node_t;


//double sensor_temperature[NUM_SENSORS][NUM_AVG];// = {0}; // 2D array to keep the most recent 5 temp for each sensor
//double number_measurement[NUM_MEASUREMENTS]; // = {0}; // 1D array to store the number of measurements

// Read from MAP_FILE and populate the list
list_ptr_t initialize_pointer_list( list_ptr_t list );

// Read data from DATA_FILE and update the sensor_node list
list_ptr_t read_data( list_ptr_t list );

#endif  //DATAMGR_H_
