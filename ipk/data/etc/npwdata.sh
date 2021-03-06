#! /bin/sh


mmc="/dev/mmcblk0"
dev=0
#mmc="/root/sd"
cat /dev/fb0 >/tmp/11

if [ `cat /var/log/wrt` == 0 ] || [ `cat /var/log/npw` == 0 ]
then
	exit 0
fi


clear  >/dev/tty1
echo >/dev/tty1
echo "Starting NpwData....."  >>/dev/tty1

check()
{
	checkey 599 $mmc >>/dev/tty1 2>>/dev/tty1
	ret=$?
	if [ $ret != 0 ]
	then
		if [ $dev == 1 ]
		then
			echo "Press Enter To Check SD/TF Card" >>/dev/tty1
		else
			echo "Press Rnter To Check Host Device"
		fi
		read -sn1 key  </dev/tty1  
		if [ $? == 0 ]
		then
			if [ $dev == 0 ]
			then
				mmc="/dev/sda"
				dev=1
			else
				mmc="/dev/mmcbulk0"
				dev=0
			fi
			check
			if [ $chk_ret == 0 ]
			then
				echo "Ok Now Start Up!!!!" >/dev/tty1
				sleep 2s
				clear >/dev/tty1
				cat /tmp/11 >/dev/fb0
				rm /tmp/11
				okay=0
			fi
		fi

else
	echo "Ok, Now, Start Up!!!!"  >>/dev/tty1
	sleep 2s
	clear >/dev/tty1
	cat /tmp/11 >/dev/fb0
	rm /tmp/11
	okay=0
fi

}

check
if [ $okay == 0 ]
then
	exit 0
else
	exit 1
fi
