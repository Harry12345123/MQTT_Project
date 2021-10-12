#ifndef MQTT_PUBLISH_DATA_H
#define MQTT_PUBLISH_DATA_H

#include "mqtt_publish_manage.h"

int init_mqtt_publish_data_function();

void * CreateMqttClientThread(void *args);
void * SendMqttClientThread(void *args);

#endif // MQTT_PUBLISH_DATA_H
