#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "datamgr.h"
#include "list.h"

// Read from MAP_FILE and populate the list
list_ptr_t initialize_pointer_list( list_ptr_t list )
{
    FILE* fp;
    fp = fopen(MAP_FILE, "r");  // r for read
    if (fp == NULL) {
        printf("Couldn't open MAP_FILE\n");
        exit(EXIT_FAILURE);
    }

    uint16_t room_id, sensor_id;
    sensor_node_t* sensor_node = (sensor_node_t*)malloc(sizeof(sensor_node_t));
    sensor_node->num_of_measurements = 0;

    while (!feof(fp)) {
        if (fscanf(fp, "%" SCNu16 " %" SCNu16, &room_id, &sensor_id) == 2) {
            sensor_node->sensor_id = sensor_id;
            sensor_node->room_id = room_id;
            list_insert_at_index(list, sensor_node, 0);
        }
    }

    free(sensor_node);
    fclose(fp);
    return list;
}

// Read data from DATA_FILE and update the sensor_node list
list_ptr_t read_data( list_ptr_t list ) {
    FILE* fp;
    fp = fopen(DATA_FILE, "rb");    //rb open binary file;
    if (!fp) {
        printf("Couldn't open DATA_FILE\n");
        exit(EXIT_FAILURE);
    }

    uint16_t sensor_id;
    double temp;
    time_t timestamp;
    int i, j;
    double sum = 0;
    sensor_node_t* sensor_node;
    int size = list_size(list);

    fseek(fp, 0, SEEK_SET); //SEEK_SET  Beginning of file from 0 position

    while (!feof(fp)) {
        fread(&sensor_id, sizeof(uint16_t), 1, fp);
        fread(&temp, sizeof(double), 1, fp);
        fread(&timestamp, sizeof(time_t), 1, fp);

        // Update temperature data in list
        for (i = 0; i < size; i++) {
            sensor_node = list_get_element_at_index(list, i);
            if (sensor_node->sensor_id == sensor_id) {
                sensor_node->rencent_measurements[sensor_node->num_of_measurements % NUM_AVG] = temp;
                sensor_node->num_of_measurements++;
                sensor_node->last_modified = timestamp;
                if (sensor_node->num_of_measurements >= 5) {
                    for (j = 0; j < NUM_AVG; j++) {
                        sum += sensor_node->rencent_measurements[j];
                    }
                    sensor_node->running_avg = sum / NUM_AVG;
                    sum = 0;
                    // printf("running_avg = %f\n", sensor_node->running_avg);
                    if (sensor_node->running_avg > SET_MAX_TEMP) {
                        fprintf(stderr, "Room %" PRIu16 " is too hot\n", sensor_node->room_id);
                    }
                    if (sensor_node->running_avg < SET_MIN_TEMP) {
                        fprintf(stderr, "Room %" PRIu16 " is too cold\n", sensor_node->room_id);
                    }
                }
                break;
            }
        }
    }

    fclose(fp);
    return list;
}
