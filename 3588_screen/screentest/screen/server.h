// cal.h:算术运算相关声明
#ifndef __SERVER_H
#define __SERVER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAC_SIZE 18
#define IP_SIZE 16
extern int get_ip_by_domain(const char *domain, char *ip); // 根据域名获取ip
extern int get_local_mac(const char *eth_inf, char *mac);  // 获取本机MAC地址
extern int get_local_ip(const char *eth_inf, char *ip);    // 获取本机IPd地址
#endif
