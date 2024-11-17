#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct path{
    char ruta[128];
    int niveles;
};

char * cargaRuta();
int validaRuta(char*);
char * guardaRuta(char*,struct path*,int*);
int * nivelesRuta(char*);

int main(){
    struct path paths[100];
    char *ruta,op,*guardado;
    int rutaValida,cantidad_de_paths_cargados = 0;

    do{
        system("cls");
        ruta = cargaRuta();
        rutaValida = validaRuta(ruta);
        if(rutaValida == 0){
           printf("\n");
           printf("\n *** Sintaxis correcta! *** \n");
           guardado = guardaRuta(ruta,paths,&cantidad_de_paths_cargados);
           if(strcmp(guardado,"*** Path creado con exito! ***") == 0){
                printf("\n");
                printf("%s",guardado);
                printf("\n");
           } else{
                printf("\n");
                printf("%s",guardado);
                printf("\n");
           }

        } else{
            printf("\n");
            printf("\n x Sintaxis incorrecta x \n");
        }

        do{
            fflush(stdin);
            printf("\n - Desea agregar otro path? Ingrese <s/n>");
            scanf("%c",&op);
            if(op != 's' && op != 'n'){
                printf("\n x ERROR. INGRESE 's' O 'n' x \n");
            }
        } while(op != 's' && op != 'n');

    } while(op != 'n');

    return 0;
}
