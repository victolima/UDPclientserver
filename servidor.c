//=============================================================================
// SERVIDOR.C 
// Exemplo de uso do mecanismo de comunicação por Socket - UDP
// Programa que recebe e envia uma mensagem para outro processo via socket
// Rafaela Gomes de Miranda
// Victo Ferreira Lima
//=============================================================================

#include "./local.h"
#include "./help.h"
#include <sys/utsname.h>
#include <time.h>
main(int argc, char * argv[])
{
  struct utsname uts;
  uname(&uts);

  int socket_servidor, socket_cliente, bytes_recebidos, bytes_enviados;
  struct sockaddr_in servidor, cliente;
  int tamanho_cliente = sizeof(cliente);
  int tamanho_servidor = sizeof(servidor);
  char buffer[MAX_SIZE_BUFFER];

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  printf("------------------------------------------------------\n");
  printf("Servidor aguardando comandos pela porta 6000\n");
  printf("------------------------------------------------------\n");
  
  socket_servidor = socket(AF_INET, SOCK_DGRAM, 0);
  
  bzero(&servidor, sizeof(servidor));
  servidor.sin_family      = AF_INET;
  servidor.sin_port        = htons(atoi(argv[1]));
  servidor.sin_addr.s_addr = htonl(INADDR_ANY);
 
 bind(socket_servidor,(struct sockaddr *)&servidor, tamanho_servidor); 
 
 while (1) {
    bytes_recebidos = recvfrom(socket_servidor, buffer, MAX_SIZE_BUFFER, 0,(struct sockaddr *)&cliente,&tamanho_cliente);
    printf("Comando a ser processado: %s.\n", buffer);

  
    if(strcmp(buffer,"date") == 0){
      //strcpy(buffer, "%d/%d/%d\n\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
      //printf("%d/%d/%d\n\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    }

    else if (strcmp(buffer,"time") == 0){
      //strcpy(buffer, ("%d:%d:%d\n\n", tm.tm_hour, tm.tm_min, tm.tm_sec));
      //printf("%d:%d:%d\n\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
     else if(strcmp(buffer,"nodename") == 0){
      strcpy(buffer, ("Node name:   %s\n\n", uts.nodename));
    }
     else if(strcmp(buffer,"sysname") == 0){
      strcpy(buffer, ("System name: %s\n\n", uts.sysname));
    }
     else if(strcmp(buffer,"release") == 0){
      strcpy(buffer,("Release:    %s\n\n", uts.release));

    }
     else if(strcmp(buffer,"version") == 0) {
      strcpy(buffer,("Version:     %s\n\n", uts.version));
    }

    else if(strcmp(buffer,"machine") == 0) {
      strcpy(buffer,("Machine:     %s\n\n", uts.machine));
    }
     else if(strcmp(buffer,"shutdown") == 0) {
      //close(socket_servidor); 
    }
     else if(strcmp(buffer,"credits") == 0){
      strcpy(buffer,"### Versão de terminal linux desenvolvido para a matéria de Redes\n### Copyright by Rafaela Gomes de Miranda e Victo Ferreira Lima\n\n");
    }
     else if(strcmp(buffer,"exit") == 0) {
      //strcpy(buffer,"Encerrando... \n\n");
      //exit(EXIT_FAILURE);
    }
     else if(strcmp(buffer,"help") == 0) {
      //strcpy(buffer, help());
      //help();
    }
     else {
      strcpy(buffer,"Comando não encontrado ou invalido\n\n");
    }
    bytes_enviados = sendto(socket_servidor, buffer,MAX_SIZE_BUFFER, 0, (struct sockaddr *)&cliente, tamanho_cliente);
 }
 close(socket_servidor);  
 return 0;
}