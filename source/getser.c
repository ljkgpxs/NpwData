/*  Author :  Ljk
 *  Support : GT Studio
 */

#include "npwdata.h"




int main(int argc, char **argv)
{
	if(argc<3) {
		fprintf(stderr, "Usage :%s [Sys Password] [Info Num]\n"
				"\tInfo Num Include :\n"
				"\t1\tReturn Noah Serial\n"
				"\t2\tReturn Your Personal Password\n", argv[0]);
		return -1;
	}

	if(!initNpw(atoi(argv[1]))) {
		fprintf(stderr, "NpwData Init Failed!!\n");
		return -1;
	}

	Urd *user_stc;
	user_stc = get_user_stc();

	if(atoi(argv[2]) == 1) {
		int i;
		for(i=0; i<SER_NUM; i++)
			printf("%d", user_stc->ser[i]);
	}
	else if(atoi(argv[2]) == 2) {
		int i;
		for(i=0; i<KEY_NUM; i++)
			printf("%c", user_stc->key[i]);
	}
					
	return 0;
}



