#include <iostream>
#define tam 6
#include <time.h>
#include <windows.h>
using namespace std;


/**#define BLACK     0
#define BLUE         1
#define GREEN        2
#define AQUA         3
#define RED          4
#define PURPLE       5
#define YELLOW       6
#define WHITE        7
#define GRAY         8
#define LIGHTBLUE    9
#define LIGHTGREEN   10
#define LIGHTAQUA    11
#define LIGHTRED     12
#define LIGHTPURPLE  13
#define LIGHTYELLOW  14
#define BRIGHTWHITE  15
*/

struct play{
    char mtr[tam][tam] = {' '};
    char mtrM[tam][tam] = {' ',' ',' ',' ',' ',' ',
                           ' ',' ',' ',' ',' ',' ',
                           ' ',' ',' ',' ',' ',' ',
                           ' ',' ',' ',' ',' ',' ',
                           ' ',' ',' ',' ',' ',' ',
                           ' ',' ',' ',' ',' ',' ',};

    char mtrF[tam][tam] = {'A','F','G','R','T','P',
                           'D','W','M','N','V','H',
                           'P','X','A','S','Q','I',
                           'Q','O','F','G','I','Z',
                           'X','D','W','N','T','R',
                           'O','S','M','H','V','Z'};
};

int numAleatorio(){
    srand(time(NULL));
    return rand()%3;
}


void colorir (int cor) {

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(out, cor);
}

void posicaoxy(int column, int line ){
        COORD coord;
        coord.X = column;
        coord.Y = line;
        SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

void escolherDificultade(play &p, int num){
    switch(num){
        case 0:
            for(int i=0; i<tam; i++){
                for(int j=0; j<tam; j++){
                    p.mtr[i][j] = p.mtrF[j][i];
                }
            }break;
        case 1:
            for(int i=0; i<tam; i++){
                for(int j=tam-1; j>=0; j--){
                    p.mtr[i][j] = p.mtrF[i][j];
                }
            }break;
        case 2:
            for(int i=tam-1; i>=0; i--){
                for(int j=0; j<tam; j++){
                    p.mtr[i][j] = p.mtrF[i][j];
                }
            }break;
    }
}

void escolherPosicao(play &p, int &x, int &y, char &letra){
    int i, j;
    do{
        cout <<"Escolhe uma linha: \n";
        cin >>i;
        cout <<"Escolhe uma coluna: \n";
        cin >>j;
    }while((i < 0 || i > tam-1) || (j < 0 || j > tam-1) || (i == x && j == y) || p.mtrM[i][j] != ' ');
        letra = p.mtr[i][j];
        x = i;
        y = j;
}

void mostrar_game(play &p, int &x, int &y){
    cout<<endl;
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            if(i == x && j == y){
                colorir(4);
                cout<<p.mtr[i][j]<<"  ";
                colorir(7);
            }else{cout << 'X'<< "  ";}
        }cout<<endl;
    }
}

bool matriz_Final(play &p, char &escolha1, char &escolha2){
    colorir(9);
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            if(p.mtr[i][j] == escolha1 && escolha1 == escolha2){
                p.mtrM[i][j] = escolha1;
                colorir(13);
                cout<<p.mtrM[i][j]<<"  ";
                colorir(9);
            }else if(p.mtrM[i][j] != ' '){
                colorir(13);
                cout<<p.mtrM[i][j]<<"  ";
                colorir(9);
            }else{cout<<'X'<<"  ";}
        }cout<<endl;
    }colorir(7);
}

bool verifica(play &p){

    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            if(p.mtrM[i][j] == ' ') return false;
        }
    }return true;
}

int main()
{

    int num_Jogadas = 0, x = -1, y = -1;
    play p;
    char escolha1, escolha2, letra;
    escolherDificultade(p , numAleatorio());
    cout << "JOGO DA MEMORIA \n LEST GO..."<<endl;
    system("pause");
    system("cls");
    while(num_Jogadas < 24){

        matriz_Final(p,escolha1,escolha2);
        escolherPosicao(p ,x,y,letra);
        escolha1 = letra;
        mostrar_game(p ,x,y);
        escolherPosicao(p ,x,y,letra);
        escolha2 = letra;
        mostrar_game(p ,x,y);
        num_Jogadas++;

        if(escolha1 == escolha2){
            cout << "\n Jogada perfeita \n faltam: "<<24-num_Jogadas<<endl;
        }else{
            cout << "\n Jogada errada \n faltam: "<<24-num_Jogadas<<endl;
        }

        system("pause");
        system("cls");
    }

    if(num_Jogadas >= 24){
        if(!verifica(p)){
            cout << " Jogo Terminado, a Quantidade de jogadas esgotadas\n Jogadas "<<num_Jogadas<<endl;
        }else{
            cout << " Jogo Terminado, Parabens";
        }
        return 0;
    }
    cout << " Jogo Terminado, Parabens"<<endl;

    return 0;
}

