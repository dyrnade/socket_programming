#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

/* 
#define AF_INET  means IPv4  
This is defined in socket.h already so there is no need to define it here.
*/

const char MESSAGE[] = "A message\n";

int
main(int argc, char *argv[]){
  
  int simpleSocket = 0;
  int simplePort = 0;
  int returnStatus = 0;
  struct sockaddr_in simpleServer;

  /* check whether we got the port or not */
  if (2 != argc) {
    
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(1);

  }

  /* Create TCP Socket */
  simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (simpleSocket == -1) {
    
    fprintf(stderr, "Could not create a socket!!!\n");
    exit(1);

  }
  else {
   
    fprintf(stderr, "Socket created!\n");
  
  } /* End of creation of TCP Socket */


  
  /* Bind the socket */ 

  /* retrieve the port number */
  simplePort = atoi(argv[1]);

  /*
   * set up the address structure
   * use INADDR_ANY to bind to all local addresses
   * note use of htonl() and htons()
   * */
  bzero(&simpleServer, sizeof(simpleServer));
  simpleServer.sin_family = AF_INET;
  simpleServer.sin_addr.s_addr = htonl(INADDR_ANY);
  simpleServer.sin_port = htons(simplePort);

  /* bind to the address and port with our socket */
  returnStatus = bind(simpleSocket,
                      (struct sockaddr *)&simpleServer,
                      sizeof(simpleServer));

  if (returnStatus == 0) {
  
    fprintf(stderr,"Bind completed!\n");
  
  }
  else {
  
    fprintf(stderr, "Could not bind to address!\n");
    close(simpleSocket);
    exit(1);
  } /* End of Binding */

  
  /* Listen the connections */

  /* tell the socket we are ready to accept connections */
  returnStatus = listen(simpleSocket, 5);

  if (returnStatus == -1) {

    fprintf(stderr, "Cannot listen on socket!\n");
    close(simpleSocket);
    exit(1);

  } /* End of Listening the connections*/



  /* Accept and handle the connection requests */
  
  while (1) {
    
    /* set up variables to handle client connections */
    struct sockaddr_in clientName = { 0 };
    int simpleChildSocket = 0;
    int clientNameLength = sizeof(clientName);
    
    /* block on accept function call */
    simpleChildSocket = accept(simpleSocket,
                               (struct sockaddr *)&clientName,
                               &clientNameLength);

    if (simpleChildSocket == -1) {
      
      fprintf(stderr, "Cannot accept connections!!!\n");
      close(simpleSocket);
      exit(1);

    }

    /* handle the connection request */
    /* write out our message to the client */
    send(simpleChildSocket, MESSAGE, strlen(MESSAGE), 0);
    close(simpleChildSocket);

  }
  
  close(simpleSocket);
  return 0;
}
