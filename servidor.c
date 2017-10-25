//=============================================================================
// SERVIDOR.C 
// Exemplo de uso do mecanismo de comunicação por Socket - UDP
// Programa que recebe e envia uma mensagem para outro processo via socket
// Rafaela Gomes de Miranda
// Victo Ferreira Lima
//=============================================================================

#include "./local.h"
main(int argc, char * argv[])
{
  int socket_servidor, socket_cliente, bytes_recebidos, bytes_enviados;
  struct sockaddr_in servidor, cliente;
  int tamanho_cliente = sizeof(cliente);
  int tamanho_servidor = sizeof(servidor);
  char buffer[MAX_SIZE_BUFFER];

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
      strcpy(buffer,"ACK");
      bytes_enviados = sendto(socket_servidor, buffer,MAX_SIZE_BUFFER, 0, (struct sockaddr *)&cliente, tamanho_cliente);

  }

  close(socket_servidor);  

  return 0;
} 
