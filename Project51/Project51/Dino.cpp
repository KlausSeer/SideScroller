#include "Dino.h"

#define Gravity 9.81

Dino::Dino(Size _Client) {
	//1294, 343
	this->Client = _Client;
	this->areaDibujo.X = int(_Client.Width / 8.5);
	this->areaDibujo.Y = int(_Client.Height / 1.60);
	this->areaDibujo.Width = 70;
	this->areaDibujo.Height = 100;
	this->indice = 0;						 // Sprite Indice: 0,1
	this->salto = false;
	this->vo = 60;
	this->yo = int(_Client.Height / 1.60)* -1;
	this->t = 0;

}

Rectangle Dino::get_Posicion() {
	return this->areaDibujo;
}

void Dino::realizarSalto() {
	this->salto = true;
}

void Dino::Dibujar(Graphics^ g, Bitmap^ img) {

	g->DrawImage(img, retornarAreaDibujo(), retornarFoco(img), GraphicsUnit::Pixel);

}

Rectangle Dino::retornarAreaDibujo() {

	if (this->salto) {
		t += 0.210;
		double yt; // posicion en instante t
		yt = this->yo + (this->vo * this->t) - ((Gravity / 2)*t*t);
		this->areaDibujo.Y = yt * -1;
		
		yt <= this->yo ? this->salto = false, this->t = 0: this->salto = true;
	}

	return this->areaDibujo;
}

Rectangle Dino::retornarFoco(Bitmap^ img) {

	Rectangle f;
	
	this->indice < 3 ? this->indice += 1: this->indice = 0;

	f = Rectangle(indice*(img->Width / 4), 0, img->Width / 4, img->Height);

	return f;
}


