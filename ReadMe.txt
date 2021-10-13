备注：这份MQTT代码分为发布者和订阅者，其中发布者由三个文件组成mqtt_publish_data.c、mqtt_publish_manage.c、mqtt_publish_main.c。
          订阅者代码则比较简单，直接就是mqtt_subscribe.c组成。

编译文件只需要使用Makefile，直接Make则可以编译出来

特别注意：由于这个项目依赖于第三方MQTT库，所以需要在Ubuntu(或者Linux)上面安装mqtt库。安装流程如下

第一步：git clone https://github.com/eclipse/paho.mqtt.c.git 下载mqtt库
第二步：cd paho.mqtt.c 
第三步:  直接进行Make操作，Make完之后，make install