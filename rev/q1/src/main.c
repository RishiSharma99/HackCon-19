#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char pass[19] = {};
char user[1000] = {};
char *ruser = user + sizeof(char)*16;
char  result = 0;
void begin (void) __attribute__((constructor (101)));
void end(void) __attribute__((destructor (102)));
void check(void) __attribute__((destructor (101)));


void begin() {
	pass[0] = 'f'^0x41;
	pass[1] = 'l'^0x41;
	pass[2] = 'a'^0x41;
	pass[3] = 'g'^0x41;
	pass[4] = '{'^0x41;
	pass[5] = 'T'^0x41;
	pass[6] = 'h'^0x41;
	pass[7] = '1'^0x41;
	pass[8] = '5'^0x41;
	pass[9] = '_'^0x41;
	pass[10] = '1'^0x41;
	pass[11] = '5'^0x41;
	pass[12] = '_'^0x41;
	pass[13] = 'C'^0x41;
	pass[14] = 'r'^0x41;
	pass[15] = '4'^0x41;
	pass[16] = 'z'^0x41;
	pass[17] = 'y'^0x41;
	pass[18] = '}'^0x41;
}


void end(){
	int i = 0;
	for(; i<19 ; i++){
		result |= (ruser[i]^pass[i]^0x41);  	
	}
}

void check(){
	char msg[100] = {};
	if (result){
		msg[0] = 'W';
		msg[1] = 'r';
		msg[2] = 'o';
		msg[3] = 'n';
		msg[4] = 'g';
		msg[5] = ' ';
		msg[6] = ',';
		msg[7] = ' ';
		msg[8] = 'P';
		msg[9] = 'a';
		msg[10] = 's';
		msg[11] = 's';
		msg[12] = 'w';
		msg[13] = 'o';
		msg[14] = 'r';
		msg[15] = 'd';
	} else {
		msg[0] = 'F';
		msg[1] = 'l';
		msg[2] = 'a';
		msg[3] = 'g';
		msg[4] = ' ';
		msg[5] = 'a';
		msg[6] = 'f';
		msg[7] = 't';
		msg[8] = 'e';
		msg[9] = 'r';
		msg[10] = ' ';
		msg[11] = '1';
		msg[12] = '6';
		msg[13] = ' ';
		msg[14] = 'b';
		msg[15] = 'y';
		msg[16] = 't';
		msg[17] = 'e';
		msg[18] = 's';
	}
	puts(msg);
}

int main(){
	printf("Password : ");
	fflush(stdout);
	return read(0 , user , 1000);
}
