/*  Author : Ljk
 *  Support : GT Studio
 */

#ifndef COM_H
# define COM_H	1
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#ifndef __USE_FILE_OFFSET64
# define __USE_FILE_OFFSET64
#endif

#define __USE_LARGEFILE64
#define _LARGEFILE64_SOURCE

#include <unistd.h>

#define LOCAL_DEV	"/dev/root"

Urd  *user_stc;
Ld   *sys_stc;


