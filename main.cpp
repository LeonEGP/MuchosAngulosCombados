//Programa que: Implementa un algoritmo fundamentado en el escaneo Graham para determinar la Cáscar Convexa dados ciertos puntos.
//Programadores: León Emiliano García Pérez [A00573074], Carla Morales López [A01639225].
//Fecha de entrega: Domingo 23 de Octubre de 2022.

//Inclusión de librerías
#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <bits/stdc++.h>

//Ajuste a estandar
using namespace std;

//Definición de estrucutra Punto
struct Point {
	int x;
	int y;
};

//Punto global que funciona como auxiliar para realizar un ordenamiento.
Point p0;

//Función que ayuda a encontrar el Punto siguiente al Top de un Stack, recibe un stack referenciado de Puntos y retorno el Punto siguiente al Top.
Point nextToTop(stack<Point>& S) { //Complejidad Computacional: O(1). 
	Point p = S.top();
	S.pop();
	Point res = S.top();
	S.push(p);
	return res;
}

//Función que intercambia dos Puntos, recibe la referencia a dos Puntos, no tiene valor de retorno.
void swap(Point& p1, Point& p2) { //Complejidad Computacional: O(1). 
	Point temp = p1;
	p1 = p2;
	p2 = temp;
}

//Función que calcula el cuadrado de la distancia entre dos puntos, recibe como parámetro los dos puntos, y retorna el entero de la distancia cuadrada.
int distSq(Point p1, Point p2) { //Complejidad Computacional: O(1). 
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

//Función que determina el sentido dados tres Puntos, recibe los tres Puntos y retorna 0 si son colineares, 1 si van al sentido del reloj, 2 si van en contra sentido del reloj.
int orientation(Point p, Point q, Point r) { //Complejidad Computacional: O(1). 

	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

	if (val == 0) {
		return 0; //Collinear
	}
	else if (val > 0) {
		return 1; //Clockwise
	}
	else {
		return 2; //Counterclockwise
	}

}

//Función auxiliar de comparación para ordenar un arreglo de Puntos, recibe dos apuntadores a constantes void y retorna -1 o 1 según sea el caso.
int compare(const void* vp1, const void* vp2) { //Complejidad Computacional: O(1). 

	Point* p1 = (Point*)vp1;
	Point* p2 = (Point*)vp2;

	int o = orientation(p0, *p1, *p2);

	if (o == 0) {
		if (distSq(p0, *p2) >= distSq(p0, *p1)) {
			return -1;
		}
		else {
			return 1;
		}
	}
	else if (o == 2) {
		return -1;
	}
	else {
		return 1;
	}
}

//Función que imprime la cáscara conveza dado un arreglo de puntos, recibe además la cantidad de puntos, no tiene valor de retorno.
void convexHull(Point points[], int n) { //Complejidad Computacional: O(n). 
	

	int ymin = points[0].y, min = 0;

	for (int i = 1; i < n; i++) {
		
		int y = points[i].y;

		if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
			ymin = points[i].y, min = i;
		}
	}

	swap(points[0], points[min]);
	p0 = points[0];
	qsort(&points[1], n - 1, sizeof(Point), compare);

	int m = 1;

	for (int i = 1; i < n; i++) {

		while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0){
			i++;
        }
		points[m] = points[i];
		m++;
	}

	if (m < 3){
        cout << "IMPOSIBLE "
		return;
	}

	stack<Point> S;
	S.push(points[0]);
	S.push(points[1]);
	S.push(points[2]);

	for (int i = 3; i < m; i++) {

		while (S.size() > 1 && orientation(nextToTop(S), S.top(), points[i]) != 2) //
			S.pop();
		S.push(points[i]);
	}

	vector<Point> result;

	while (!S.empty()) {
		Point p = S.top();
		result.push_back(p);
		S.pop();
	}

	for (int i = result.size() - 1; i >= 0; i--) {
		cout << "(" << result[i].x << ", " << result[i].y << ") ";
		cout << endl;
	}

}


int main() {
    int n;
    cin >> n;

	Point points[n];

    for (int i = 0; i<n; i++){
        int xCord;
        int yCord;
        Point auxiliar;
        cin >> xCord;
        cin >> yCord;
        auxiliar.x = xCord;
        auxiliar.y = yCord;
        points[i] = auxiliar;
    }

	convexHull(points, n);

	return 0;
}
