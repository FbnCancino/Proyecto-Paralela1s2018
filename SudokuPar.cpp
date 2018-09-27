#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <time.h>
#include <omp.h>
#include <ctime>
#include <iomanip>
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
void llenadoRestante(int matriz[][9]){
	cout<<"llenado"<<endl;
	
	bool ver1,ver2,ver3;
	int target_thread_num = 4;
	omp_set_num_threads(target_thread_num);
	unsigned long times[target_thread_num];
	for(int i=0;i<9;i++)
	{
		//cout<<"for1"<<endl;
		for(int j=0;j<9;j++)
		{
			cout<<endl;
			if(matriz[i][j]==0)
			{
				cout<<endl;
				int n=1;
				while(n<10)
				{
					cout<<endl;
					#pragma omp parallel sections
    				{
						#pragma omp section
        					{
        						int thread_id = omp_get_thread_num();
   								//times[thread_id] = start_time();

   								cout << "Thread number: " << omp_get_thread_num() << endl;

   								//times[thread_id] = end_time();
        						//cout<<"soy el proce 1"<<endl;
        						ver1=RevisarFila(matriz,n,i);
						
        					}
						#pragma omp section
        					{
        						//cout<<"soy el proce 2"<<endl;
        						int thread_id = omp_get_thread_num();
   								//times[thread_id] = start_time();

   								cout << "Thread number: " << omp_get_thread_num() << endl;
        						ver2=RevisarColumna(matriz,n,j);
        					}
					
						#pragma omp section
							{
								//cout<<"soy el proce 3"<<endl;
								int thread_id = omp_get_thread_num();
   								//times[thread_id] = start_time();

   								cout << "Thread number: " << omp_get_thread_num() << endl;
								ver3=RevisarSubmatriz(matriz,i,j,n);
							}
    				}
					
					
					
					if(ver1)
					{
						//cout<<"fila"<<endl;
						if(ver2)
						{
							//cout<<"columna"<<endl;
							if(ver3)
							{
								//cout<<"matriz"<<endl;
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
				#pragma omp parallel sections
    			{
					#pragma omp section
        			{
        				//cout<<"soy el proce 1"<<endl;
						verif1=RevisarFila(matriz,Conv_Num(num),Conv_Num(pos_i));
        			}
					#pragma omp section
        			{
        				//cout<<"soy el proce 2"<<endl;
        				verif2=RevisarColumna(matriz,Conv_Num(num),Conv_Num(pos_j));
        			}
					
					#pragma omp section
					{
						//cout<<"soy el proce 3"<<endl;
						verif3=RevisarSubmatriz(matriz,Conv_Num(pos_i),Conv_Num(pos_j),Conv_Num(num));
					}
    			}
				
				
				
				
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
	ofstream archivo;
	archivo.open("solucion.csv");
	for(int g=0;g<9;g++)
	{
		for(int h=0;h<9;h++)
		{
			if(h<8)
			{
				archivo<<matriz[g][h]<<",";
			}
			else
			{
				archivo<<matriz[g][h]<<"\n";
			}
		}
	}
	archivo.close();
}
