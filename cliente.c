//=============================================================================
// CLIENTE.C 
// Exemplo de uso do mecanismo de comunicação por Socket - UDP
// Programa que envia e recebe uma mensagem para outro processo via socket
// Rafaela Gomes de Miranda
// Victo Ferreira Lima
//=============================================================================
#include "./local.h"
#include "./help.h"
#include <sys/utsname.h>
#include <sys/socket.h>
#include <string.h>
#include <time.h>

main(int argc, char *argv[])
{
  struct utsname uts;
  uname(&uts);

  int socket_servidor,bytes_enviados, bytes_recebidos;
  struct sockaddr_in servidor;
  int tamanho_servidor = sizeof(servidor);
  char buffer[MAX_SIZE_BUFFER] = "";

  while(1) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    socket_servidor = socket(AF_INET, SOCK_DGRAM, 0);
    
    bzero(&servidor, sizeof(servidor));
    servidor.sin_family        = AF_INET;
    servidor.sin_port          = htons(atoi(argv[2]));
    servidor.sin_addr.s_addr = inet_addr(argv[1]);
  
    printf("192.168.0.7:6000 @: ");
    gets(buffer);
    
    bytes_enviados = sendto(socket_servidor, buffer, MAX_SIZE_BUFFER, 0, (struct sockaddr *)&servidor, sizeof(servidor));

    bytes_recebidos = recvfrom(socket_servidor, buffer,MAX_SIZE_BUFFER, 0, (struct sockaddr *)&servidor, &tamanho_servidor);

    printf("%s", buffer);

    close(socket_servidor);
  }
  return 0;
}