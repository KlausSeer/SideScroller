#include "Controller.h"

Controller::Controller(Size _Client) {
	this->Client = _Client;
	this->Barney = new Dino(_Client);
	this->indice_esc = 0;
	this->gameover = false;
}

Controller::~Controller() {
	delete Barney;
}

void Controller::animar(Graphics^ g, Bitmap^ img1, Bitmap^ img2, Bitmap^ img3) {

	this->dibujar_Escenario(g, img2);
	this->agregarEnemigo();
	this->ver_Colision();
	this->dibujarEnemigos(g, img3);
	this->dibujar_Barney(g, img1);
	
	
	this->limpiarEnemigos();
	
	
}

void Controller::agregarEnemigo() {

	System::Random r;

	int n = 0;
	n = r.Next(0, 1501);

	if (n % 100 == 0) {
		this->enemigos.push_back(new Enemy(this->Client));
	}

}

void Controller::dibujarEnemigos(Graphics^ g, Bitmap^ img3) {
	if (enemigos.size() != 0) {
		for (unsigned int i = 0; i < this->enemigos.size(); i++) {
			this->enemigos.at(i)->dibujar(g, img3);
		}
	}
	
}

void Controller::dibujar_Barney(Graphics^ g, Bitmap^ img1) {
	if (this->Barney == nullptr) {
		this->gameover = true;
	}
	else {
		this->Barney->Dibujar(g, img1);
	}


}
void Controller::limpiarEnemigos() {
	for (unsigned int i = 0; i < this->enemigos.size(); i++) {
		if (this->enemigos.at(i)->get_AreaDibujo().X < 0) {
			delete[] this->enemigos.at(i);
			this->enemigos.erase(this->enemigos.begin() + i);
		}
	}
}

void Controller::dino_Saltar() {
	this->Barney->realizarSalto();
}




void Controller::dibujar_Escenario(Graphics^ g, Bitmap^ img) {

	g->DrawImage(img, Rectangle(0, 0, Client.Width, Client.Height), obtenerSubImagen(img), GraphicsUnit::Pixel);
}

bool Controller::game_over() {
	return this->gameover;
}

void Controller::ver_Colision() {
	if (this->Barney != nullptr) {
		for (unsigned int i = 0; i < this->enemigos.size(); i++) {
			if (this->Barney != nullptr) {
				if (this->Barney->retornarAreaDibujo().IntersectsWith(this->enemigos.at(i)->get_AreaDibujo())) {
					delete this->Barney;
					this->Barney = nullptr;
					this->gameover = true;
					delete this->enemigos.at(i);
					this->enemigos.erase(this->enemigos.begin() + i);

				}
			}
		}
	}
	
}

Rectangle Controller::obtenerSubImagen(Bitmap^ img) {

	Rectangle f;

	this->indice_esc >= 1280 ? this->indice_esc = 1 : this->indice_esc += 10;

	f = Rectangle(indice_esc, 0, 640, img->Height);

	return f;
}

void Controller::Restart(Size _Client) {
	if (this->Barney == nullptr) {
		this->gameover = false;
		this->Barney = new Dino(_Client);
		this->enemigos.clear();
	}
		
		
}