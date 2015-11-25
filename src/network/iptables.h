#ifndef __IPTABLES__
#define __IPTABLES__

#include <stdio.h>
#include <stdlib.h>

int setup_iptables();

int iptables_command(const char *format, ...);

int deny_mac(const char* mac);

int allow_mac(const char* mac);

#endif
