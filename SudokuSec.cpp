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
/*bool test_rows(int matriz[][9]){
	int f,c,k;
	int next_num=1;
	bool rowReturn[9];

//#pragma omp parallel for private(i)
	for(f=0;f<9;f++)
	{

	}
}*/
/*void RRevisarFila(int matriz[][9], int num, int fila, bool resp, int coaux){
	resp=true;
	for(int j=0;j<9;j++)
	{
		if(matriz[fila][j]==num)
		{
			resp=false;
			coaux=j;
			break;
		}
	}
	if(resp==false)
	{
		cout<<"La fila "<<fila<<" ya contiene el n° "<<num<<" en la posición: ["<<fila<<","<<coaux<<"]	<--	["<<fila<<";"<<coaux<<";"<<num<<"]"<<endl;	
	}
}*/
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
/*void RRevisarColumna(int matriz[][9], int num, int columna, bool resp, int fiaux){
	resp=true;
	for(int i=0;i<9;i++)
	{
		if(matriz[i][columna]==num)
		{
			resp=false;
			fiaux=i;
			break;
		}
	}
	if(resp==false)
	{
		cout<<"La columna "<<columna<<" ya contiene el n° "<<num<<" en la posición: ["<<fiaux<<","<<columna<<"]	<--	["<<fiaux<<";"<<columna<<";"<<num<<"]"<<endl;	
	}
}*/
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
void llenadoRestante(int matriz[][9]){
	cout<<"llenado"<<endl;
	int n=1;
	bool ver1,ver2,ver3;
	for(int i=0;i<9;i++)
	{
		cout<<"for1"<<endl;
		for(int j=0;j<9;j++)
		{
			cout<<"for2"<<endl;
			if(matriz[i][j]==0)
			{
				cout<<"if1"<<endl;
				while(n<10)
				{
					cout<<n<<endl;
					ver1=RevisarFila(matriz,n,i);
					ver2=RevisarColumna(matriz,n,j);
					ver3=RevisarSubmatriz(matriz,i,j,n);
					if(ver1)
					{
						cout<<"fila"<<endl;
						if(ver2)
						{
							cout<<"columna"<<endl;
							if(ver3)
							{
								cout<<"matriz"<<endl;
								matriz[i][j]=n;
								n++;
								break;
							}
						}
					}
					n++;
				}
			}
		}
	}
}
int main(int argc, char* argv[]){
	bool verif3, verif2, resp, resp1, resp2, verif1;
	int coaux,fiaux;
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
		cout<<endl;
		while(argumento!="")
		{
			pos_i=argumento.substr(1,1);
			pos_j=argumento.substr(3,1);
			num=argumento.substr(5,1);
			if(esNumero(pos_i) && esNumero(pos_j) && esNumero(num) && Conv_Num(pos_i)>=0 && Conv_Num(pos_i)<9 && Conv_Num(pos_j)>=0 && Conv_Num(pos_j)<9 && Conv_Num(num)>=1 && Conv_Num(num)<=9)
			{
				verif1=RevisarFila(matriz,Conv_Num(num),Conv_Num(pos_i));
				verif2=RevisarColumna(matriz,Conv_Num(num),Conv_Num(pos_j));
				verif3=RevisarSubmatriz(matriz,Conv_Num(pos_i),Conv_Num(pos_j),Conv_Num(num));
				if(verif1)
				{
					if(verif2)
			 		{
						if(verif3)
						{
							matriz[Conv_Num(pos_i)][Conv_Num(pos_j)]=Conv_Num(num);
						}
					}
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
	llenadoRestante(matriz);
	Mostrar(matriz);
}
