#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

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
        fflush(stdin);
        printf("\n CARGA DE PATHS \n");
        ruta = cargaRuta();
        rutaValida = validaRuta(ruta);
        if(rutaValida == 0){
           printf("\n");
           printf("\n *** Sintaxis correcta! *** \n");
           guardado = guardaRuta(ruta,paths,&cantidad_de_paths_cargados);
           if(strcmp(guardado,"*** PATH CREADO CON EXITO! ***") == 0){
                printf("\n");
                printf("\n %s \n",guardado);
                printf("\n");
           } else{
                printf("\n");
                printf("\n %s \n",guardado);
                printf("\n");
           }

        } else{
            printf("\n");
            printf("\n x Sintaxis incorrecta x \n");
        }

        do{
            fflush(stdin);
            printf("\n ----------------------------------------------");
            printf("\n - Desea agregar otro path? Ingrese <s/n> : ");
            scanf("%c",&op);
            if(op != 's' && op != 'n'){
                printf("\n x ERROR. INGRESE 's' O 'n' x \n");
            }
        } while(op != 's' && op != 'n');

    } while(op != 'n');

    return 0;
}

char * cargaRuta(){
    static char ruta[128];
    int i;

    printf("\n + Ingrese path: ");
    fgets(ruta,sizeof(ruta),stdin);
    ruta[strcspn(ruta,"\n")] = '\0';
    printf("\n");
    printf("\n - Path generado - \n");

    return ruta;
}



int validaRuta(char *ruta){
    int longitud_path,i,flag = 0,longitud_token;
    char delim[] = "/", *token,copia_ruta[128];

    strcpy(copia_ruta,ruta);

    longitud_path = strlen(copia_ruta);
    if(longitud_path >= 3 && longitud_path <= 128){
        printf("\n * LONGITUD VALIDA * \n");
        if(copia_ruta[0] == '/' && copia_ruta[longitud_path - 1] == '/'){

            token = strtok(copia_ruta,delim);
            while(token != NULL){
                longitud_token = strlen(token);
                for(i = 0; i < longitud_token; i++){
                    if(isalnum(token[i]) == 0){
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0){
                    Sleep(1000);
                    printf("\n * DIRECTORIO CONFORMADO POR CARACTERES ALFANUMERICOS * \n");
                    if(longitud_token >= 1 && longitud_token <= 8){
                            Sleep(1000);
                            printf("\n * DIRECTORIO VALIDO * \n");
                    } else{
                            Sleep(1000);
                            printf("\n x LONGITUD SOBREPASA LOS 8 CARACTERES x \n");
                            flag = 1;
                            break;
                    }

                } else{
                    Sleep(1000);
                    printf("\n x SE HAN DETECTADO CARACTERES NO ALFANUMERICOS x \n");
                    break;
                }

                token = strtok(NULL,delim);
            }

            if(flag == 0){
                return 0;
            } else{
                return 1;
            }

        } else{
            Sleep(1000);
            printf("\n x LA RUTA NO COMIENZA CON O TERMINA CON '/' x \n");
            return 1;
        }

    } else{
        Sleep(1000);
        printf("\n x LONGITUD INVALIDA x \n");
        return 1;
    }

}

char * guardaRuta(char *ruta, struct path *paths, int *cantidad_de_paths_cargados){
    int pos = 0, *niveles,flag = 0;
    static char aviso[50];
    static char copia_ruta[128];

    strcpy(copia_ruta,ruta);

    if(paths[0].niveles == 0){
        strcpy(paths[*cantidad_de_paths_cargados].ruta,copia_ruta);
        niveles = nivelesRuta(copia_ruta);
        paths[*cantidad_de_paths_cargados].niveles = *niveles;
        (*cantidad_de_paths_cargados)++;
        strcpy(aviso,"*** PATH CREADO CON EXITO! ***");
        return aviso;

    } else{

        do{
            if(strcmp(ruta,paths[pos].ruta) == 0){
                flag = 1;
            } else{
                pos++;
            }

        } while(pos < *cantidad_de_paths_cargados && flag == 0);

        if(flag == 1){
            strcpy(aviso,"x EL PATH YA EXISTE x");
        } else{
            strcpy(paths[*cantidad_de_paths_cargados].ruta,copia_ruta);
            niveles = nivelesRuta(ruta);
            paths[*cantidad_de_paths_cargados].niveles = *niveles;
            (*cantidad_de_paths_cargados)++;
            strcpy(aviso,"*** PATH CREADO CON EXITO! ***");
        }

    return aviso;

    }
}

int * nivelesRuta(char *copia_ruta){
    char delim[] = "/", *token,copia[128];
    static int cont_tokens = 0;

    strcpy(copia,copia_ruta);

    token = strtok(copia,delim);
    while(token != NULL){
        cont_tokens++;
        token = strtok(NULL,delim);
    }

    return &cont_tokens;
}

