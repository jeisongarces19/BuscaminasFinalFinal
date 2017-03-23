#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct casilla{// Estructura tipo casilla(char,char,int).\nHecho por Jeison Fernando Garces Castañeda\n
    char etiqueta;
    char tipo;
    int Minas;

};
typedef struct casilla tipocasilla;
int tableroterminado(int filas,int columnas,tipocasilla **matriz,int minas);

tipocasilla **CrearMatriz(int filas,int columnas){
    tipocasilla **matriz=(tipocasilla **)malloc((filas+2) * sizeof(tipocasilla *));
    int i;
    for(i=0;i<filas+2;i++){
        matriz[i]=((tipocasilla *)malloc((columnas+2) * sizeof(tipocasilla)));
    }
    return matriz;
}

void llenar_tablero(int filas,int columnas,tipocasilla **matriz){
  int i;
  for(i=0;i<filas+2;i++){
    int j;
    for(j=0;j<columnas+2;j++){
      matriz[i][j].etiqueta='#';
      matriz[i][j].tipo='c';
      matriz[i][j].Minas=0;
    }
  }
  //colocar un numero x, fila arriba y abajo.
  int i2;
  for(i2=0;i2<filas+2;i2++){
        matriz[0][i2].Minas=(filas+1);//colocar en la fila 0 , un x numero, mayor que la fila.
  }
  int j2;
  for(j2=0;j2<filas+2;j2++){
        matriz[filas+1][j2].Minas=(filas+1);//colocar en la ultima fila, un x numero, mayor que la fila.
  }
  int i3;//colocar un numero x, columna arriba y columna.
  for(i3=1;i3<columnas+1;i3++){
        matriz[i3][0].Minas=(columnas+1);//colocar en la columna 0, un x numero, mayor que la columna.
  }
  int j3;
  for(j3=1;j3<columnas+1;j3++){
        matriz[j3][columnas+1].Minas=(columnas+1);//colocar en la ultima columna, un x numero, mayor que la columna.
  }
}

void colocarminas(int filas,int columnas,tipocasilla **matriz,int minas){//x=x-1,10=11,25
    int posfila;
    int poscolumna;
    while(minas>0){
        posfila=1+rand()% filas;
        poscolumna=1+rand()% columnas;
        if(matriz[posfila][poscolumna].tipo=='c'){
            matriz[posfila][poscolumna].tipo='M';
            minas--;
        }
    }
}

void imprimir_tablero(int filas,int columnas,tipocasilla **matriz){
    int w=1;
    int t;
    printf("   ");
    for(t=1;t<columnas+1;t++){//numeros de arriba
        printf("  %d ",t);
    }
    while(w<filas+1){
        int k=1;
        printf("\n");
        printf(" %d ",w);//numeros al lado izquierdo
        while(k<columnas+1){
            printf("|");
            printf(" %c ",matriz[w][k].etiqueta);
            //printf(" %d ",matriz[w][k].Minas);
            //printf(" %c ",matriz[w][k].tipo);
            k++;
        }
        printf("|");
        //printf(" %d",w);//numeros al lado derecho
        printf("\n");
        w++;
    }
}

void ayudadminas(int filas,int columnas,tipocasilla **matriz,int minas){
    int fila=filas+1;
    int columna=columnas+1;
    int i3=1;
    while(i3<fila){
      int j3=1;
      while(j3<columna){
        if(matriz[i3][j3].tipo=='c'){
            if(matriz[i3][j3-1].tipo=='M'){
              matriz[i3][j3].Minas=matriz[i3][j3].Minas+1;
            }
            if(matriz[i3-1][j3-1].tipo=='M'){
              matriz[i3][j3].Minas=matriz[i3][j3].Minas+1;
            }
            if(matriz[i3-1][j3].tipo=='M'){
              matriz[i3][j3].Minas=matriz[i3][j3].Minas+1;
            }
            if(matriz[i3-1][j3+1].tipo=='M'){
              matriz[i3][j3].Minas=matriz[i3][j3].Minas+1;
            }
            if(matriz[i3][j3+1].tipo=='M'){
              matriz[i3][j3].Minas=matriz[i3][j3].Minas+1;
            }
            if(matriz[i3+1][j3+1].tipo=='M'){
              matriz[i3][j3].Minas=matriz[i3][j3].Minas+1;
            }
            if(matriz[i3+1][j3].tipo=='M'){
              matriz[i3][j3].Minas=matriz[i3][j3].Minas+1;
            }
            if(matriz[i3+1][j3-1].tipo=='M'){
              matriz[i3][j3].Minas=matriz[i3][j3].Minas+1;
            }
        }
        j3++;
      }
      i3++;
    }
}

void destapar(int i3,int j3,tipocasilla **matriz){
        matriz[i3][j3].etiqueta=matriz[i3][j3].Minas + '0';

        if(matriz[i3][j3].Minas==0 && matriz[i3][j3].tipo=='c'){
            matriz[i3][j3-1].etiqueta=matriz[i3][j3-1].Minas + '0';
            matriz[i3-1][j3-1].etiqueta=matriz[i3-1][j3-1].Minas + '0';
            matriz[i3-1][j3].etiqueta=matriz[i3-1][j3].Minas + '0';
            matriz[i3-1][j3+1].etiqueta=matriz[i3-1][j3+1].Minas + '0';
            matriz[i3][j3+1].etiqueta=matriz[i3][j3+1].Minas + '0';
            matriz[i3+1][j3+1].etiqueta=matriz[i3+1][j3+1].Minas + '0';
            matriz[i3+1][j3].etiqueta=matriz[i3+1][j3].Minas + '0';
            matriz[i3+1][j3-1].etiqueta=matriz[i3+1][j3-1].Minas + '0';
        }
        if(matriz[i3][j3].Minas==0 && matriz[i3][j3].tipo=='c'){
            destapar(i3,j3-1,matriz);
            destapar(i3-1,j3-1,matriz);
            destapar(i3-1,j3,matriz);
            destapar(i3-1,j3+1,matriz);
        }
}
void destapar2(int i3,int j3,tipocasilla **matriz){
        matriz[i3][j3].etiqueta=matriz[i3][j3].Minas + '0';

        if(matriz[i3][j3].Minas==0 && matriz[i3][j3].tipo=='c'){
            matriz[i3][j3-1].etiqueta=matriz[i3][j3-1].Minas + '0';
            matriz[i3-1][j3-1].etiqueta=matriz[i3-1][j3-1].Minas + '0';
            matriz[i3-1][j3].etiqueta=matriz[i3-1][j3].Minas + '0';
            matriz[i3-1][j3+1].etiqueta=matriz[i3-1][j3+1].Minas + '0';
            matriz[i3][j3+1].etiqueta=matriz[i3][j3+1].Minas + '0';
            matriz[i3+1][j3+1].etiqueta=matriz[i3+1][j3+1].Minas + '0';
            matriz[i3+1][j3].etiqueta=matriz[i3+1][j3].Minas + '0';
            matriz[i3+1][j3-1].etiqueta=matriz[i3+1][j3-1].Minas + '0';
        }
        if(matriz[i3][j3].Minas==0 && matriz[i3][j3].tipo=='c'){
            destapar(i3,j3+1,matriz);
            destapar(i3+1,j3+1,matriz);
            destapar(i3+1,j3,matriz);
            destapar(i3+1,j3-1,matriz);
        }
}

int tableroterminado(int filas,int columnas,tipocasilla **matriz,int minas){
    int i;
    for(i=1;i<filas+1;i++){
    int j;
        for(j=1;j<columnas+1;j++){
            if(matriz[i][j].tipo=='c'){
                matriz[i][j].etiqueta=matriz[i][j].Minas + '0';
            }
            else{
                matriz[i][j].etiqueta='*';
            }
        }
    }
}

int ganaste(tipocasilla **matriz,int *minascopia,int i2,int j2){
    int i=i2;
    int j=j2;
    if(matriz[i][j].tipo=='M'){
        *minascopia=*minascopia-1;
        if(*minascopia==0){
            return 1;
        }
    }
    return 0;
}

void pedirfilacolumna(int filas,int columnas,tipocasilla **matriz,int minas){
    int minascopia=minas;
    int Despedidad=0;
    while(1){
        int i2,j2;
        char MoB;
        int victoria=0;
        printf("\nN = Normal , B = Bandera");
        printf("\nIngrese: fila,columna,N  O  fila,columna,B:  ");
        scanf("%d,%d,%c",&i2,&j2,&MoB);

        if(MoB=='N'){
            destapar(i2,j2,matriz);
            destapar2(i2,j2,matriz);
            system("cls");
            imprimir_tablero(filas,columnas,matriz);

            if(matriz[i2][j2].tipo=='M'){
                break;
            }
        }
        if(MoB=='B'){
            matriz[i2][j2].etiqueta='B';
            system("cls");
            imprimir_tablero(filas,columnas,matriz);
            if(matriz[i2][j2].tipo=='M'){
                victoria= ganaste(matriz,&minascopia,i2,j2);
            }
            if(victoria==1){
                printf("\n\n  GANASTE EL JUEGO  \n\n");
                Despedidad=Despedidad+1;
                break;
            }
        }
    }
    if(Despedidad==0){
        printf("\n   PERDISTE, PERO PUEDES VOLVERLO A INTENTAR\n   Hecho por Jeison Fernando Garces Castañeda\n");
    }
    printf("\n   EL JUEGO SE ENCONTRABA DE ESTA FORMA:  \n\n");
    tableroterminado(filas,columnas,matriz,minas);
    //system("cls");
    imprimir_tablero(filas,columnas,matriz);

}

int main(int argc,char *argv[],int argc2,char *argv2[],int argc3,char *argv3[]){
    typedef struct casilla tipocasilla;
    tipocasilla **matriz;
    int filas=atoi(argv[1]);
    int columnas=atoi(argv[2]);
    int minas;//atoi(argv[3])
    srand(time(NULL));
    printf("¿Cuantas minas quieres? (recuerda menor que el numero de casillas) : ");
    scanf("%d",&minas);

    matriz=CrearMatriz(filas,columnas);// Creacion de la matriz , con las filas y las columnas.
    llenar_tablero(filas,columnas,matriz);// Llernar el tablero filas y columnas"se llena con la estructura casilla"
    colocarminas(filas,columnas,matriz,minas);
    ayudadminas(filas,columnas,matriz,minas);
    imprimir_tablero(filas,columnas,matriz);
    pedirfilacolumna(filas,columnas,matriz,minas);
}
