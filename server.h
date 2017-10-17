#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#define MAX_CONNECTIONS 10
#define MAX_PID 40000 /* this is totally sketchy. I just know that /proc/sys/kernel/pid_max = 32768 */

static int comm_num = 0;
static int sck;
static int addrlen;
static int sockets[MAX_PID]; 

void sigchild_handler(int sig);
int exec_comm_handler(int sck, int conn_num);
void do_listen();