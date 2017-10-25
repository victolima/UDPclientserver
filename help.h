#include <stdio.h>
void help() {
    printf("\n----------------------------------------------------------\n");
    printf("date: (remoto) retornar a data\n");
    printf("time: (remoto) retornar a hora\n");
    printf("nodename: (remoto) retornar o nome do nó\n");
    printf("sysname: (remoto) retornar o nome do sistema\n");
    printf("release: (remoto) retornar a liberação do sistema\n");
    printf("version: (remoto) retornar a versão do sistema\n");
    printf("machine: (remoto) retornar o nome da máquina\n");
    printf("shutdown: (remoto e local) encerrar a execução das aplicações CLIENTE e SERVIDOR\n");
    printf("credits: (remoto) exibir o nome completo de todos os participantes da equipe\n");
    printf("exit: (local) encerrar a execução da aplicação CLIENTE\n");
    printf("help: (local) exibir um auxilio sobre os comandos existentes");
    printf("\n----------------------------------------------------------\n\n");
}