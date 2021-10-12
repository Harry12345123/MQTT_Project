all:
	gcc mqtt_subscribe.c -o mqtt_subscribe -lpaho-mqtt3c
	gcc mqtt_publish_main.c mqtt_publish_data.c mqtt_publish_manage.c -o mqtt_publish_main -lpaho-mqtt3c -lpthread
