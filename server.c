#include "server.h"

void sigchild_handler(int sig) 
{
  pid_t p;
  int status;

  while ((p=waitpid(-1, &status, WUNTRACED)) != -1)
  {
    printf("Child died!\n");
    printf("pid: %d, sock: %d\n", p, sockets[p]);
    close(sockets[p]);
  }
}

int exec_comm_handler(int sck, int conn_num)
{
  close(0);
  close(1);
  close(2);

  if( dup(sck) != 0 || dup(sck) != 1 || dup(sck) != 2) {
    perror("error duplicating socket for stdin/stdout/stderr");
    exit(1);
  }
  printf("this should now go across the socket...\n");
  execl("./test", "", NULL);
  perror("the execl(3) call failed.");
  exit(1);
}

void do_listen() 
{
  int client;
  pid_t child_pid;
  struct sockaddr_in peer_addr;

  while((client = accept(sck, (struct sockaddr*) &peer_addr, &addrlen )) != -1) {
    printf("got connection\n");
    comm_num++;
    child_pid = fork();
    if( child_pid < 0 ) {
      perror("Error forking");
      exit(3);
    }

    if( child_pid == 0 ) {
      exec_comm_handler(client, comm_num);
    } else {
      printf("pid: %d, sock: %d\n", child_pid, client);
      sockets[child_pid] = client;
    }
  }
}

int main(int argc, char const *argv[])
{
  struct sockaddr_in this_addr, peer_addr;
  unsigned short port = 1337;

  addrlen = sizeof( struct sockaddr_in );
  memset( &this_addr, 0, addrlen);
  memset( &peer_addr, 0, addrlen);

  this_addr.sin_port        = htons(port);
  this_addr.sin_family      = AF_INET;
  this_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  sck = socket( AF_INET, SOCK_STREAM, IPPROTO_IP);
  if(bind( sck, (struct sockaddr*) &this_addr, addrlen ) == -1) {
    perror("cannot bind socket");
    exit(1);
  }
  if (listen(sck, MAX_CONNECTIONS) == -1) {
    perror("error in listen");
    exit(2);
  }

  signal(SIGCHLD, sigchild_handler);

  do_listen();

  exit(0);

  return 0;
}
