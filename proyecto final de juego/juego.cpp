#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

char tabla[50][50];//tabla con valores reales
char tabla2[50][50];//tabla para ocultar (?)
int aciertos, vidas, puntuacion;
bool level_up;//si paso de nivel

int matriz[4][4]={{8,7,2,5}, {12,14,1,11}, {10,6,13,3}, {9,15,4,0}};
int posicion[2];


int menu_principal(){
	int opcion;
	cout<<"\t\t\t\tMENU PRINCIPAL"<<endl;
	cout<<"\t\t\t\t=============="<<endl;
	cout<<"\t\t[1]: Juego de Memoria"<<endl;
	cout<<"\t\t[2]: Juego de Ordenar"<<endl;
	cout<<"\t\t[3]: Instrucciones"<<endl;
	cout<<"\t\t[0]: Salir"<<endl;
	do{
		cout<<"Ingrese una opcion: [ ]"<<"\b\b";
		cin>>opcion;
	}while(opcion<0||opcion>3);
	return opcion;
}

void instrucciones(){
	system("cls");
	cout<<"\t\t\t\tINSTRUCCIONES"<<endl<<endl;
	cout<<"\t\t\t\t**************"<<endl;
	cout<<"JUEGO DE MEMORIA:"<<endl;
	cout<<"================"<<endl;
	cout<<"1. Apareceran letras al azar."<<endl;
	cout<<"2. Memoricelas rapidamente."<<endl;
	cout<<"3. Presione cualquier tecla."<<endl;
	cout<<"4. Escriba el numero de fila y columna que recuerde."<<endl;
	cout<<"5. Escriba el valor (LETRA) que tenia ese elemento."<<endl<<endl;
	cout<<"El puntaje empieza con 100 puntos, por cada letra bien contestada usted sumara 50 puntos."<<endl;
	cout<<"Cada vez que suba de nivel se le regala 100 puntos adicionales y"<<endl;
	cout<<"si pierde se le descuenta 10 puntos"<<endl;
	cout<<"tiene 3 intentos"<<endl<<endl;
	cout<<"JUEGO DE ORDENAR:"<<endl;
	cout<<"================"<<endl;
	cout<<"1. Ordene los numeros del 1 al 15."<<endl;
	cout<<"2. Muevase con las teclas w-a-s-d hasta que el cuadro quede organizado"<<endl;
	cout<<"3. w (arriba)"<<endl;
	cout<<"4. a (izquierda)"<<endl;
	cout<<"5. s (abajo)"<<endl;
	cout<<"6. d (derecha)"<<endl<<endl;
	cout<<"Buena suerte :D"<<endl;
}

void salir(){
	system("cls");
	cout<<"\t\t\t\tSALIENDO"<<endl;
	cout<<"\t\t\t\t========"<<endl;
	cout<<"Terminando procesos."<<endl;
}

void ocultar(int &dificultad){
	int fila, columna;
	char valor;
	
	if(vidas==0){
		cout<<"\n\t\t\t\tFIN DEL JUEGO";
		getche();
	}
	else if(aciertos==dificultad*dificultad){
		cout<<"\n\t\t\t\tFELICIDADES";
		level_up=true;
		puntuacion+=100;
		dificultad++;
		getche();
	}
	
	else{
		system("cls");
		
		//oculto los elementos
		for(int i=0;i<dificultad;i++){
			//este if es para la primera fila
			if(i==0){
				cout<<"\t\t\t\t  ";
				for(int w=1;w<=dificultad;w++){
					cout<<w<<" ";
				}
				cout<<endl;
			}
			
			cout<<"\t\t\t\t"<<i+1<<" ";
			for(int j=0;j<dificultad;j++){
				cout<<tabla2[i][j]<<" ";
			}
			cout<<endl;
		}
		
		
		cout<<"Tiene "<<vidas<<" vidas."<<endl;
		cout<<"Tiene "<<puntuacion<<" puntos."<<endl<<endl;
		do{
			cout<<"Ingrese el valor de la fila: ";
			cin>>fila;
			cout<<"Ingrese el valor de la columna: ";
			cin>>columna;
		}while(fila<=0||columna<=0||fila>dificultad||columna>dificultad);
		cout<<"Que valor tenia?: ";
		cin>>valor;
		fila--;columna--;
		
		
		if(tabla2[fila][columna]=='0'){
			cout<<"Este valor ya fue resuelto.";
			getche();
			ocultar(dificultad);
		}
		else{
			//si acerto
			if(tabla[fila][columna]==valor){
				cout<<"Correcto.";
				tabla2[fila][columna]='0';
				aciertos++;
				puntuacion+=50;
				getche();
				ocultar(dificultad);
			}
			else{
				cout<<"Incorrecto.";
				vidas--;
				puntuacion-=10;
				getche();				
				ocultar(dificultad);
			}
		}
		
	}
}

void jugar(int &dificultad){
	level_up=false;
	system("cls");
	
	if(dificultad==1)
		dificultad=2;
	else if(dificultad==2)
		dificultad=3;
	
	//lleno la matriz
	for(int i=0;i<dificultad;i++){
		for(int j=0;j<dificultad;j++){
			tabla[i][j]='a'+rand()%20;
		}
	}

	//escribo la matriz
	for(int i=0;i<dificultad;i++){
		//este if es para la primera fila
		if(i==0){
			cout<<"\t\t\t\t  ";
			for(int w=1;w<=dificultad;w++){
				cout<<w<<" ";
			}
			cout<<endl;
		}
		cout<<"\t\t\t\t"<<i+1<<" ";
		
		for(int j=0;j<dificultad;j++){
			cout<<tabla[i][j]<<" ";
		}
		cout<<endl;
	}
	
	//lleno la tabla ?
	for(int i=0;i<dificultad;i++){
		for(int j=0;j<dificultad;j++){
			tabla2[i][j]='?';
		}
	}
	
	cout<<"\nToque cualquier tecla cuando este listo.";
	getche();
	ocultar(dificultad);
	
	//me dice si vuelvo a jugar
	if(level_up==true){
		aciertos=0;
		jugar(dificultad);
	}
}

void menu_jugar(){
	bool superior=false;
	int aux;//posicion superior
	int dificultad;
	
	srand(time(NULL));
	system("cls");
	cout<<"\t\t\t\tElija su dificultad:"<<endl;
	cout<<"\t\t\t\t==================="<<endl;
	cout<<"\t\t[1]: Facil (2X2)"<<endl;
	cout<<"\t\t[2]: Dificil (3X3)"<<endl;
	cout<<"\t\t[0]: Personalizada"<<endl;
	do{
		cout<<"Ingrese una opcion: [ ]"<<"\b\b";
		cin>>dificultad;
	}while(dificultad<0||dificultad>2);
	
	if(dificultad==0){
		cout<<endl;
		do{
			cout<<"Ingrese su nivel de dificultad [4-50]: ";cin>>dificultad;
		}while(dificultad<4||dificultad>50);
	}
	
	jugar(dificultad);
}


//me dice si se ordeno
bool control(){
	if(matriz[0][0]==1 && matriz[0][1]==2 && matriz[0][2]==3 && matriz[0][3]==4 &&
		matriz[1][0]==5 && matriz[1][1]==6 && matriz[1][2]==7 && matriz[1][3]==8 &&
		matriz[2][0]==9 && matriz[2][1]==10 && matriz[2][2]==11 && matriz[2][3]==12 &&
		matriz[3][0]==13 && matriz[3][1]==14 && matriz[3][2]==15 && matriz[3][3]==0){
		return true;
	}
	return false;
}

void ubicacion(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			if(matriz[i][j]==0){				
				posicion[0]=i;
				posicion[1]=j;
			}
		}
	}
}

void movimiento(char mover){
	switch(mover){
		case 'w':
			if(posicion[0]!=0){
				matriz[posicion[0]][posicion[1]]=matriz[posicion[0]-1][posicion[1]];
				matriz[posicion[0]-1][posicion[1]]=0;
			}
			break;
		case 'a':
			if(posicion[1]!=0){
				matriz[posicion[0]][posicion[1]]=matriz[posicion[0]][posicion[1]-1];
				matriz[posicion[0]][posicion[1]-1]=0;
			}
			break;
		case 's':
			if(posicion[0]!=3){
				matriz[posicion[0]][posicion[1]]=matriz[posicion[0]+1][posicion[1]];
				matriz[posicion[0]+1][posicion[1]]=0;
			}
			break;
		case 'd':
			if(posicion[1]!=3){
				matriz[posicion[0]][posicion[1]]=matriz[posicion[0]][posicion[1]+1];
				matriz[posicion[0]][posicion[1]+1]=0;
			}
			break;
	}
}

void ordenar(){
	char mover;
	system("cls");
	cout<<"\t\t\t\tOrdene:"<<endl;
	cout<<"\t\t\t\t======="<<endl;
	
	if(control()==true){
		cout<<"Lo lograste.";
	}
	else{
		for(int i=0;i<4;i++){
			cout<<"\t\t\t";
			for(int j=0;j<4;j++){
				cout<<setw(3)<<matriz[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<"Muevase con w-a-s-d hasta que el cuadro quede organizado:"<<endl;
		ubicacion();
		cin>>mover;
		movimiento(mover);
		
		ordenar();
	}
}

int main(){
	int opcion;
	
	do{
		system("cls");
		opcion=menu_principal();
		switch(opcion){
			case 1:
				vidas=3;
				aciertos=0;
				puntuacion=100;
				menu_jugar();
				getche();
				break;
			case 2:
				ordenar();
				getche();
				break;
			case 3:
				instrucciones();
				getche();
				break;
			case 0:
				salir();
				getche();
				break;
		}
	}while(opcion!=0);
	return 0;
}
