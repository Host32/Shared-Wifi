#include "ap.h"

int setup_ap(){
    fprintf(stdout, "\nCriando pasta para arquivos de backup\n");
    system("mkdir src/conf/bkp");

    fprintf(stdout, "\nFazendo backup do hostapd.conf\n");
    system("cp /etc/hostapd/hostapd.conf src/conf/bkp/hostapd_bkp_`date +%Y%m%d%H%M%S`.conf");

    fprintf(stdout, "\nAplicando hostapd.conf\n");
    system("cp src/conf/hostapd.conf /etc/hostapd/hostapd.conf -f");

    fprintf(stdout, "\nFazendo backup do sysctl.conf\n");
    system("cp /etc/sysctl.conf src/conf/bkp/sysctl_bkp_`date +%Y%m%d%H%M%S`.conf");

    fprintf(stdout, "\nAplicando sysctl.conf\n");
    system("cp src/conf/sysctl.conf /etc/sysctl.conf -f");

    fprintf(stdout, "\nFazendo backup do rc.local\n");
    system("cp /etc/rc.local src/conf/bkp/rc_bkp_`date +%Y%m%d%H%M%S`.local");

    fprintf(stdout, "\nAplicando rc.local\n");
    system("cp src/conf/rc.local /etc/rc.local -f");

    fprintf(stdout, "\nFazendo backup do interfaces\n");
    system("cp /etc/network/interfaces src/conf/bkp/interfaces_bkp_`date +%Y%m%d%H%M%S`");

    fprintf(stdout, "\nAplicando interfaces\n");
    system("cp src/conf/interfaces /etc/network/interfaces -f");

    fprintf(stdout, "\nInterrompendo network-manager\n");
    system("service network-manager stop");

    fprintf(stdout, "\nIniciando servico hostapd\n");
    system("service hostapd start");
    return 1;
}
