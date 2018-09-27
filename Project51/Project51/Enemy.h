#pragma once

using namespace System::Drawing;

class Enemy {
	Size Client;
	Rectangle areaDibujo;

public:
	Enemy(Size _Client);

	void dibujar(Graphics^ g, Bitmap^ img);
	Rectangle obtenerPosicion();
	Rectangle get_AreaDibujo();

};