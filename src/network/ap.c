#include "ap.h"

int setup_ap(){
    system("apt-get install hostapd");
    system("service network-manager stop");
    system("ifconfig eth0 192.168.0.1");
    system("ifconfig eth0 up");
    system("hostapd /etc/hostapd/hostapd.conf");
    return 1;
}
