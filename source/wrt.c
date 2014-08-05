#include "npwdata.h"
#include "common.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	atexit(sync);
	if(argc < 5) {
	       printf("Usage %s [Sys Password] [lock stat] [SD Write stat] [SD Card Device Path]\n", argv[0]);
	       return -1;
	}

	int psd = atoi(argv[1]);
	int need_lock = atoi(argv[2]);
	int wrt_sd = 0;
	int sd_fd = -1;

	if(need_lock > 1 || need_lock < 0) {
		fprintf(stderr, "Unkonw Lock Stat\n");
		return -1;
	}

	if(!initNpw(psd)) {
		fprintf(stderr, "NpwData Init failed\n");
		return -1;
	}

	if(atoi(argv[3])) {
		sd_fd = open(argv[4], O_WRONLY);
		if(sd_fd == -1) {
			perror("Open SD Device Error ");
			return -1;
		}
		wrt_sd = 1;
	}
	else { 
		wrt_sd = 0;
	}

	int local_fd = open(LOCAL_DEV, O_WRONLY);
	if(local_fd == -1) {
		perror("Open Local Device Error");
		return -1;
	}


	sys_stc = get_sys_stc();
	user_stc = get_user_stc();

	if(need_lock)
		lockmac();
	lseek(local_fd, -SEEK_NUM, SEEK_END);
	
	if(write(local_fd, sys_stc, sizeof(Ld)) == -1) {
		perror("Write System Data Error ");
		close(local_fd);
		return -2;
	}

	if(wrt_sd) {
//		printf("USER Stat %d\n", user_stc->stat);
		if(lseek(sd_fd, (__off64_t)-user_stc->stat, SEEK_END) == -1) {
			perror("Set SD Seek Error ");
fprintf(stderr, "--Your SD Card Memory is to large!\n");
			close(sd_fd);
			return -2;
		}
//		printf("Now,   %d  \n", user_stc->stat);

		if(write(sd_fd, user_stc, sizeof(Urd)) == -1){
			perror("Write SD Data Error ");
			close(sd_fd);
			return -2;
		}
	}
	close(local_fd);
	close(sd_fd);
	return 0;
}


