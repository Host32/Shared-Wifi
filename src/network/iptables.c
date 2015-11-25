#include "iptables.h"

int setup_iptables(){
	/*Permitindo pedidos DHCP e DNS de qualquer usuário*/
	system("iptables -t nat -A prerouting_rule -m state --state NEW,ESTABLISHED,RELATED,INVALID -p udp --dport 67 -j ACCEPT");
	system("iptables -t nat -A prerouting_rule -m state --state NEW,ESTABLISHED,RELATED,INVALID -p tcp --dport 67 -j ACCEPT");
	system("iptables -t nat -A prerouting_rule -m state --state NEW,ESTABLISHED,RELATED,INVALID -p udp --dport 53 -j ACCEPT");
	system("iptables -t nat -A prerouting_rule -m state --state NEW,ESTABLISHED,RELATED,INVALID -p tcp --dport 53 -j ACCEPT");
	return 1;
}

int deny_mac(const char* mac){
    return iptables_command("iptables -t nat -D prerouting_rule -m mac --mac-source %s -j RETURN",mac);
}

int allow_mac(const char* mac){
    return iptables_command("iptables -t nat -I prerouting_rule -m mac --mac-source %s -j RETURN",mac);
}
