/*  Author :  Ljk
 *  Suppot :  GT Studio
 */



#include "npwdata.h"
#include "common.h"


int read_sd(char *sd_path)
{
	int fd = open(sd_path, O_RDWR);
	if(fd == -1) {
		perror("Open SD Card Error ");
		return -5;
	}
//	printf("Stat %d Fd %d\n", user_stc->stat, fd);
	if(lseek(fd, (__off64_t)-user_stc->stat, SEEK_END) == -1) {
		perror("Set SD Seek ");
//		printf("%d\n", user_stc->stat);
		close(fd);
		return -1;
	}

//	printf("Now  ::   %ld\n", lseek(fd, 0, SEEK_CUR));
	Urd *userdata = (Urd*)malloc(sizeof(Urd));
	if(read(fd, userdata, sizeof(Urd)) == -1) {
		perror("Read Data From SD Error ");
		close(fd);
		return -2;
	}
	if(userdata->stat != user_stc->stat) {
		fprintf(stderr, "Your SD Data Is Bad! %d, %d\n", userdata->stat, user_stc->stat);
		close(fd);
		return -2;
	}

	int i,ret=0;
	for(i=0; i<SER_NUM; i++) {
		if(userdata->ser[i] != user_stc->ser[i]) {
			fprintf(stderr, "Your SD Card Match Your Machine!\n");
			ret = -3;
		}
		if(ret != 0) {
			close(fd);
			return ret;
		}
	}
	close(fd);
	return 0;
}

int pass(char *sd_path)
{
	Ld *sysdata = (Ld*)malloc(sizeof(Ld));;
	int lc_dev = open(LOCAL_DEV, O_RDONLY);
	lseek(lc_dev, -SEEK_NUM, SEEK_END);
	if(read(lc_dev, sysdata, sizeof(Ld)) == -1) {
		perror("Read Local Data Error ");
		close(lc_dev);
		return -4;
	}
	if(sysdata->header[1] != '.') {
		fprintf(stderr,"System Data Is Not Matching\n");
		close(lc_dev);
		return -1;
	}
	if(sysdata->stat == 1) {
		printf("Your Machine Was Locked\nNow , Checking You SD KEY\n");
		if(read_sd(sd_path) != 0) {
			fprintf(stderr, "Your SD Key Is Wrong \n");
			close(lc_dev);
			return 2;
		}
		else {
			printf("Your SD Key Was Passed\n");
			close(lc_dev);
			return 0;
		}
	}
	else {
		printf("You Have Not Locked Your Machine, Your Machine Is Ok!\n");
		return 0;
	}

}





int main(int argc, char **argv)
{
	
	if(argc < 3) {
		printf("Usage : %s [Sys Password] [SD Card Device Path]\n"
				"\tFor Example : %s 100 /dev/sda\n",argv[0], argv[0]);
		return -1;
	}

	if(!initNpw(atoi(argv[1]))) {
		fprintf(stderr, "NpwData Init Failed!\n");
		return -1;
	}

	user_stc = get_user_stc();
//	sys_stc  = get_sys_stc();
	
	printf("Your Noah Serial : ");
	int i;
	for(i=0; i<SER_NUM; i++)
		printf("%d", user_stc->ser[i]);
	printf("\n");

	if(pass(argv[2]) != 0)
		return -1;
	else
		return 0;


}
