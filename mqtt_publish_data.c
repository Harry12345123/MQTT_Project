#include "mqtt_publish_data.h"

int init_mqtt_publish_data_function()
{
   init_mqtt_connent_manage();

   int ret = 0;
   pthread_t createthread;
   ret = pthread_create(&createthread, NULL, CreateMqttClientThread, NULL);
   if(ret != 0)
   {
      printf("Create CreateMqttClientThread Failed\n");
   }

   pthread_t sendthread;
   ret = pthread_create(&sendthread, NULL, SendMqttClientThread, NULL);
   if(ret != 0)
   {
      printf("Create CreateMqttClientThread Failed\n");
   }

   return 0;
}

void * CreateMqttClientThread(void * args)
{
    pthread_detach(pthread_self());
    MQTTClient mqtt_client;

    while (1)
    {
       mqtt_client = get_mqtt_client();
       if(mqtt_client == NULL)
       {
          create_mqtt_connent();
          usleep(1000*1000);
          continue;
       }
       else
       {
          printf("Create Mqtt Client Success\n");
       }

       usleep(1000*1000);
    }

    return NULL;
}

void *SendMqttClientThread(void * args)
{
    pthread_detach(pthread_self());
    char buf[1024];
    const int time_out=10000;
    char *client_id="publish_client";
    char *topic="mqtt_examples";
    MQTTClient mqtt_client;
    int QOS=1;

    MQTTClient_message publish_msg=MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    publish_msg.qos=QOS;
    publish_msg.retained=0;

    while (1)
    {
        mqtt_client = get_mqtt_client();
        if(mqtt_client == NULL)
        {
            destroy_mqtt_connect();
            continue;
        }

        fgets(buf,sizeof(buf),stdin);
        publish_msg.payload=(void *)buf;
        publish_msg.payloadlen=strlen(buf);

        MQTTClient_publishMessage(mqtt_client,topic,&publish_msg,&token);
        printf("waiting for %d seconds for publication of %s on topic %s for client with CLIENTID :%s\n",time_out/1000,buf,topic,client_id);
        MQTTClient_waitForCompletion(mqtt_client,token,time_out);
        sleep(3);
    }

    return NULL;
}

