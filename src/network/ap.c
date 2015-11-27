#include "ap.h"

int setup_ap(){
    system("apt-get install hostapd");
    system("apt-get install havaged");
    system("service network-manager stop");
    system("mv src/conf/hostapd.conf /etc/hostapd/hostapd.conf -f");
    system("mv src/conf/sysctl.conf /etc/sysctl.conf -f");
    system("mv src/conf/rc.local /etc/rc.local -f");
    system("mv src/conf/interfaces /etc/network/interfaces -f");
    system("service hostapd start");
    return 1;
}
