#include "diretorio.h"

int main(){

diretorio main = diretorio("main");


main.print_diret();

while(open){

    if(main.atualizar()){
        system("CLS");
        printf("Atualizou \n");
        main.print_diret();
        main.pesistencia();
    }

}

    return 0;
}

