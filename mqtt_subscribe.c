#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include"MQTTClient.h"

int main()
{
    char *address="tcp://localhost:1883";
    char *client_id="client_sub";
    char *payload="mqtt_examples";
    int    rv,i;
    char *ptr=NULL;
    char *topic=NULL;
    int topic_len;
    MQTTClient client;
    MQTTClient_connectOptions conn_opts=MQTTClient_connectOptions_initializer;
    MQTTClient_deliveryToken token;
    MQTTClient_message *receive_msg=NULL;
    conn_opts.keepAliveInterval=60;
    conn_opts.cleansession=1;

    if((rv=MQTTClient_create(&client,address,client_id,MQTTCLIENT_PERSISTENCE_NONE,NULL))<0)
    {
        printf("MQTTClient_create failure:%s\n",strerror(errno));
        return 0;
    }

    printf("MQTTClient_create successfully\n");
    if((rv=MQTTClient_connect(client,&conn_opts))!=MQTTCLIENT_SUCCESS)
    {
        printf("MQTTClient_connect failure:%s\n",strerror(errno));
        return 0;
    }
    printf("MQTTClient_connect successfuly\n");
    MQTTClient_subscribe(client,payload,1);

    while(1)
    {
        if((rv=MQTTClient_receive(client,&topic,&topic_len,&receive_msg,100000))!=MQTTCLIENT_SUCCESS)//最后一个参数是超时时间,单位是毫秒
        {
            printf("MQTTClient_receive failure:%s\n",strerror(errno));
            break;
        }
        printf("MQTTClient_receive successfully\n");
        ptr=receive_msg->payload;
        printf("Topic:%s\nTopic_len:%d\nmsg:",topic,topic_len);
        for(i=0;i<receive_msg->payloadlen;i++)
        {
            putchar(*ptr++);
        }
        printf("\nmsg_len:%d\nmsg_id:%d\n",receive_msg->payloadlen,receive_msg->msgid);
        sleep(3);
    }
    printf("end\n");
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return 0;
}
