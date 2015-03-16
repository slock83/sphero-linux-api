#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>


//TODO : work on this


int main(int argc, char **argv)
{
	struct sockaddr_rc addr = { 0 };
	int s, status;
	char dest[18] = "68:86:E7:04:56:41";//Sphero Anthony
	//char dest[18] = "68:86:E7:04:6B:3A";//Sphero Luc
	// allocate a socket
	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	// set the connection parameters (who to connect to)
	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = (uint8_t) 1;
	str2ba( dest, &addr.rc_bdaddr );
	// connect to server
	status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
	// send a message
	if( status == 0 ) {
		while(status >= 0)
		{
			sleep(1);
        	status = write(s, "\xFF\xFE\x02\x20\x00\x05\x00\x00\xFF\x00\xD9",11);//LED Bleue
			sleep(1);
			write(s, "\xFF\xFE\x02\x20\x00\x05\xFF\xFF\xFF\x00\xDB",11);//LED blanche
			sleep(1);
			write(s, "\xFF\xFE\x02\x20\x00\x05\xFF\x00\x00\x00\xD9",11);//LED rouge
		}
	}
	if( status < 0 ) perror("uh oh");
	sleep(25);
	close(s);
	return 0;
}
