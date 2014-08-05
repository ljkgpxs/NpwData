/*   NpwData  Program   
*    Author : Ljk
*    Date : 2013-2-21
*    
*         GT Studio
*/



#include <string.h>
#include "npwdata.h"



int pwpass = -1;
int initdone;


/* That will return 1 or 0 or other , 1 is pw ok, 0 is password error, other is init error */

void Initall();

int initNpw(int rootpw)
{
	char strings[8] = {"GT Soft"};
	int total,i;
	for(i=0,total=0; i < 7; i++) {
		total += (int)strings[i];
		//printf("%d\n", total);
	}

	if(rootpw != total) {
		pwpass = 0;
		return 0;
	}
	else {
		pwpass = 1;
		Initall();
		return 1;
	}

	return 2;
}

/* All the key,stc in function must use int type, only print user key use the char */


Urd     usermem;
Ld     stcmem;



int * sertokey(int *ser)
{
	int i,t,j;
	int *k = (int *)malloc(sizeof(int)*KEY_NUM);
	for(j=0,i = 3; i < 11; i++,j++) {
		t = ser[i]*ser[i+1]*ser[i+2]*ser[i-1]+ser[i];
		if(t > 122) {
			for(; t > 122; t-=5) {}
			k[j] = t;
		}
		if(t < 97) {
			for(; t < 97; t+=2) {}
			k[j] = t;
		}
		k[j] = t;
	}

	return k;

}


void Initall() {
	int *ser = getserial();
	int i;
	for(i=0;i<SER_NUM;i++) {
		usermem.ser[i] = ser[i];
	}

	memset(usermem.header, '.', 128);
	int *key = sertokey(ser);
	for(i=0; i<KEY_NUM; i++) {
		usermem.key[i] = key[i];
		stcmem.key[i] = key[i];
	}

	usermem.stat = ser[0]*100+ser[1]*10+ser[2]+128*sizeof(int);  // SD Seek Number

	memset(stcmem.header, '.', 128);


	initdone = 1;   // Init Done
}


/*  If Sys PassWord Pass */

int pwps()
{
	if(pwpass != 1)
		return 0;
	else
		return 1;
}

/* User Functions include getserial() and so on */

int * getserial()
{
	if(!pwps()) {
		fprintf(stderr, "Not Init Library!\n");
		return (int *)-1;
	}

	int i;
	int *serial;
	serial = (int *)malloc(sizeof(int)*SER_NUM);
	char c[2] = {1, 0};

	FILE *dev = fopen(SER_DEV, "r");
	fseek(dev, SEEK_NUM, SEEK_SET);
	for(i=0; i < SER_NUM; i++) {
		c[0] = fgetc(dev);
		//printf("C  %c\n", c[0]);
		serial[i] = atoi(c);
	}
	fclose(dev);
//	for(i=0;i<SER_NUM;i++) {
//		printf("Serial %d\n ", serial[i]);
//	}
//	printf("***************Debug........");

	return serial;

}

int lockmac()
{
	if(!pwps()) {
		fprintf(stderr, "Not Init Library!\n");
		return -1;
	}
	stcmem.stat = 1; // That mean : Lock Your Machine
	
	return 1;
}

Urd * get_user_stc(void)
{
	if(!pwps()) {
		fprintf(stderr, "Not Init Library!\n");
		return NULL;
	}
	return &usermem;
}

Ld * get_sys_stc(void)
{
	if(!pwps()) {
		fprintf(stderr, "Not Init Library\n");
		return NULL;
	}

	return &stcmem;
}



int main()
{
	
	if(!initNpw(599)){
		fprintf(stderr,"Pass Word Error\n");
		return 1;
	}

//	Initall();   //  That is the old version usage

	printf("\n\nStart!!\n%s\n", usermem.header);
	int *aaa;
	aaa = sertokey(usermem.ser);
	int i;

	printf("Your NOAH Serial Number is :");
	
	for(i=0;i<SER_NUM; i++)
		printf("%d", usermem.ser[i]);
	printf("\n");

	printf("Your personal password is :");
	for(i=0;i<8;i++) {
		printf("%c ", aaa[i]);
	}
	printf("\n");
	return 0;
}

