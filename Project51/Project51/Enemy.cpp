#include "Enemy.h"

Enemy::Enemy(Size _Client) {
	this->Client = _Client;
	this->areaDibujo.X = _Client.Width;
	this->areaDibujo.Y = int(_Client.Height / 1.30);
	this->areaDibujo.Width = 70;
	this->areaDibujo.Height = 40;
}

void Enemy::dibujar(Graphics^ g, Bitmap^ img) {
	g->DrawImage(img, obtenerPosicion());
}

Rectangle Enemy::obtenerPosicion() {

	this->areaDibujo.X -= 10;

	return this->areaDibujo;
}

Rectangle Enemy::get_AreaDibujo() {
	return this->areaDibujo;
}
