#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector> 

using namespace std;

void integrantes(){
	cout<<"Fabian Cancino Riquelme"<<endl;
	cout<<"Victor Gomez Espinosa"<<endl;
	cout<<"Alberto Vasquez Benanvente"<<endl;
}

bool verificar(string n){
	if(n.length()>1){
		return false;
	}
	else{
		if(n[0]>47 && n[0]<58 || n[0]==91 || n[0]==93 || n[0]==59){
			return true;
		}
		else{
			return false;
		}
	}
}

void mostrar(int matriz[][9]){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout<<matriz[i][j]<<" ";
		}
		cout<<endl;
	}
}

int convierte(string aux){   
	int n = atoi(aux.c_str()); 
    return n; 
}

bool RevisarFila (int fila, int valor, int matriz[][9]){
    for(int j=0;j<9;j++){
        if(matriz[i][j]==valor){
            return true;
        }
    }
    return false;
}

bool RevisarColumna (int fila, int valor, int matriz[][9]){
    for(int i=0;i<9;i++){
        if(matriz[i][j]==valor){
            return true;
        }
    }
    return false;
}


int main(int argc, char* argv[]){

     //variables necesarias
	int matriz[9][9];
    int ct=0 ,ct_usa=0;
    int posI, posJ, num;
    string argu;

// llenado de matriz con 0
    for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			matriz[i][j]=0;
		}
    }


	//Para ingresar datos, se ingresa con el siguiente formato: ./ejecutable "[1;2;3]" "[4;5;6]" "[7;8;9]"
for(int i=1;i<argc;i++){
		argu=argv[i];
		cout << endl;
		if (argu.substr(0,1)=="[" && argu.substr(6,1)=="]"){
			if(argu.substr(2,1)==";" && argu.substr(4,1)==";"){
				if(verificar(argu.substr(1,1)) && verificar(argu.substr(3,1)) && verificar(argu.substr(5,1))){
					posI= convierte(argu.substr(1,1));
					posJ= convierte(argu.substr(3,1));
					num= convierte(argu.substr(5,1));
					while(argu!=""){
						if (posI >= 0 && posI < 9 && posJ>= 0 && posJ<9 && num >=1 && num <=9){
							if (matriz [posI][posJ]==0){
								matriz [posI][posJ]=num;
								ct ++;
							}
							else {
								cout << "Parametro ya ingresado previamente" << endl;
							}
						}
						argu=argu.substr(7);
					}
				}
				else{cout << "Datos mal ingresados";}
			}
			else{cout << "Datos mal ingresados";}		
		}
		else{cout << "Datos mal ingresados";}	
	}
	mostrar(matriz); 
    return 0;
}