
#ifndef __SPACE_H
#define __SPACE_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct PACKED // 定义一个cpu occupy的结构体
{

    char name[20]; // 定义一个char类型的数组名name有20个元素

    unsigned int user; // 定义一个无符号的int类型的user

    unsigned int nice; // 定义一个无符号的int类型的nice

    unsigned int system; // 定义一个无符号的int类型的system

    unsigned int idle; // 定义一个无符号的int类型的idle

} CPU_OCCUPY;

typedef struct PACKED1 // 定义一个mem occupy的结构体
{

    char name[20]; // 定义一个char类型的数组名name有20个元素

    unsigned long total;

    char name2[20];

    unsigned long free;

} MEM_OCCUPY;
extern float get_disk();
extern float get_memoccupy(MEM_OCCUPY *mem);                    // 获取内存使用率
extern float get_cpuoccupy(CPU_OCCUPY *cpust);                         // CPU使用情况
extern float cal_cpuoccupy(CPU_OCCUPY *o, CPU_OCCUPY *n); // 计算CPU使用率
#endif
