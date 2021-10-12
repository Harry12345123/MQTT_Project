#include "mqtt_publish_data.h"
#include <stdio.h>
#include <unistd.h>

int main(){

   init_mqtt_publish_data_function();

   while (1)
   {
      sleep(50);
   }

   return 0;
}
