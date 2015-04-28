#include <iostream>
#include "..\include\LinkedList.h"
#include <winbgim.h>
#include <math.h>
using namespace std;
#define PI 3.14159265358979

LinkedList<char> genDragon(int generaciones){
	/*  	String inicial: FX
	 *	Angulo: 90
	 */

	LinkedList<char> dragon;
	dragon.append('F');
	dragon.append('X');
	for(int i = 0; i < generaciones; i++){
	//Para cada generacion realizar las expansiones
		for(dragon.goToStart(); dragon.getPos() < dragon.getSize(); dragon.next()){
			if(dragon.getElement() == 'X'){
				//La X se reemplaza por X+YF
				dragon.next();
				dragon.insert('+');
				dragon.next();
				dragon.insert('Y');
				dragon.next();
				dragon.insert('F');
			}
			else if(dragon.getElement() == 'Y'){
				//La Y se reemplaza por FX-Y

				dragon.insert('F');
				dragon.next();
				dragon.insert('X');
				dragon.next();
				dragon.insert('-');
				dragon.next();
			}
		}
	}
	return dragon;
}

LinkedList<char> genSierp(int generaciones){
	/*  	String inicial: A
	 *	Angulo: 60
	 */
	LinkedList<char> sierp;
	sierp.append('A');

	for(int i = 0; i < generaciones; i++){
	//Para cada generacion realizar las expansiones
		for(sierp.goToStart(); sierp.getPos() < sierp.getSize(); sierp.next()){
			if(sierp.getElement() == 'A'){
				//La A se reemplaza por B-A-B

				//Primero insertar B- antes de A
				sierp.insert('B');
				sierp.next();
				sierp.insert('-');
				sierp.next();

				sierp.next();//Saltarse la posicion de la A
				//Luego insertar -B despues de la A
				sierp.insert('-');
				sierp.next();
				sierp.insert('B');
			}
			else if(sierp.getElement() == 'B'){
				//La B se reemplaza por A+B+A

				//Primero insertar A+ antes de B
				sierp.insert('A');
				sierp.next();
				sierp.insert('+');
				sierp.next();

				sierp.next();//Saltarse la posicion de la B

				//Luego insertar +A despues de la B
				sierp.insert('+');
				sierp.next();
				sierp.insert('A');
			}
		}
	}
	return sierp;
}

LinkedList<char> genLevy(int generaciones){
	/*  	String inicial: F
	 *	Angulo: 45
	 */
	LinkedList<char> levy;
	levy.append('F');
	for(int i = 0; i < generaciones; i++){
	//Para cada generacion realizar las expansiones
		for(levy.goToStart(); levy.getPos() < levy.getSize(); levy.next()){
			if(levy.getElement() == 'F'){
				//La F se reemplaza por +F--F+
				//Insertar + antes de la F
				levy.insert('+');
				levy.next();

				levy.next();//Saltarse la F

				//Insertar --F+ despues de la F
				levy.insert('-');
				levy.next();
				levy.insert('-');
				levy.next();
				levy.insert('F');
				levy.next();
				levy.insert('+');
			}
		}
	}
	return levy;
}

void turtle(LinkedList<char> fractal, int deltaAngle){// Se encarga de dibujar la lista de instrucciones.
    int dist = 250/(2+sqrt(fractal.getSize())/3);
    int angle = deltaAngle;
    double xpos,ypos, xnext, ynext;
    int color = rand()%10+1;
    int colorCount = 0;

    switch(deltaAngle){
	case 90:

		xpos = 500;
		ypos = 400;
		break;
	case -60:
		dist = 150/(5+sqrt(fractal.getSize()/2));
		xpos = 50;
		ypos = 650;
		break;
	case 60:
		dist = 150/(5+sqrt(fractal.getSize()/2));
		xpos = 600;
		ypos = 20;
		break;

	case 45:
	 	xpos = 500;
		ypos = 200;
		break;
    }

    initwindow(1200, 700);



    for(fractal.goToStart(); fractal.getPos() < fractal.getSize(); fractal.next()){
        switch(fractal.getElement()){
            case 'A':
            case 'B':
            case 'F':
                xnext = xpos + dist*cos(angle*PI/180);
                ynext = ypos + dist*sin(angle*PI/180);
		if(colorCount == 1000){
		color = rand()% 10 + 1;
		colorCount = 0;
		}
		colorCount++;
		setcolor(color);
		line((int) xpos, (int) ypos, (int) xnext, (int) ynext);

		xpos = xnext;
		ypos = ynext;
		break;

            case '+':
                angle += deltaAngle;
                break;
            case '-':
                angle -= deltaAngle;
                break;
        }
    }
    outtextxy (10, 10, (char*) "Fractal dibujado.  Presione una tecla para continuar...");
    getch();
    closegraph();
}

void menu(){
	int p, i;
	cout << "\n\n1. Curva del Dragon\n2. Curva de punta de flecha de Sierpinsky\n3. Curva C de Levy\n0. SALIR\n\n";
	cout << "Elija un fractal: "; cin >> p;

	if(p == 0) exit(0);

	if(p < 0 || p > 3){
		cout<<"\nEsa no es una opcion valida. Por favor, digite una opcion valida"<<endl;
		menu();
	}

	cout << "\nCuantas generaciones desea:  "; cin >> i;

    if (i < 0){
        cout<<"\nEse no es un numero valido. Por favor, digite un numero positivo"<<endl;
		menu();
    }

	cout << "Generando fractal. Favor espere...\n";

	switch(p){
		case 1:
			turtle(genDragon(i), 90);
			break;
		case 2:
			switch(i%2){
				case 1:
					turtle(genSierp(i), -60);
					break;
				case 0:
					turtle(genSierp(i), 60);
					break;
			}
			break;
		case 3:
			turtle(genLevy(i), 45);
			break;
	}

	system("cls");

	menu();
}

int main(){

	cout <<"\n\n ______              _        _ ______            "<<endl;
	cout <<" |  ___|            | |      | |  __  |            "<<endl;
	cout <<" | |_ _ __ __ _  ___| |_ __ _| | |  |_|___ _ ___  "<<endl;
	cout <<" |  _| '__/ _` |/ __| __/ _` | | |  __| _ | '_  |  "<<endl;
	cout <<" | | | | | (_| || (_| || (_| | | |_|  | __/ | | | "<<endl;
	cout <<" |_| |_| |___,_||___|__|__,__|_|_____/|___|_| |_| "<<endl;
	cout <<" \n\n	Instituto Tecnologico de Costa Rica"<<endl;



    	menu();


	return 0;
}

