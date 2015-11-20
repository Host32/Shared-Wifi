#include "ap.h"

int setup_ap(){
    system("apt-get install hostapd");
    system("service network-manager stop");
    system("ifconfig wlan0 192.168.0.1");
    system("ifconfig wlan0 up");
    system("service hostapd /etc/hostapd/hostapd.conf");
    return 1;
}
