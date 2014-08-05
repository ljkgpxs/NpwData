/*  NpwData Program
 *  Author  : Ljk
 *  Support : GT Studio
 *  Tester  : Ljk
 *  Date    : 2013-3-5
 */


#ifndef NPWDATA
 #define NPWDATA  1
#endif

#include <stdio.h>
#include <stdlib.h>


#define SER_DEV     "/dev/mtd1" //  Our Serial log device
#define SEEK_NUM    4096      //  Local device's Seek Number
#define SER_NUM     12        //  Serial's long
#define KEY_NUM     8          // SD Key long

/* 用户态结构体 */

struct _userdata {
	char header[128];
	int  key[KEY_NUM];
	int  stat;
	int  ser[SER_NUM];
};


/* 库内部结构体, 不允许修改其内容 */
struct _localdata {
	char header[128];
	int  key[KEY_NUM];
	int  stat;
};


typedef struct _userdata   Urd;
typedef struct _localdata  Ld;

/* 从库的内部获取已初始化的用户态结构体指针
 * 指针指向已初始化的内存区,将返回Urd *类型  */
Urd  * get_user_stc(void);

/* 从库内部获取 Ld(_localdata)已初始化的指针 */
Ld   * get_sys_stc(void);

/* 获取NOAH机器序列号 */
int  * getserial();

/* 初始化NpwData函数库 */
int    initNpw(int);

/* 修改内部结构体,把锁装态调为 加锁*/
int    lockmac();

