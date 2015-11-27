#include "dhcp.h"

int setup_dhcp(){
    system("apt-get install isc-dhcp-server");
    system("mv src/conf/dhcpd.conf /etc/dhcp/dhcpd.conf -f");
    system("service isc-dhcp-server start");
    return 1;
}
