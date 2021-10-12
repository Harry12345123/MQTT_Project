#ifndef MQTT_PUBLISH_MANAGE_H
#define MQTT_PUBLISH_MANAGE_H

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "MQTTClient.h"

typedef struct
{
    pthread_mutex_t mutex;
    MQTTClient client;

}S_MQTT_MANAGE;

int init_mqtt_connent_manage();
int create_mqtt_connent();
int destroy_mqtt_connect();
int set_mqtt_client(MQTTClient client);
MQTTClient get_mqtt_client();

#endif // MQTT_PUBLISH_MANAGE_H
