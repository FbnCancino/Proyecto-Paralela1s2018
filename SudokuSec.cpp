#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>

using namespace std;

int Conv_Num(string valor){   
	int n = atoi(valor.c_str()); 
    return n; 
}
bool esNumero(string valor){
	if(Conv_Num(valor)==0){
		return true;
	}
	else{
		int aux = atoi(valor.c_str());
		if(aux==0){
			return false;
		}
		else{
			return true;
		}
	}
}
void Mostrar(int matriz[][9]){
	cout<<"Matriz"<<endl;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout<<matriz[i][j]<<" ";
		}
		cout<<endl;
	}
}
bool RevisarFila(int matriz[][9], int num, int fila){
	bool resp=true;
	for(int j=0;j<9;j++)
	{
		if(matriz[fila][j]==num)
		{
			resp=false;
		}
	}
	return resp;
}
bool RevisarColumna(int matriz[][9], int num, int columna)
{
	bool respp=true;
	for(int x=0;x<9;x++)
	{
		if(matriz[x][columna]==num)
		{
			respp=false;
		}
	}
	return respp;
}
bool RevisarSubmatriz(int matriz [][9], int fila, int columna, int num)
{
	bool ressp=true;
	int auxi1, auxi2, auxj1, auxj2;
	if(fila<3)
	{
		auxi1=0;
		auxi2=2;
	}
	if(fila>=3 && fila<6)
	{
		auxi1=3;
		auxi2=5;
	}
	if(fila>=6 && fila<9)
	{
		auxi1=6;
		auxi2=8;
	}
	if(columna<3)
	{
		auxj1=0;
		auxj2=2;
	}
	if(columna>=3 && columna<6)
	{
		auxj1=3;
		auxj2=5;
	}
	if(columna>=6 && columna<9)
	{
		auxj1=6;
		auxj2=8;
	}
	for(int y=auxi1;y<=auxi2;y++)
	{
		for(int z=auxj1;z<=auxj2;z++)
		{
			if(matriz[y][z]==num)
			{
				ressp=false;
			}
		}
	}
	return ressp;
}
int main(int argc, char* argv[]){
	bool verif1, verif2, verif3;
	int subm[3][3];
	int matriz[9][9];
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			matriz[i][j]=0;

	string argumento=argv[1];
	string pos_i;
	string pos_j;
	string num;
	if (argumento.substr(0,1)=="[")
	{
		while(argumento!="")
		{
			pos_i=argumento.substr(1,1);
			pos_j=argumento.substr(3,1);
			num=argumento.substr(5,1);
			if(esNumero(pos_i) && esNumero(pos_j) && esNumero(num))
			{
				if(Conv_Num(pos_i)>=0 && Conv_Num(pos_i)<9)
				{
					if(Conv_Num(pos_j)>=0 && Conv_Num(pos_j)<9)
					{
						if(Conv_Num(num)>=1 && Conv_Num(num)<=9)
						{
							verif1=RevisarFila(matriz,Conv_Num(num),Conv_Num(pos_j));
							verif2=RevisarColumna(matriz,Conv_Num(num),Conv_Num(pos_i));
							verif3=RevisarSubmatriz(matriz,Conv_Num(pos_j),Conv_Num(pos_i),Conv_Num(num));
							if(verif1==false)
							{
								cout<<"La fila "<<pos_j<<" ya contiene el n° "<<num<<endl;
							}
							else
							{
								if(verif2==false)
								{
									cout<<"La columna "<<pos_i<<" ya contiene el n° "<<num<<endl;
								}
								else
								{
									if(verif3==false)
									{
										cout<<"El numero "<<num<<" ya está contenido en la submatriz"<<endl;
									}
									else
									{
										matriz[Conv_Num(pos_j)][Conv_Num(pos_i)]=Conv_Num(num);
									}
								}
							}
						}
						else
						{
							cout<<"Error de formato"<<endl;
						}
					}
					else
					{
						cout<<"Error de formato"<<endl;
					}
				}
				else
				{
					cout<<"Error de formato"<<endl;
				}
			}
			else
			{
				cout<<"Error de formato"<<endl;
			}
			argumento=argumento.substr(7);
		}
		cout<<endl;
	}
	else
	{
		cout<<"Error de formato"<<endl;
	}
	Mostrar(matriz);
}
