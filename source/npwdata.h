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

/* �û�̬�ṹ�� */

struct _userdata {
	char header[128];
	int  key[KEY_NUM];
	int  stat;
	int  ser[SER_NUM];
};


/* ���ڲ��ṹ��, �������޸������� */
struct _localdata {
	char header[128];
	int  key[KEY_NUM];
	int  stat;
};


typedef struct _userdata   Urd;
typedef struct _localdata  Ld;

/* �ӿ���ڲ���ȡ�ѳ�ʼ�����û�̬�ṹ��ָ��
 * ָ��ָ���ѳ�ʼ�����ڴ���,������Urd *����  */
Urd  * get_user_stc(void);

/* �ӿ��ڲ���ȡ Ld(_localdata)�ѳ�ʼ����ָ�� */
Ld   * get_sys_stc(void);

/* ��ȡNOAH�������к� */
int  * getserial();

/* ��ʼ��NpwData������ */
int    initNpw(int);

/* �޸��ڲ��ṹ��,����װ̬��Ϊ ����*/
int    lockmac();

