#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include "server.h"
#include <stdlib.h>
#include "space.h"
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include "/usr/local/mysql/include/mysql.h"
//#include "/usr/include/mysql/mysql.h"
#include <string.h>

MYSQL mysql; // mysql连接
MYSQL_RES *resMain;
MYSQL_RES *res;
MYSQL_RES *res2;
MYSQL_RES *res3;
MYSQL_RES *res4; // 这个结构代表返回行的一个查询结果集
MYSQL_ROW rowMain;
MYSQL_ROW row;
MYSQL_ROW row2;
MYSQL_ROW row3;
MYSQL_ROW row4; // 一个行数据的类型安全(type-safe)的表示
char *queryMain;
char *query;
char *query2;
char *query3;
char *query4; // 查询语句
float cpuMain, cpuFunction1, cpuFunction2, cpuFunction3, cpuFunction4, cpuFunction5, cpuFunction6;
float memoryMain, memoryFunction1, memoryFunction2, memoryFunction3, memoryFunction4, memoryFunction5, memoryFunction6;
float diskMain, diskFunction1, diskFunction2, diskFunction3, diskFunction4, diskFunction5, diskFunction6;
float emmcMain, emmcFunction1, emmcFunction2, emmcFunction3, emmcFunction4, emmcFunction5, emmcFunction6;
char ip[IP_SIZE];
char ipMain[16];
char ip1[16];
char ip2[16];
char ip3[16];
char ip4[16];
char ipMain_copy[16];
char ip1_copy[16];
char ip2_copy[16];
char ip3_copy[16];
char ip4_copy[16];
char rawMain[16];
char raw1[16];
char raw2[16];
char raw3[16];
char raw4[16];
char mac[MAC_SIZE];
const char ip_str[2] = ".";
const char *test_domain = "www.baidu.com";
const char *test_eth = "ens33";
int fd, nByte;
unsigned char *uart3 = "/dev/ttyS0"; // 要使用的开发板串口
int tMain, t, t2, t3, t4, r, r2, r3, r4;
char numberMain = 0;
char number1 = 0;
char number2 = 0;
char number3 = 0;
char number4 = 0;
char number5 = 0;
char number6 = 0;
char head[4] = {0xEE, 0xB1, 0x12, 0x00};
char page_id[1] = {0x08};
char page_id1[1] = {0x09};
char page_id2[1] = {0x04};
char page_id3[1] = {0x05};
char page_id4[1] = {0x07};
char page_id5[1] = {0x0A};
char page_id6[1] = {0x06};
char cpu_id[2] = {0x00, 0x04};
char cpu_len[2] = {0x00, 0x05};
char cpu_agreement[5] = {0x30, 0x30, 0x30, 0x2E, 0x30};
char emmc_id[2] = {0x00, 0x07};
char emmc_len[2] = {0x00, 0x05};
char emmc_agreement[5] = {0x30, 0x30, 0x2E, 0x30, 0x30};
char disk_id[2] = {0x00, 0x08};
char disk_len[2] = {0x00, 0x05};
char disk_agreement[5] = {0x30, 0x30, 0x2E, 0x30, 0x30};
char servicetype_id[2] = {0x00, 0x09};
char servicetype_len[2] = {0x00, 0x09};
char servicetype_arguement[9] = {0x6D, 0x79, 0x73, 0x71, 0x6C, 0x20, 0x74, 0x63, 0x70};
char ip_id[2] = {0x00, 0x0B};
char ip_len[2] = {0x00, 0x0F};
char ip_argument[15] = {0x31, 0x39, 0x32, 0x2E, 0x31, 0x36, 0x38, 0x2E, 0x20, 0x30, 0x30, 0x2E, 0x20, 0x30, 0x30};
char tail[4] = {0xFF, 0xFC, 0xFF, 0xFF};
//unsigned char mainPanel[46] = {0xEE, 0xB1, 0x12, 0x00, 0x08, 0x00, 0x04, 0x00, 0x05, 0x30, 0x30, 0x2E, 0x30, 0x30, 0x00, 0x07, 0x00, 0x05, 0x30, 0x30, 0x2E, 0x30, 0x30, 0x00, 0x08, 0x00, 0x05, 0x30, 0x30, 0x2E, 0x30, 0x30, 0x00, 0x09, 0x00, 0x05, 0x30, 0x30, 0x2E, 0x30, 0x30, 0X00, 0X0B, 0X00, 0X0F, 0X31, 0X39, 0X32, 0X2E, 0X31, 0X36, 0X38, 0X2E, 0X20, 0X30, 0X30, 0X2E, 0X20, 0X30, 0X30, 0xFF, 0xFC, 0xFF, 0xFF};

char result[100] = {0};
char buf[100] = {0};


void my_system(const char *cmd)
{
    FILE *fp = NULL;

    if( (fp = popen(cmd, "r")) == NULL ) {
        printf("popen error!\n");
        return;
    }

    while (fgets(buf, sizeof(buf), fp)) {
        memcpy(result, buf, 100);
    }

    pclose(fp);
}


struct command_uart
{
	char head[4];
	char page_id[1];
	char cpu_id[2];
	char cpu_len[2];
	char cpu_agreement[5];
	char emmc_id[2];
	char emmc_len[2];
	char emmc_agreement[5];
	char disk_id[2];
	char disk_len[2];
	char disk_agreement[5];
	char servicetype_id[2];
	char servicetype_len[2];
	char servicetype_arguement[9];
	char ip_id[2];
	char ip_len[2];
	char ip_argument[15];
	char tail[4];
}; 
    struct command_uart card ;
	struct command_uart card1;
	struct command_uart card2;
	struct command_uart card3;
	struct command_uart card4;
	struct command_uart card5;
	struct command_uart card6;
void card_init(){	
	//主控板初始化

	memcpy(card.head, head, 4 * sizeof(char));
	memcpy(card.page_id, page_id, 1 * sizeof(char));
	memcpy(card.cpu_id, cpu_id, 2 * sizeof(char));
	memcpy(card.cpu_len, cpu_len, 2 * sizeof(char));
	memcpy(card.cpu_agreement, cpu_agreement, 5 * sizeof(char));
	memcpy(card.emmc_id, emmc_id, 2 * sizeof(char));
	memcpy(card.emmc_len, emmc_len, 2 * sizeof(char));
	memcpy(card.emmc_agreement, emmc_agreement, 5 * sizeof(char));
	memcpy(card.disk_id, disk_id, 2 * sizeof(char));
	memcpy(card.disk_len, disk_len, 2 * sizeof(char));
	memcpy(card.disk_agreement, disk_agreement, 5 * sizeof(char));
	memcpy(card.servicetype_id, servicetype_id, 2 * sizeof(char));
	memcpy(card.servicetype_len, servicetype_len, 2 * sizeof(char));
	memcpy(card.servicetype_arguement, servicetype_arguement, 9 * sizeof(char));
	memcpy(card.ip_id, ip_id, 2 * sizeof(char));
	memcpy(card.ip_len, ip_len, 2 * sizeof(char));
	memcpy(card.ip_argument, ip_argument, 15 * sizeof(char));
	memcpy(card.tail, tail, 4 * sizeof(char));
	write(fd, &card, sizeof(struct command_uart));
	
	// 板卡1初始化
	memcpy(card1.head, head, 4 * sizeof(char));
	memcpy(card1.page_id, page_id1, 1 * sizeof(char));
	memcpy(card1.cpu_id, cpu_id, 2 * sizeof(char));
	memcpy(card1.cpu_len, cpu_len, 2 * sizeof(char));
	memcpy(card1.cpu_agreement, cpu_agreement, 5 * sizeof(char));
	memcpy(card1.emmc_id, emmc_id, 2 * sizeof(char));
	memcpy(card1.emmc_len, emmc_len, 2 * sizeof(char));
	memcpy(card1.emmc_agreement, emmc_agreement, 5 * sizeof(char));
	memcpy(card1.disk_id, disk_id, 2 * sizeof(char));
	memcpy(card1.disk_len, disk_len, 2 * sizeof(char));
	memcpy(card1.disk_agreement, disk_agreement, 5 * sizeof(char));
	memcpy(card1.servicetype_id, servicetype_id, 2 * sizeof(char));
	memcpy(card1.servicetype_len, servicetype_len, 2 * sizeof(char));
	memcpy(card1.servicetype_arguement, servicetype_arguement, 9 * sizeof(char));
	memcpy(card1.ip_id, ip_id, 2 * sizeof(char));
	memcpy(card1.ip_len, ip_len, 2 * sizeof(char));
	memcpy(card1.ip_argument, ip_argument, 15 * sizeof(char));
	memcpy(card1.tail, tail, 4 * sizeof(char));
	write(fd, &card1, sizeof(struct command_uart));
	// 板卡2初始化
	memcpy(card2.head, head, 4 * sizeof(char));
	memcpy(card2.page_id, page_id2, 1 * sizeof(char));
	memcpy(card2.cpu_id, cpu_id, 2 * sizeof(char));
	memcpy(card2.cpu_len, cpu_len, 2 * sizeof(char));
	memcpy(card2.cpu_agreement, cpu_agreement, 5 * sizeof(char));
	memcpy(card2.emmc_id, emmc_id, 2 * sizeof(char));
	memcpy(card2.emmc_len, emmc_len, 2 * sizeof(char));
	memcpy(card2.emmc_agreement, emmc_agreement, 5 * sizeof(char));
	memcpy(card2.disk_id, disk_id, 2 * sizeof(char));
	memcpy(card2.disk_len, disk_len, 2 * sizeof(char));
	memcpy(card2.disk_agreement, disk_agreement, 5 * sizeof(char));
	memcpy(card2.servicetype_id, servicetype_id, 2 * sizeof(char));
	memcpy(card2.servicetype_len, servicetype_len, 2 * sizeof(char));
	memcpy(card2.servicetype_arguement, servicetype_arguement, 9 * sizeof(char));
	memcpy(card2.ip_id, ip_id, 2 * sizeof(char));
	memcpy(card2.ip_len, ip_len, 2 * sizeof(char));
	memcpy(card2.ip_argument, ip_argument, 15 * sizeof(char));
	memcpy(card2.tail, tail, 4 * sizeof(char));
	write(fd, &card2, sizeof(struct command_uart));
	// 板卡3初始化
	memcpy(card3.head, head, 4 * sizeof(char));
	memcpy(card3.page_id, page_id3, 1 * sizeof(char));
	memcpy(card3.cpu_id, cpu_id, 2 * sizeof(char));
	memcpy(card3.cpu_len, cpu_len, 2 * sizeof(char));
	memcpy(card3.cpu_agreement, cpu_agreement, 5 * sizeof(char));
	memcpy(card3.emmc_id, emmc_id, 2 * sizeof(char));
	memcpy(card3.emmc_len, emmc_len, 2 * sizeof(char));
	memcpy(card3.emmc_agreement, emmc_agreement, 5 * sizeof(char));
	memcpy(card3.disk_id, disk_id, 2 * sizeof(char));
	memcpy(card3.disk_len, disk_len, 2 * sizeof(char));
	memcpy(card3.disk_agreement, disk_agreement, 5 * sizeof(char));
	memcpy(card3.servicetype_id, servicetype_id, 2 * sizeof(char));
	memcpy(card3.servicetype_len, servicetype_len, 2 * sizeof(char));
	memcpy(card3.servicetype_arguement, servicetype_arguement, 9 * sizeof(char));
	memcpy(card3.ip_id, ip_id, 2 * sizeof(char));
	memcpy(card3.ip_len, ip_len, 2 * sizeof(char));
	memcpy(card3.ip_argument, ip_argument, 15 * sizeof(char));
	memcpy(card3.tail, tail, 4 * sizeof(char));
	write(fd, &card3, sizeof(struct command_uart));
	// 板卡4初始化
	memcpy(card4.head, head, 4 * sizeof(char));
	memcpy(card4.page_id, page_id4, 1 * sizeof(char));
	memcpy(card4.cpu_id, cpu_id, 2 * sizeof(char));
	memcpy(card4.cpu_len, cpu_len, 2 * sizeof(char));
	memcpy(card4.cpu_agreement, cpu_agreement, 5 * sizeof(char));
	memcpy(card4.emmc_id, emmc_id, 2 * sizeof(char));
	memcpy(card4.emmc_len, emmc_len, 2 * sizeof(char));
	memcpy(card4.emmc_agreement, emmc_agreement, 5 * sizeof(char));
	memcpy(card4.disk_id, disk_id, 2 * sizeof(char));
	memcpy(card4.disk_len, disk_len, 2 * sizeof(char));
	memcpy(card4.disk_agreement, disk_agreement, 5 * sizeof(char));
	memcpy(card4.servicetype_id, servicetype_id, 2 * sizeof(char));
	memcpy(card4.servicetype_len, servicetype_len, 2 * sizeof(char));
	memcpy(card4.servicetype_arguement, servicetype_arguement, 9 * sizeof(char));
	memcpy(card4.ip_id, ip_id, 2 * sizeof(char));
	memcpy(card4.ip_len, ip_len, 2 * sizeof(char));
	memcpy(card4.ip_argument, ip_argument, 15 * sizeof(char));
	memcpy(card4.tail, tail, 4 * sizeof(char));
	write(fd, &card4, sizeof(struct command_uart));
	// 板卡5初始化
	memcpy(card5.head, head, 4 * sizeof(char));
	memcpy(card5.page_id, page_id5, 1 * sizeof(char));
	memcpy(card5.cpu_id, cpu_id, 2 * sizeof(char));
	memcpy(card5.cpu_len, cpu_len, 2 * sizeof(char));
	memcpy(card5.cpu_agreement, cpu_agreement, 5 * sizeof(char));
	memcpy(card5.emmc_id, emmc_id, 2 * sizeof(char));
	memcpy(card5.emmc_len, emmc_len, 2 * sizeof(char));
	memcpy(card5.emmc_agreement, emmc_agreement, 5 * sizeof(char));
	memcpy(card5.disk_id, disk_id, 2 * sizeof(char));
	memcpy(card5.disk_len, disk_len, 2 * sizeof(char));
	memcpy(card5.disk_agreement, disk_agreement, 5 * sizeof(char));
	memcpy(card5.servicetype_id, servicetype_id, 2 * sizeof(char));
	memcpy(card5.servicetype_len, servicetype_len, 2 * sizeof(char));
	memcpy(card5.servicetype_arguement, servicetype_arguement, 9 * sizeof(char));
	memcpy(card5.ip_id, ip_id, 2 * sizeof(char));
	memcpy(card5.ip_len, ip_len, 2 * sizeof(char));
	memcpy(card5.ip_argument, ip_argument, 15 * sizeof(char));
	memcpy(card5.tail, tail, 4 * sizeof(char));
	write(fd, &card5, sizeof(struct command_uart));
	// 板卡6初始化
	memcpy(card6.head, head, 4 * sizeof(char));
	memcpy(card6.page_id, page_id6, 1 * sizeof(char));
	memcpy(card6.cpu_id, cpu_id, 2 * sizeof(char));
	memcpy(card6.cpu_len, cpu_len, 2 * sizeof(char));
	memcpy(card6.cpu_agreement, cpu_agreement, 5 * sizeof(char));
	memcpy(card6.emmc_id, emmc_id, 2 * sizeof(char));
	memcpy(card6.emmc_len, emmc_len, 2 * sizeof(char));
	memcpy(card6.emmc_agreement, emmc_agreement, 5 * sizeof(char));
	memcpy(card6.disk_id, disk_id, 2 * sizeof(char));
	memcpy(card6.disk_len, disk_len, 2 * sizeof(char));
	memcpy(card6.disk_agreement, disk_agreement, 5 * sizeof(char));
	memcpy(card6.servicetype_id, servicetype_id, 2 * sizeof(char));
	memcpy(card6.servicetype_len, servicetype_len, 2 * sizeof(char));
	memcpy(card6.servicetype_arguement, servicetype_arguement, 9 * sizeof(char));
	memcpy(card6.ip_id, ip_id, 2 * sizeof(char));
	memcpy(card6.ip_len, ip_len, 2 * sizeof(char));
	memcpy(card6.ip_argument, ip_argument, 15 * sizeof(char));
	memcpy(card6.tail, tail, 4 * sizeof(char));
	write(fd, &card6, sizeof(struct command_uart));
}

int set_opt(int, int, int, char, int);

void main()
{       
        MYSQL mysql;
        MYSQL_RES *resMain;
        MYSQL_ROW rowMain;
        char *queryMain;
	if ((fd = open(uart3, O_RDWR | O_NOCTTY)) < 0)
		printf("open %s is failed", uart3);
	else
	{
		set_opt(fd, 19200, 8, 'N', 1);
	}
	//主板初始化
	card_init();
	// 主板
	//  server查询
	//  get_ip_by_domain(test_domain, ip);
	//  printf("%s ip: %s\n", test_domain, ip); // 域名IP
	//  get_local_mac(test_eth, mac);
	//  printf("local %s mac: %s\n", test_eth, mac); // MAC
	/*get_local_ip(test_eth, ip);
	printf("local %s ip: %s\n", test_eth, ip); 
	
	CPU_OCCUPY cpu_stat1;
	CPU_OCCUPY cpu_stat2;
	MEM_OCCUPY mem_stat;
	memoryMain = get_memoccupy((MEM_OCCUPY *)&mem_stat);
	printf("%.2f\n", memoryMain);
	mainPanel[27] = (int)memoryMain / 10 + 48;
	mainPanel[28] = (int)memoryMain % 10 + 48;
	mainPanel[30] = (int)(memoryMain * 10) % 10 + 48;
	mainPanel[31] = (int)(memoryMain * 100) % 10 + 48;
	get_cpuoccupy((CPU_OCCUPY *)&cpu_stat1);
	sleep(1);
	get_cpuoccupy((CPU_OCCUPY *)&cpu_stat2);
	cpuMain = cal_cpuoccupy((CPU_OCCUPY *)&cpu_stat1, (CPU_OCCUPY *)&cpu_stat2);
	mainPanel[9] = (int)cpuMain / 10 + 48;
	mainPanel[10] = (int)cpuMain % 10 + 48;
	mainPanel[12] = (int)(cpuMain * 10) % 10 + 48;
	mainPanel[13] = (int)(cpuMain * 100) % 10 + 48;
	diskMain = get_disk();
	printf("内存使用率为：%.2f\n", diskMain);
	mainPanel[36] = (int)diskMain / 10 + 48;
	mainPanel[37] = (int)diskMain % 10 + 48;
	mainPanel[39] = (int)(diskMain * 10) % 10 + 48;
	mainPanel[40] = (int)(diskMain * 100) % 10 + 48;
	for (int i = 0; i < 45; i++)
	{
		printf(" %x", mainPanel[i]);
	}
	write(fd, mainPanel, 45);*/
	
	
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, "127.0.0.1", "root", "", "fe", 0, NULL, 0))
	{
		printf("Error connecting to database: %s", mysql_error(&mysql));
	}else{
		printf("Connected...\n");
	}
	//主控板
         char init_disk[9] = {0x20, 0x20, 0x30, 0x30, 0x2E, 0x30, 0x30, 0x20, 0x20};
        printf("get ip main\r\n");
        queryMain=" select ip from network limit 0,1";
        tMain=mysql_real_query(&mysql,queryMain,(unsigned int)strlen(queryMain));//执行指定为计数字符串的SQL查询。
        if(tMain)
        {
        printf("执行显示时出现异常: %s",mysql_error(&mysql));
        }
	resMain = mysql_store_result(&mysql); // 检索完整的结果集至客户端。
	while (rowMain = mysql_fetch_row(resMain))
	{
		printf("%s\t", rowMain[0]);
		for (t = 0; t < 17; t++)
		{
			ipMain[t] = rowMain[0][t];
			ipMain_copy[t] = rowMain[0][t];
		}
	}
	char *tokenMain;
	tokenMain = strtok(ipMain_copy, ip_str);
	while (tokenMain != NULL)
	{
		int len = strlen(tokenMain);
		// printf("len is:%d/n",len);
		if (len < 3)
		{
			switch (len)
			{
			case 1:
				ipMain[2 + 4 * numberMain] = tokenMain[0];
				ipMain[1 + 4 * numberMain] = 0x20;
				ipMain[0 + 4 * numberMain] = 0x20;
				break;
			case 2:
				ipMain[2 + 4 * numberMain] = tokenMain[1];
				ipMain[1 + 4 * numberMain] = tokenMain[0];
				ipMain[0 + 4 * numberMain] = 0x20;
				break;
			}
		}
		tokenMain = strtok(NULL, ip_str);
		ipMain[3 + 4 * numberMain] = 0x2E;
		numberMain++;
	}
	memcpy(card.ip_argument, ipMain, 15 * sizeof(char));
        //memcpy(card.servicetype_arguement, init_disk, 9 * sizeof(char));
        //main card  cpu
        my_system("top -bn 1 -i -c | sed -n '8p' | awk '{print $9}' ");
        double maincardcpu = atof(result);
        printf("main card cpu: %f\n", maincardcpu);
        char maincpu_agreement[5];
        memcpy(maincpu_agreement, cpu_agreement, 5 * sizeof(char));
        if(maincardcpu >= 0 && maincardcpu < 10){
        maincpu_agreement[2] = result[0];
        maincpu_agreement[4] = result[2];
        }else if(maincardcpu >= 10 && maincardcpu < 100){
        maincpu_agreement[1] = result[0];
        maincpu_agreement[2] = result[1];
        maincpu_agreement[4] = result[3];
        }else{
        maincpu_agreement[0] = result[0];
        maincpu_agreement[1] = result[1];
        maincpu_agreement[2] = result[2];
        maincpu_agreement[4] = result[4];
        }
        memcpy(card.cpu_agreement, maincpu_agreement, 5 * sizeof(char));
	//main card emmc
        my_system("df -h | grep /dev/mmcblk0p4 | cut -d ' ' -f 27-27");
        printf("main card emmc: %s\n", result);
        char mainemmc_agreement[5];
        memcpy(mainemmc_agreement, emmc_agreement, 5 * sizeof(char));
        if(result[1] == 0x25){
        mainemmc_agreement[1] = result[0];
        }else{
	mainemmc_agreement[0] = result[0];
	mainemmc_agreement[1] = result[1];
        }
	memcpy(card.emmc_agreement, mainemmc_agreement, 5 * sizeof(char));
        //main card memory
        my_system("free -m | grep Mem | cut -d ' ' -f 13-14");
        int cardmemorytotal = atoi(result);
        my_system("free -m | grep Mem | cut -d ' ' -f 22-23");
        int cardmemoryuse = atoi(result);
        float cardmemory = (float)cardmemoryuse/cardmemorytotal;
        printf("main card memory : %.2f\n", cardmemory);
        char maindisk_agreement[5];
        memcpy(maindisk_agreement, disk_agreement, 5 * sizeof(char));
        maindisk_agreement[0] = (int)cardmemory/10 + 48;
        maindisk_agreement[1] = (int)cardmemory%10 + 48;
        maindisk_agreement[3] = (int)(cardmemory * 10)%10 + 48;
        maindisk_agreement[4] = (int)(cardmemory * 100)%10 + 48;
        memcpy(card.disk_agreement, maindisk_agreement, 5 * sizeof(char));
        //main card cipan
        my_system("df -h | grep /dev/disk/by-partlabel/rootfs | cut -d ' ' -f 12-12");
        printf("main card disk: %s\n", result);
        if(result[1] == 0x25){
        init_disk[3] = result[0];
        }else{
	init_disk[2] = result[0];
	init_disk[3] = result[1];
        }
        memcpy(card.servicetype_arguement, init_disk, 9 * sizeof(char));	

	write(fd, &card, sizeof(struct command_uart)); 

	// 取板卡1ip
        printf("get ip 1\r\n");
	query = "select ip from network where network.macAddress='72:75:58:e3:2a:07'";
	t = mysql_real_query(&mysql, query, (unsigned int)strlen(query)); // 执行指定为计数字符串的SQL查询。
	if (t)
	{
		printf("执行显示时出现异常: %s", mysql_error(&mysql));
	}
	res = mysql_store_result(&mysql); // 检索完整的结果集至客户端。
	while (row = mysql_fetch_row(res))
	{
		printf("%s\t", row[0]);
		for (t = 0; t < 17; t++)
		{
			ip1[t] = row[0][t];
			ip1_copy[t] = row[0][t];
		}
	}
	char *token;
	token = strtok(ip1_copy, ip_str);
	while (token != NULL)
	{
		int len = strlen(token);
		// printf("len is:%d/n",len);
		if (len < 3)
		{
			switch (len)
			{
			case 1:
				ip1[2 + 4 * number1] = token[0];
				ip1[1 + 4 * number1] = 0x20;
				ip1[0 + 4 * number1] = 0x20;
				break;
			case 2:
				ip1[2 + 4 * number1] = token[1];
				ip1[1 + 4 * number1] = token[0];
				ip1[0 + 4 * number1] = 0x20;
				break;
			}
		}
		token = strtok(NULL, ip_str);
		ip1[3 + 4 * number1] = 0x2E;
		number1++;
	}
	memcpy(card1.ip_argument, ip1, 15 * sizeof(char));	
        //card 1 cpu
        my_system("ansible -m shell -a \"top -bn 1 -i -c | sed -n '8p' | cut -d ' ' -f 25-26\" host1");
        printf("ansible card1 cpu: %s\n", result);
        char cpu1_agreement[5];
        memcpy(cpu1_agreement, cpu_agreement, 5 * sizeof(char));
        if(result[3] == 0x0A){
        cpu1_agreement[1] = result[0];
        cpu1_agreement[3] = result[2];
        }else{
        cpu1_agreement[0] = result[0];
        cpu1_agreement[1] = result[1];
        cpu1_agreement[3] = result[3];
        }
        memcpy(card1.cpu_agreement, cpu1_agreement, 5 * sizeof(char));
	//card 1 emmc
        my_system("ansible -m shell -a \"df -h | grep /dev/mmcblk1p9 | cut -d ' ' -f 8-9\" host1");
        printf("ansible card1 emmc: %s\n", result);
        char emmc1_agreement[5];
        memcpy(emmc1_agreement, emmc_agreement, 5 * sizeof(char));
        if(result[3] == 0x0A){
        emmc1_agreement[1] = result[1];
        }else{
	emmc1_agreement[0] = result[1];
	emmc1_agreement[1] = result[2];
        }
	memcpy(card1.emmc_agreement, emmc1_agreement, 5 * sizeof(char));
        //card 1 memory
        my_system("ansible -m shell -a \"free -m | grep Mem | cut -d ' ' -f 12-16\" host1");
        int card1memorytotal = atoi(result);
        my_system("ansible -m shell -a \"free -m | grep Mem | cut -d ' ' -f 21-24\" host1");
        int card1memoryuse = atoi(result);
        float card1memory = (float)card1memoryuse/card1memorytotal;
        printf("ansible card1 memory : %.2f\n", card1memory);
        char disk1_agreement[5];
        memcpy(disk1_agreement, disk_agreement, 5 * sizeof(char));
        disk1_agreement[0] = (int)card1memory/10 + 48;
        disk1_agreement[1] = (int)card1memory%10 + 48;
        disk1_agreement[3] = (int)(card1memory * 10)%10 + 48;
        disk1_agreement[4] = (int)(card1memory * 100)%10 + 48;
        memcpy(card1.disk_agreement, disk1_agreement, 5 * sizeof(char));

	write(fd, &card1, sizeof(struct command_uart));

	// 取板卡2ip
        printf("get ip 2\r\n");
	query2 = "select ip from network where network.macAddress='00:0a:35:00:01:22'";
	t2 = mysql_real_query(&mysql, query2, (unsigned int)strlen(query2)); // 执行指定为计数字符串的SQL查询。
	if (t2)
	{
		printf("执行显示时出现异常: %s", mysql_error(&mysql));
	}
	res2 = mysql_store_result(&mysql); // 检索完整的结果集至客户端。
	while (row2 = mysql_fetch_row(res2))
	{
		printf("%s\t", row2[0]);
		for (t2 = 0; t2 < 17; t2++)
		{
			ip2[t2] = row2[0][t2];
			ip2_copy[t2] = row2[0][t2];
		}
	}

	char *token2;
	token2 = strtok(ip2_copy, ip_str);
	while (token2 != NULL)
	{
		int len = strlen(token2);
		 printf("len is:%d/n",len);
		if (len < 4)
		{
			switch (len)
			{
			case 1:
				ip2[2 + 4 * number2] = token2[0];
				ip2[1 + 4 * number2] = 0x20;
				ip2[0 + 4 * number2] = 0x20;
				break;
			case 2:
				ip2[2 + 4 * number2] = token2[1];
				ip2[1 + 4 * number2] = token2[0];
				ip2[0 + 4 * number2] = 0x20;
				break;
                         case 3:
                                ip2[2 + 4 * number2] = token2[2];
                                ip2[1 + 4 * number2] = token2[1];
                                ip2[0 + 4 * number2] = token2[0];
                                break;
			}
		}
	
	//	for (int n = 0; n < len; n++)
	//	{
	//		printf("%d\n", token[n]);
	//	}
                token2 = strtok(NULL, ip_str);
                ip2[3 + 4 * number2] = 0x2E;
		number2++;
	}
	memcpy(card2.ip_argument, ip2, 15 * sizeof(char));
	write(fd, &card2, sizeof(struct command_uart));
	// 取板卡3ip
        printf("get ip 3\r\n");
	query3 = " select ip from network where network.macAddress='b6:a5:8c:5e:31:a7'";
	t3 = mysql_real_query(&mysql, query3, (unsigned int)strlen(query3)); // 执行指定为计数字符串的SQL查询。
	if (t3)
	{
		printf("执行显示时出现异常: %s", mysql_error(&mysql));
	}
	res3 = mysql_store_result(&mysql); // 检索完整的结果集至客户端。
	while (row3 = mysql_fetch_row(res3))
	{
		printf("%s\t", row3[0]);
		for (t3 = 0; t3 < 17; t3++)
		{
			ip3[t3] = row3[0][t3];
			ip3_copy[t3] = row3[0][t3];
		}
	}

	char *token3;
	token3 = strtok(ip3_copy, ip_str);
	while (token3 != NULL)
	{
		int len = strlen(token3);
		// printf("len is:%d/n",len);
		if (len < 3)
		{
			switch (len)
			{
			case 1:
				ip3[2 + 4 * number3] = token3[0];
				ip3[1 + 4 * number3] = 0x20;
				ip3[0 + 4 * number3] = 0x20;
				break;
			case 2:
				ip3[2 + 4 * number3] = token3[1];
				ip3[1 + 4 * number3] = token3[0];
				ip3[0 + 4 * number3] = 0x20;
				break;
			}
		}
		token3 = strtok(NULL, ip_str);
		ip3[3 + 4 * number3] = 0x2E;
		/*for (int n = 0; n < 4; n++)
		{
			printf("%d\n", ip1[n + 4 * number3]);
		}*/
		number3++;
	}
	memcpy(card3.ip_argument, ip3, 15 * sizeof(char));
        //card 3 cpu
        my_system("ansible -m shell -a \"top -bn 1 -i -c | sed -n '8p' | awk '{print \\$9}'\" host3");
        double card3cpu = atof(result);
        printf("ansible card3 cpu: %f\n", card3cpu);
        char cpu3_agreement[5];
        memcpy(cpu3_agreement, cpu_agreement, 5 * sizeof(char));
        if(card3cpu >= 0 && card3cpu < 10){
        cpu3_agreement[2] = result[0];
        cpu3_agreement[4] = result[2];
        }else if(card3cpu >= 10 && card3cpu < 100){
        cpu3_agreement[1] = result[0];
        cpu3_agreement[2] = result[1];
        cpu3_agreement[4] = result[3];
        }else{
        cpu3_agreement[0] = result[0];
        cpu3_agreement[1] = result[1];
        cpu3_agreement[2] = result[2];
        cpu3_agreement[4] = result[4];
        }
        memcpy(card3.cpu_agreement, cpu3_agreement, 5 * sizeof(char));
	//card 3 emmc
        my_system("ansible -m shell -a \"df -h | grep /dev/mmcblk0p2 | cut -d ' ' -f 11-11\" host3");
        printf("ansible card3 emmc: %s\n", result);
        char emmc3_agreement[5];
        memcpy(emmc3_agreement, emmc_agreement, 5 * sizeof(char));
        if(result[1] == 0x25){
        emmc3_agreement[1] = result[0];
        }else{
	emmc3_agreement[0] = result[0];
	emmc3_agreement[1] = result[1];
        }
	memcpy(card3.emmc_agreement, emmc3_agreement, 5 * sizeof(char));
        //card 3 memory
        my_system("ansible -m shell -a \"free -m | grep Mem | cut -d ' ' -f 12-16\" host3");
        int card3memorytotal = atoi(result);
        my_system("ansible -m shell -a \"free -m | grep Mem | cut -d ' ' -f 20-24\" host3");
        int card3memoryuse = atoi(result);
        float card3memory = (float)card3memoryuse/card3memorytotal;
        printf("ansible card3 memory : %.2f\n", card3memory);
        char disk3_agreement[5];
        memcpy(disk3_agreement, disk_agreement, 5 * sizeof(char));
        disk3_agreement[0] = (int)card3memory/10 + 48;
        disk3_agreement[1] = (int)card3memory%10 + 48;
        disk3_agreement[3] = (int)(card3memory * 10)%10 + 48;
        disk3_agreement[4] = (int)(card3memory * 100)%10 + 48;
        memcpy(card3.disk_agreement, disk3_agreement, 5 * sizeof(char));
	write(fd, &card3, sizeof(struct command_uart));

	// 取板卡4ip
        printf("get ip 4\r\n");
	query4 = " select ip from network limit 0,1";
	t4 = mysql_real_query(&mysql, query4, (unsigned int)strlen(query4)); // 执行指定为计数字符串的SQL查询。
	if (t4)
	{
		printf("执行显示时出现异常: %s", mysql_error(&mysql));
	}
	res4 = mysql_store_result(&mysql); // 检索完整的结果集至客户端。
	while (row4 = mysql_fetch_row(res4))
	{
		printf("%s\t", row4[0]);
		for (t4 = 0; t4 < 17; t4++)
		{
			ip4[t4] = row4[0][t4];
			ip4_copy[t4] = row4[0][t4];
		}
	}

	char *token4;
	token4 = strtok(ip4_copy, ip_str);
	while (token4 != NULL)
	{
		int len = strlen(token4);
		// printf("len is:%d/n",len);
		if (len < 3)
		{
			switch (len)
			{
			case 1:
				ip4[2 + 4 * number4] = token4[0];
				ip4[1 + 4 * number4] = 0x20;
				ip4[0 + 4 * number4] = 0x20;
				break;
			case 2:
				ip4[2 + 4 * number4] = token4[1];
				ip4[1 + 4 * number4] = token4[0];
				ip4[0 + 4 * number4] = 0x20;
				break;
			}
		}
		token4 = strtok(NULL, ip_str);
		ip4[3 + 4 * number4] = 0x2E;
		/*for (int n = 0; n < 4; n++)
		{
			printf("%d\n", ip1[n + 4 * number4]);
		}*/
		number4++;
	}

	memcpy(card4.ip_argument, ip4, 15 * sizeof(char));
	write(fd, &card4, sizeof(struct command_uart));

	mysql_free_result(res); // 释放结果集使用的内存。
	mysql_free_result(res2);
	mysql_free_result(res3);
	mysql_free_result(res4);
	mysql_close(&mysql);
	close(fd);
}
int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio, oldtio;
	if (tcgetattr(fd, &oldtio) != 0)
	{ // 检测串口是否可用
		perror("SetupSerial 1");
		return -1;
	}
	bzero(&newtio, sizeof(newtio));
	newtio.c_cflag |= CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;

	switch (nBits) // 设置数据位
	{
	case 7:
		newtio.c_cflag |= CS7;
		break;
	case 8:
		newtio.c_cflag |= CS8;
		break;
	}

	switch (nEvent) // 设置检验位
	{
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E':
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':
		newtio.c_cflag &= ~PARENB;
		break;
	}

	switch (nSpeed) // 设置波特率
	{
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		break;
	case 19200:
		cfsetispeed(&newtio, B19200);
		cfsetospeed(&newtio, B19200);
		break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		break;
	case 460800:
		cfsetispeed(&newtio, B460800);
		cfsetospeed(&newtio, B460800);
		break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	}
	if (nStop == 1) // 设置停止位
		newtio.c_cflag &= ~CSTOPB;
	else if (nStop == 2)
		newtio.c_cflag |= CSTOPB;
	newtio.c_cc[VTIME] = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(fd, TCIFLUSH);
	if ((tcsetattr(fd, TCSANOW, &newtio)) != 0) // 设置串口参数
	{
		perror("com set error");
		return -1;
	}

	printf("set done!\n\r");
	return 0;
}
