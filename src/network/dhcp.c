#include "dhcp.h"

/**
 * Arquivo de configuracao:
 * /etc/dhcp/dhcpd.conf 
 * TODO: gerar esse arquivo automaticamente

ddns-update-style none;
option domain-name "home";
option domain-name-servers 8.8.8.8.8 , 8.8.4.4;

default-lease-time 600;
max-lease-time 7200;

authoritative;

log-facility local7;

subnet 10.0.0.0 netmask 255.255.255.0 {
  range 10.0.0.2 10.0.0.10;
  option routers 10.0.0.1;
}

 *
 */
int setup_dhcp(){
    system("apt-get install isc-dhcp-server");
    system("service isc-dhcp-server start");
    return 1;
}
