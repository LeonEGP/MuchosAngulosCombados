//Programa que: Implementa un algoritmo fundamentado en el escaneo Graham para determinar la Cáscar Convexa dados ciertos puntos.
//Programadores: León Emiliano García Pérez [A00573074], Carla Morales López [A01639225].
//Fecha de entrega: Domingo 23 de Octubre de 2022.

//Inclusión de librerías
#include <iostream>
#include <bits/stdc++.h>
#include <stack>
#include <algorithm>
#include <vector>
#include <stdlib.h>

//Ajuste a estandar
using namespace std;

//Definición de estrucutra Punto.
struct Punto {
	int x;
	int y;
};

//Función que imprime en consola un salto de línea, no recibe parámetros y no tiene valor de retorno.
void espacio() { //Complejidad Computacional: O(1), es una ejecución lineal en el contenido de la función.
	cout << endl;
}

//Punto global que funciona como auxiliar para realizar un ordenamiento.
Punto punto0;

//Función que ayuda a encontrar el punto siguiente al top de un stack, recibe un stack referenciado de puntos y retorno el Punto siguiente al Top.
Punto siguientoAlTop(stack<Punto>& pila) { //Complejidad Computacional: O(1), es una ejecución lineal en el contenido de la función.

	Punto punto;
	Punto resultado;

	punto = pila.top();
	pila.pop();
	resultado = pila.top();
	pila.push(punto);

	return resultado;
}

//Función que intercambia dos puntos, recibe la referencia a dos puntos, no tiene valor de retorno.
void intercambio(Punto& punto1, Punto& punto2) { //Complejidad Computacional: O(1), es una ejecución lineal en el contenido de la función.

	Punto auxiliar;

	auxiliar = punto1;
	punto1 = punto2;
	punto2 = auxiliar;
}

//Función que calcula el cuadrado de la distancia entre dos puntos, recibe como parámetro los dos puntos, y retorna el entero de la distancia cuadrada.
int distanciaCuadrada(Punto punto1, Punto punto2) { //Complejidad Computacional: O(1), es una ejecución lineal en el contenido de la función.
	return (punto1.x - punto2.x) * (punto1.x - punto2.x) + (punto1.y - punto2.y) * (punto1.y - punto2.y);
}

//Función que determina el sentido dados tres puntos, recibe los tres puntos y retorna un 0 si es Collinear, 1 si es Dextrógiro (Al sentido del Reloj), 2 si es Levógiro ( Al sentido ContraReloj).
int direccion(Punto p, Punto q, Punto r) { //Complejidad Computacional: O(1), es una ejecución lineal en el contenido de la función.

	int valor;

	valor = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (valor == 0) {
		return 0;
	}
	else if (valor > 0) {
		return 1;
	}
	else {
		return 2;
	}
}

//Función auxiliar de comparación para ordenar un arreglo de puntos respecto al primero, recibe dos apuntadores a constantes void y retorna -1 o 1 según sea el caso.
int comparar(const void* voidPunto1, const void* voidPunto2) { //Complejidad Computacional: O(1), es una ejecución lineal en el contenido de la función.

	int sentido;
	Punto* punto1;
	Punto* punto2;

	punto1 = (Punto*)voidPunto1;
	punto2 = (Punto*)voidPunto2;
	sentido = direccion(punto0, *punto1, *punto2);

	if (sentido == 0) {
		if (distanciaCuadrada(punto0, *punto2) >= distanciaCuadrada(punto0, *punto1)) {
			return -1;
		}
		else {
			return 1;
		}
	}
	else if (sentido == 2) {
		return -1;
	}
	else {
		return 1;
	}
}

//Función que imprime la cáscara conveza dado un arreglo de puntos, recibe además la cantidad n de puntos, no tiene valor de retorno.
void cascaraConvexaGraham(Punto puntos[], int n) { //Complejidad Computacional: O(nlogn), siendo n la cantidad de puntos.

	int yMinima;
	int minimo;
	int tamanio;
	stack<Punto> pilaResultante;
	vector<Punto> resultado;

	yMinima = puntos[0].y;
	minimo = 0;

	for (int i = 1; i < n; i++) { //Complejidad Computacional: O(n), siendo n la cantidad de puntos.

		int y;
		y = puntos[i].y;

		if ((y < yMinima) || (yMinima == y && puntos[i].x < puntos[minimo].x)) {
			yMinima = puntos[i].y;
			minimo = i;
		}
	}

	intercambio(puntos[0], puntos[minimo]);
	punto0 = puntos[0];
	qsort(&puntos[1], n - 1, sizeof(Punto), comparar); //Complejidad Computacional: O(nlogn), siendo n la cantidad de puntos.
	tamanio = 1;

	for (int i = 1; i < n; i++) { //Complejidad Computacional: O(n), siendo n la cantidad de puntos.

		while (i < n - 1 && direccion(punto0, puntos[i], puntos[i + 1]) == 0) {
			i++;
		}

		puntos[tamanio] = puntos[i];
		tamanio++;
	}

	if (tamanio < 3) {
		espacio();
		cout << "¡¡¡IMPOSIBLE LA CREACION DE UN POLIGONO CONVEXO!!!";
		espacio();
		espacio();
		return;
	}

	pilaResultante.push(puntos[0]);
	pilaResultante.push(puntos[1]);
	pilaResultante.push(puntos[2]);

	for (int i = 3; i < tamanio; i++) {

		while (pilaResultante.size() > 1 && direccion(siguientoAlTop(pilaResultante), pilaResultante.top(), puntos[i]) != 2) {
			pilaResultante.pop();
		}

		pilaResultante.push(puntos[i]);
	}

	while (!pilaResultante.empty()) {
		Punto p = pilaResultante.top();
		resultado.push_back(p);
		pilaResultante.pop();
	}

	espacio();
	cout << "POLIGONO CONVEXO MAS PEQUENIO: [PUNTOS DADOS EN SENTIDO CONTRARIO AL RELOJ]" << endl;

	for (int i = resultado.size() - 1; i >= 0; i--) {
		cout << "(" << resultado[i].x << ", " << resultado[i].y << ") ";
		espacio();
	}

	espacio();
}

//Función main que ejecuta el programa, no recibe parámetros, retorna un entero [return 0].
int main() { //Complejidad Computacional: O(1). Dentro de esa ejecución lineal, el emplear el Graham Scan para la creación de la cáscara, se encuentra una complejidad de: O(nlogn).

	int n;
	cout << "INGRESE LA CANTIDAD DE PUNTOS: " << endl;
	cin >> n;

	Punto puntos[n];

	for (int i = 0; i < n; i++) { //Complejidad Computacional: O(n). 

		int xCord;
		int yCord;
		Punto auxiliar;

		cout << "x" << i + 1 << ": ";
		cin >> xCord;
		cout << "y" << i + 1 << ": ";
		cin >> yCord;

		auxiliar.x = xCord;
		auxiliar.y = yCord;
		puntos[i] = auxiliar;
	}

	cascaraConvexaGraham(puntos, n); //Complejidad Computacional: O(nlogn).

	return 0;
}
