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
  
    if(strcmp(buffer,"date") == 0){
      printf("%d/%d/%d\n\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
  
    else if (strcmp(buffer,"time") == 0){
      printf("%d:%d:%d\n\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
  
    else if(strcmp(buffer,"nodename") == 0){
      printf("Node name:   %s\n\n", uts.nodename);
    }
  
    else if(strcmp(buffer,"sysname") == 0){
      printf("System name: %s\n\n", uts.sysname);
    }
  
    else if(strcmp(buffer,"release") == 0){
      printf("Release:    %s\n\n", uts.release);
    }
  
    else if(strcmp(buffer,"version") == 0) {
      printf("Version:     %s\n\n", uts.version);
    }
    
    else if(strcmp(buffer,"machine") == 0) {
      printf("Machine:     %s\n\n", uts.machine);
    }
  
    else if(strcmp(buffer,"shutdown") == 0) {
      
    }
  
    else if(strcmp(buffer,"credits") == 0){
      printf("### Versão de terminal linux desenvolvido para a matéria de Redes\n");
      printf("### Copyright by Rafaela Gomes de Miranda e Victo Ferreira Lima\n\n");
    }
  
    else if(strcmp(buffer,"exit") == 0) {
      printf("Encerrando...\n\n");
      exit(EXIT_FAILURE);
    }
  
    else if(strcmp(buffer,"help") == 0) {
      help();
    }
  
    else {
      printf("Comando não encontrado ou invalido\n\n");
    }
  
    bytes_enviados=sendto(socket_servidor, buffer, MAX_SIZE_BUFFER, 0, (struct sockaddr *)&servidor, sizeof(servidor));
  
    bytes_recebidos = recvfrom(socket_servidor, buffer,MAX_SIZE_BUFFER, 0, (struct sockaddr *)&servidor, &tamanho_servidor);
    
    close(socket_servidor); 
  }
  return 0;
}

