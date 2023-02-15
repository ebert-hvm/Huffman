#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tree.h"
#include "heap.h"
#include "hash.h"
#include "compactor.h"
#include "descompactor.h"

int main()
{
    system("clear");
    char ch = 0;
    printf("\033[0;34m");
    printf("_____________________________________________________________________________\n");
    printf("||                                                                         ||\n");
    printf("||                                                                         ||\n");
    printf("||                                                                         ||\n");
    printf("||                                                                         ||\n");
    printf("||                                                                         ||\n");
    printf("||                                                                         ||\n");
    printf("||      ██╗  ██╗██╗   ██╗███████╗███████╗███╗   ███╗ █████╗ ███╗   ██╗     ||\n"); 
    printf("||      ██║  ██║██║   ██║██╔════╝██╔════╝████╗ ████║██╔══██╗████╗  ██║     ||\n"); 
    printf("||      ███████║██║   ██║█████╗  █████╗  ██╔████╔██║███████║██╔██╗ ██║     ||\n"); 
    printf("||      ██╔══██║██║   ██║██╔══╝  ██╔══╝  ██║╚██╔╝██║██╔══██║██║╚██╗██║     ||\n");
    printf("||      ██║  ██║╚██████╔╝██║     ██║     ██║ ╚═╝ ██║██║  ██║██║ ╚████║     ||\n");
    printf("||      ╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚═╝     ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝     ||\n");
    printf("||                                                                         ||\n");
    printf("||                                                                         ||\n");
    printf("||                                                                         ||\n");     
    printf("||                                                                         ||\n");         
    printf("||                                                                         ||\n");                 
    printf("||   Ebert Henrique - Rafael Anacleto - Tiago Beltrão - Ronaldo Cândido    ||\n");         
    printf("||                                                                         ||\n");
    printf("||_________________________________________________________________________||\n\n");
    printf("\033[0;33m");
    printf("--------------------------------INSTRUÇÕES:----------------------------------\n");
    printf("\033[0m");
    printf("(1) - Escreva o caminho do arquivo para compactar em \"file_path.txt\".\n");
    printf("(2) - O arquivo compactado será salvo na mesma pasta com a extensão \".huff\".\n");
    printf("(3) - A opção \"descompactar\" utiliza o arquivo salvo em \"compacted_file_path\" para descompactar\n");
    printf("(4) - O arquivo descompactado será salvo na mesma pasta com o nome original.\n\n");
    printf("Digite qualquer tecla para continuar\n");
    getc(stdin);
    system("clear");
    printf("\033[0;33m");
    printf("-------------------------MENU-------------------------\n\n");
    printf("\033[0m");
    printf("Digite [1] para compactar.\nDigite [2] para descompactar.\nDigite [3] para sair.\n\n");
    printf("Digite: ");
    do
    {
        ch = getc(stdin);;
        if(ch - '0' == 1)
        {
            system("clear");
            compact();
            printf("Retornando para o menu...\n\n");
        }
        if (ch - '0' == 2)
        {
            system("clear");
            descompact();
            printf("Retornando para o menu...\n\n");
        }
        if(ch - '0' == 1 || ch - '0'==2)
        {
            printf("\033[0;33m");
            printf("-------------------------MENU-------------------------\n\n");
            printf("\033[0m");
            printf("Digite [1] para compactar.\nDigite [2] para descompactar.\nDigite [3] para sair.\n\n");
            printf("Digite: ");
        }
    } while (ch - '0' != 3);
    return 0;
}