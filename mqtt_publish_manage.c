#include "mqtt_publish_manage.h"

S_MQTT_MANAGE s_mqtt_manage;
pthread_mutex_t s_mqtt_manage_mutex;

int init_mqtt_connent_manage()
{
   pthread_mutex_init(&s_mqtt_manage.mutex, NULL);
   s_mqtt_manage.client = NULL;
   return 0;
}

int create_mqtt_connent()
{
    char *address="tcp://localhost:1883";
    char *client_id="publish_client";
    int  rv;
    MQTTClient client;
    MQTTClient_connectOptions conn_opts=MQTTClient_connectOptions_initializer;
    conn_opts.keepAliveInterval=60;
    conn_opts.cleansession=1;

    MQTTClient_create(&client,address,client_id,MQTTCLIENT_PERSISTENCE_NONE,NULL);
    if((rv=MQTTClient_connect(client,&conn_opts))!=MQTTCLIENT_SUCCESS)
    {
       printf("MQTTClient_connect failure:%s\n",strerror(errno));
       return 0;
    }

    set_mqtt_client(client);
    return 0;
}

int set_mqtt_client(MQTTClient client)
{
   pthread_mutex_lock(&s_mqtt_manage.mutex);
   s_mqtt_manage.client = client;
   pthread_mutex_unlock(&s_mqtt_manage.mutex);

   return 0;
}

MQTTClient get_mqtt_client()
{
    MQTTClient mqtt_client;
    pthread_mutex_lock(&s_mqtt_manage.mutex);
    mqtt_client = s_mqtt_manage.client;
    pthread_mutex_unlock(&s_mqtt_manage.mutex);
    return mqtt_client;
}

int destroy_mqtt_connect()
{
    MQTTClient mqtt_client;
    mqtt_client = get_mqtt_client();

    if(mqtt_client != NULL)
    {
        MQTTClient_destroy(&mqtt_client);
    }

    return 0;
}

