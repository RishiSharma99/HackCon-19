#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdint.h>


#define seg_fault __asm__("push [0]")
#define ud2 __asm__("ud2")
#define int3 __asm__("int3")
#define div0 __asm__ volatile( \
		"xor cl , cl \n" \
		" div cl \n" \
		: \
		: \
		: "cl" \
		)

#define to_reg(reg , val) __asm__ volatile (\
		"movq "reg" , %0 \n" \
		: \
		: "r" (val) \
		: reg \
		)
#define from_reg(reg , addrs) __asm__ volatile (\
		"movq %0 , "reg"\n" \
		: "=r" (addrs) \
		:: reg \
		)

#define save_addrs(label) to_reg("r15" , label)

#define save_label(label) save_addrs(&&label)
#define save_func(label) save_addrs(label)

#define jmp(label) do { \
		save_label(label); \
		seg_fault; \
	} while (0)
#define call_args2(func , arg1 , arg2) do { \
		save_addrs(func); \
		to_reg("rdi" , arg1); \
		to_reg("rsi" , arg2); \
		seg_fault; \
	}while(0)

#define call(func) do { \
		save_addrs(func);\
		seg_fault; \
	} while (0)


void juggle();
void xor_();
void print();

char *input;
int input_len = 0;

void *fptrs[] = {
	juggle,
	xor_,
	print,
};

unsigned long long flen = sizeof(fptrs)/sizeof(fptrs[0]);

void evil() {
	puts("Wrong String");
}

void next() {
	int3;
	int3;
	int3;
	int3;
	jmp(there);
	__asm__ volatile(".string \"\xeb\xc8\xab\xcd\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\" \n"
					".string \"\xeb\xc8\x40\xcd\xab\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd \" \n"
					".string \"\xeb\xc8\" "
			);
there:
	__asm__ volatile (
				"mov_ins: \n"
				"mov rax , 2283 \n"
				"xor rax , rax \n"
				"jz mov_ins + 3 \n"
				".byte 0xe8"
				::
				: "rax"
			);
	ud2;
	__asm__ volatile(".byte 0xc8");
	unsigned long long ctr;
	from_reg("r14" , ctr);
	if (ctr < flen)
		call(fptrs[ctr]);
	div0;
}


void juggle() {
	int3;
	ud2;
	__asm__ volatile(".byte 0xc9");
	int3;
	int3;
	jmp(there);
	__asm__ volatile(".string \"\xeb\xc8\xab\xc3\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\" \n"
					".string \"\xeb\xc8\x40\xcd\xab\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd \" \n"
					".string \"\xeb\xc3\xc8\" "
			);
there:
	//printf("[+] Before Juggling : %s\n" , input);
	__asm__ volatile (
				"mov_ins1: \n"
				"mov rax , 2283 \n"
				"xor rax , rax \n"
				"jz mov_ins1 + 3 \n"
				".byte 0xe8"
				::
				: "rax"
			);
	ud2;
	__asm__ volatile(".byte 0xc8");
	for(int j = 3 ; j < input_len ; j += 4){
		char temp = input[j-3];
		input[j-3] = input[j-1];
		input[j-1] = temp;
		temp = input[j];
		input[j] = input[j-2];
		input[j-2] = temp;
	}
	//printf("[+] After Juggling : %s\n" , input);
	call(next);
}

void xor_(){
	int3;
	int3;
	int3;
	int3;
	jmp(there);
	__asm__ volatile(".string \"\xeb\xc8\xab\xcd\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\" \n"
					".string \"\xeb\xc8\x40\xcd\xab\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd \" \n"
					".string \"\xeb\xc8\" "
			);
there:
	__asm__ volatile (
				"mov_ins3: \n"
				"mov rax , 2283 \n"
				"xor rax , rax \n"
				"jz mov_ins3 + 3 \n"
				".byte 0xe8"
				::
				: "rax"
			);
	ud2;
	__asm__ volatile(".byte 0xc8");
	char key[] = "\xab\xcd\xef\x41\x23\x31";
	int key_len = sizeof(key);

	for(int j = 0 ; j< input_len ; j++){
		input[j] ^= key[j%key_len];
	}
	call(next);
}

void print() {
	int3;
	int3;
	int3;
	int3;
	jmp(there);
	__asm__ volatile(".string \"\xeb\xc8\xab\xcd\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\" \n"
					".string \"\xeb\xc8\x40\xcd\xab\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd\xdd \" \n"
					".string \"\xeb\xc8\" "
			);
there:
	__asm__ volatile (
				"mov_ins4: \n"
				"mov rax , 2283 \n"
				"xor rax , rax \n"
				"jz mov_ins4 + 3 \n"
				".byte 0xe8"
				::
				: "rax"
			);
	ud2;
	__asm__ volatile(".byte 0xc8");
	char fmt_str[] = "%x";
	for(int j = 0 ; j < input_len ; j++){
		printf(fmt_str , (uint8_t)input[j]);
	}
	puts("");
	call(next);
}

int get_signal(pid_t child){
	siginfo_t sig;
	if (ptrace(PTRACE_GETSIGINFO , child , &sig , &sig) < 0){
		kill(child , SIGKILL);
		exit(1);
	}
	int ret = sig.si_signo;
	return ret;
}

void __attribute__((optimize("O3")))tracer(pid_t child) {
	struct user_regs_struct regs;
	int status;
	int ctr = 0;
	while(wait(&status) > 0){
		if (WIFEXITED(status)){
			exit(3);
		}

		if (WIFSTOPPED(status)) {
			int sig = get_signal(child);
			if(ptrace(PTRACE_GETREGS , child , &regs , &regs) < 0){
				kill(child , SIGKILL);
				exit(1);
			}
			switch(sig) {
				case SIGSEGV:
					regs.rip = regs.r15;
					if (regs.rip == (unsigned long long)next){
						regs.r14 = ctr;
						ctr++;
					}
					break;
				case SIGTRAP:
					break;
				case SIGILL:
					regs.rip += 3;
					break;
				default:
					kill(child, 9);
			}
			ptrace(PTRACE_SETREGS , child , &regs , &regs);
			ptrace(PTRACE_CONT , child , 0 , 0);

		}
	}
}

void tracee() {
	ptrace(PTRACE_TRACEME , 0 , NULL , NULL);

	int3;
	int3;
	int3;
	int3;
	int3;
	int3;
	call_args2(next , 15LL , 29LL);
	jmp(here);
	__asm__(".string \"\xca\xff\xee\xff\xcc\xca\xff\xee\xff\xcc\xca\xff\xee\xff\xcc\xca\xff\xee\xff\xcc\xca\xff\xee\xff\xcc\"");
here:
	evil();
	exit(2);
}

void banner() {
	puts(" _   _                   __  __ _ _             __      _____  __ ");
	puts("| \\ | |                 |  \\/  (_) |            \\ \\    / / _ \\/_ |");
	puts("|  \\| | __ _ _ __   ___ | \\  / |_| |_ ___  ___   \\ \\  / / | | || |");
	puts("| . ` |/ _` | '_ \\ / _ \\| |\\/| | | __/ _ \\/ __|   \\ \\/ /| | | || |");
	puts("| |\\  | (_| | | | | (_) | |  | | | ||  __/\\__ \\    \\  / | |_| || |");
	puts("|_| \\_|\\__,_|_| |_|\\___/|_|  |_|_|\\__\\___||___/     \\/   \\___(_)_|");
	puts("                                                                  ");

}

int main(){
	banner();
	printf("String to encrypt (Max 5000) : ");
	fflush(stdout);
	input = malloc(sizeof(char) * 5000);
	memset(input , 0 , 5000);
	input_len = read(0, input , 5000);
	input[input_len-1] = '\0';
	input_len -= 1;
	printf("Encrypted : ");
	fflush(stdout);
	pid_t child;
	if ((child = fork())) {
		tracer(child);
	} else {
		tracee();
	}
}
