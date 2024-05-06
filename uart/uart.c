#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <termios.h>
#include <string.h>

/* 115200, 8, N, 1 */
int uart_setup(int fd)
{
    struct termios options;

    // 获取原有串口配置
    if  (tcgetattr(fd, &options) < 0) {
        return -1;
    }

    // 修改控制模式，保证程序不会占用串口
    options.c_cflag  |=  CLOCAL;

    // 修改控制模式，能够从串口读取数据
    options.c_cflag  |=  CREAD;

    // 不使用流控制
    options.c_cflag &= ~CRTSCTS;

    // 设置数据位
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // 设置奇偶校验位
    options.c_cflag &= ~PARENB;
    options.c_iflag &= ~INPCK; 

    // 设置停止位
    options.c_cflag &= ~CSTOPB;

    // 设置最少字符和等待时间
    options.c_cc[VMIN] = 1;     // 读数据的最小字节数
    options.c_cc[VTIME]  = 0;   //等待第1个数据，单位是10s
    
    // 修改输出模式，原始数据输出
    options.c_oflag &= ~OPOST;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    // 设置波特率
    cfsetispeed(&options, B115200); 
    cfsetospeed(&options, B115200);

    // 清空终端未完成的数据
    tcflush(fd, TCIFLUSH);

    // 设置新属性
    if(tcsetattr(fd, TCSANOW, &options) < 0) {
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int fd;
    int ret;
    unsigned char *uart = "/dev/ttyS0";
    char ch1[2] = {0xA1};
    char ch2[2] = {0xA2};
    char ch3[2] = {0xA3};
    char ch4[2] = {0xA4};
    char ch5[2] = {0xA5};
    char ch6[2] = {0xA6};
    char ch7[2] = {0xA7};
    char ch1f[2] = {0xB1};
    char ch2f[2] = {0xB2};
    char ch3f[2] = {0xB3};
    char ch4f[2] = {0xB4};
    char ch5f[2] = {0xB5};
    char ch6f[2] = {0xB6};
    char ch7f[2] = {0xB7};

    fd = open(uart, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) {
        printf("open dev fail!\n");
        return -1;
    } else {
        fcntl(fd, F_SETFL, 0);
    }

    ret = uart_setup(fd);
    if (ret < 0) {
        printf("uart setup fail!\n");
        close(fd);
        return -1;
    }
	char buff[512];	
	int nread;
		while((nread = read(fd, buff, 2))>0)
		{
                 //printf("\nLen: %d\n",nread);
                 //printf("the card %x\r\n",buff[0]);
                 if(buff[1] == 0x0A){
                 printf("the card %x is working\r\n",buff[0]);
                   switch (buff[0]){
                 case 1:write(fd, &ch1, 1);
                 break;
                 case 2:write(fd, &ch2, 1);
                 break;
                 case 3:write(fd, &ch3, 1);
                 break;
                 case 4:write(fd, &ch4, 1);
                 break;
                 case 5:write(fd, &ch5, 1);
                 break;
                 case 6:write(fd, &ch6, 1);
                 break;
                 case 7:write(fd, &ch7, 1);
                 break;                
                }
                }else if(buff[1] == 0x0F){
                 printf("the card %x is not working 111111111111111111\r\n",buff[0]);
                   switch (buff[0]){
                 case 1:write(fd, &ch1f, 1);
                 break;
                 case 2:write(fd, &ch2f, 1);
                 break;
                 case 3:write(fd, &ch3f, 1);
                 break;
                 case 4:write(fd, &ch4f, 1);
                 break;
                 case 5:write(fd, &ch5f, 1);
                 break;
                 case 6:write(fd, &ch6f, 1);
                 break;
                 case 7:write(fd, &ch7f, 1);
                 break;
                }
                }else{
                 printf("receive uart is error\r\n");
                     }
                  usleep(20000);
		}
        //usleep(50000);
        close(fd);
}

