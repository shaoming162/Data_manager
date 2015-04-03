#include "list.h"

#ifndef DATAMGR_H_
#define DATAMGR_H_

#define NUM_SENSORS	8
#define NUM_AVG	5

#define MAP_FILE "room_sensor.map"
#define DATA_FILE "sensor_data"
#define LOG_FILE "log"

typedef struct data data_t;

double sensor_temperature[NUM_SENSORS][NUM_AVG];// = {0}; // 2D array to keep the most recent 5 temp for each sensor

// Read from MAP_FILE and populate the list
list_ptr_t initialize_pointer_list( list_ptr_t list );

// Read data from DATA_FILE and insert data into the list
list_ptr_t read_data( list_ptr_t list );

#endif  //DATAMGR_H_