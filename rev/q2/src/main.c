#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define usage() puts("q2 <Password>")

#define bad_boy() do { \
		puts("Wrong Password"); \
		exit(-1); \
	} while(0)

#define check(SPTR) do { \
		if (strlen((SPTR))!=14) \
			bad_boy(); \
		if ((SPTR)[0]!= '0' || (SPTR)[1]!= 'x') \
			bad_boy(); \
	} while(0)

#define FLAG(i) ((1l<<(i))-1)

long to_num(char *ptr){
	long result = 0;
	while(*ptr){
		char c = *ptr++;
		if ((c >= '0' &&  c<='9') || (c>='a' && c<='f')){
			result <<= 4;
			result += (c <'A') ? c-'0' : 10 + c-'a';
		} else {
			bad_boy();
		}
	}
	return result;
}

long __attribute__((optimize("O3"))) prng(long curr , int cut){
	int i = 0;
	while((1l<<i) < curr){
		i++;
	}
	unsigned long lower = curr & FLAG(cut);
	unsigned long upper = curr & (FLAG(64 - cut)<<cut);
	lower <<= (i-cut);
	upper >>= (cut);
	return lower | upper;
}

#define good_boy() puts("That's the flag")

int main(int argc , char *argv[]) {
	if (argc < 2){
		usage();
		exit(-2);
	}

	if (strlen(argv[1]) != 54)
		bad_boy();

	char start[6] = {};
	char end[6] = {};
	int i;
	for(i=0 ; i<5 ; i++ ){
		start[i] = argv[1][i];
		end[i] = argv[1][49 + i];
	}
	if (strcmp(start , "d4rk{"))
		bad_boy();

	if (strcmp(end , "}c0de"))
		bad_boy();

	char pass[45] = {};
	for( ; i<49 ; i++ ){
		pass[i-5] = argv[1][i];
	}
	long arr[3] = {};
	char *im = strtok(pass , "-");
	check(im);
	arr[0] = to_num(im + 2);
	int j = 1;
	while((im = strtok(NULL , "-")) != NULL) {
		check(im);
		arr[j++] = to_num(im + 2);
	}
	if (arr[1] != prng(arr[0] , 13)){
		bad_boy();
	}
	if (arr[2] != prng(arr[1] , 29)){
		bad_boy();
	}
	if (arr[2] != 0x6ff76dfeb3f4){
		bad_boy();
	}
	good_boy();
}
