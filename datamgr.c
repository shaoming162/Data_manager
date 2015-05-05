#include <stdio.h>
#include <inttypes.h>
#include "datamgr.h"
#include "list.h"
#include <stdlib.h>


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
	uint16_t my_room_id, my_sensor_id;
	while(!feof(fp)) {
		int i;
		if(fscanf(fp, "%" SCNu16 " %" SCNu16, &my_room_id, &my_sensor_id) == 2) {
			// printf("%" PRIu16 " %" PRIu16 "\n", room_id, sensor_id);
			sensor_node->sensor_id = my_sensor_id;
			sensor_node->room_id = my_room_id;
			list_insert_at_index(list, sensor_node, i);
			i++;
		}
	}

	free(sensor_node);
	fclose(fp);
	return list;
}

// Read data from DATA_FILE and update the sensor_node list
list_ptr_t read_data( list_ptr_t list ){
	FILE* fp;
	fp = fopen(DATA_FILE, "rb");    //rb open binary file;
	if (!fp) {
		printf("Couldn't open DATA_FILE\n");
		exit(EXIT_FAILURE);
	}
	
	uint16_t my_sensor_id;
	double my_temp;
	time_t my_timestamp;
	int i,j;
	double my_sum;
	int size = list_size(list);
	
	
	fseek(fp, 0, SEEK_SET); //SEEK_SET 	Beginning of file from 0 position;
	sensor_node_t* sensor_node = (sensor_node_t*)malloc(sizeof(sensor_node_t));
	for(i = 0; i < size; i++){
		sensor_node = list_get_element_at_index(list, i);
		sensor_node -> index = 0;
		}
		
	while(!feof(fp)) {
		fread(&my_sensor_id, sizeof(uint16_t), 1, fp);
		//printf("sensor id: %" PRIu16 "\t", sensor_id);		
		fread(&my_temp, sizeof(double), 1, fp);
		//printf("temperature: %g\t", temp);	
		fread(&my_timestamp, sizeof(time_t), 1, fp);
		//printf("timestamp: %ld\n", timestamp);
		
		//make a queue for storing temperature datas
		for(i=0;i<size;i++){
		sensor_node = list_get_element_at_index(list, i);
		if(sensor_node -> sensor_id == my_sensor_id){
			sensor_node -> temperature[sensor_node -> index] = my_temp;
			sensor_node -> index ++;
			if (sensor_node -> index == LINE_LENGTH)           
				sensor_node -> index = 0;
		sensor_node -> last_modified = my_timestamp;
				}}}

	//caculate the average temp for the array;
	for(i = 0;i < size; i++){
		sensor_node = list_get_element_at_index(list, i);
		for(j = 0; j < LINE_LENGTH; j++){
			printf("%f ", sensor_node -> temperature[j]);                
			my_sum += sensor_node -> temperature[j];                       
			}
		sensor_node -> running_avg = my_sum / LINE_LENGTH;              
		//printf("----The average temp is %f", sensor_node -> running_avg); 
		//printf("----The timestamp is %ld\n", sensor_node -> last_modified);
	}
	
	//set the max and min temperature
	for(i = 0;i < size; i++){
		sensor_node = list_get_element_at_index(list, i);
		if(sensor_node -> running_avg > MAX_TEMP){             
			fprintf(stderr, "The temperaure in No.%hd room is too high.\n", sensor_node -> room_id);
			}
		else if(sensor_node -> running_avg < MIN_TEMP){
			fprintf(stderr, "The temperaure in No.%hd room is too low.\n", sensor_node -> room_id);
			fprintf(stderr, "The temperaure in No.%hd room is too low.\n", sensor_node -> room_id);
			}
		}
	free(sensor_node);
	fclose(fp);
	return list;
}
