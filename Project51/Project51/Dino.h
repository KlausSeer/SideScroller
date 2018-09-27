#pragma once

using namespace System::Drawing;

class Dino {

	Size Client;
	Rectangle areaDibujo;
	int indice;
	double vo;// velocidad inicial;
	double yo;// posicion incial
	double t; // instante de tiempo
	
	bool salto;
public:
	Dino(Size _Client);

	Rectangle get_Posicion();
	void realizarSalto();
	void Dibujar(Graphics^ g, Bitmap^ img);
	Rectangle retornarAreaDibujo();
	Rectangle retornarFoco(Bitmap^ img);

};