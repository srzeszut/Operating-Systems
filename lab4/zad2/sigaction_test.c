#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int number=0;


void sig_handler(int sig, siginfo_t *info, void *context) {
    printf("Siginfo handler\n");
    printf("Received signal: %d\n", sig);
    printf("PID: %d\n", info->si_pid);
    printf("UID: %d\n", info->si_uid);
    printf("Value: %d\n", info->si_value.sival_int);

}
void reset_handler(int sig, siginfo_t *info, void *context) {
    printf("Reset handler\n");
    printf("Received signal: %d\n", sig);

}
void nodefer_handler(int signo, siginfo_t *info, void *context) {
    printf("Nodefer handler\n");
    printf("number before : %d.\n",number);
    number++;
    if(number<4){
        kill(getpid(),SIGUSR1);
    }
        printf("number after : %d.\n",number);
//    number--;


}
void set_sigaction(struct sigaction sa,void (*handler)(int,siginfo_t *,void *), int flag){
    sigemptyset(&sa.sa_mask);
    sa.sa_flags =flag;
    sa.sa_sigaction = handler;
    sigaction(SIGUSR1,&sa,NULL);
    number=0;
}

void test_resethand(struct sigaction sa){
    set_sigaction(sa, reset_handler,SA_RESETHAND);
    kill(getpid(),SIGUSR1);
    kill(getpid(),SIGUSR1);
}

void test_siginfo(struct sigaction sa){
    set_sigaction(sa, sig_handler,SA_SIGINFO);
    sigval_t sig_val = {2137};
    sigqueue(getpid(),SIGUSR1,sig_val);

}

void test_nodefer(struct sigaction sa){
    printf("With nodefer flag:\n");
    set_sigaction(sa, nodefer_handler,SA_NODEFER);
    kill(getpid(),SIGUSR1);
    printf("\n");

    printf("Without nodefer flag:\n");
    set_sigaction(sa, nodefer_handler,SA_SIGINFO);
    kill(getpid(),SIGUSR1);
    printf("\n");

}

int main() {
    struct sigaction sa;
    printf("SA_SIGINFO test:\n");
    test_siginfo(sa);
    printf("#################################\n");
    printf("SA_NODEFER test:\n");
    test_nodefer(sa);
    printf("#################################\n");
    printf("SA_RESETHAND test:\n");
    test_resethand(sa);



    return 0;
}