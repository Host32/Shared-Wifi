#include "dhcp.h"

int setup_dhcp(){
    fprintf(stdout, "\nFazendo backup do dhcpd.conf\n");
    system("cp /etc/dhcp/dhcpd.conf src/conf/bkp/dhcpd_bkp_`date +%Y%m%d%H%M%S`.conf");

    fprintf(stdout, "\nAplicando dhcpd.conf\n");
    system("cp src/conf/dhcpd.conf /etc/dhcp/dhcpd.conf -f");

    fprintf(stdout, "\nIniciando servico isc-dhcp-server\n");
    system("service isc-dhcp-server start");
    return 1;
}
