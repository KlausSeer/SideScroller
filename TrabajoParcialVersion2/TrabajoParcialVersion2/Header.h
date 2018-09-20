#pragma once
using namespace System::Drawing;


class Dino {

	Size Client;
	Rectangle areaDibujo;
	int indice;
	bool agachado;
	bool enAire;
	bool haciaArriba;

public:
	Dino(Size _Client) {
		//1294, 343
		this->Client = _Client;
		this->areaDibujo.X = int(_Client.Width / 3.5);
		this->areaDibujo.Y = int(_Client.Height / 2.16);
		this->areaDibujo.Width = 50;
		this->areaDibujo.Height = 75;
		this->indice = 0;						 // Sprite Indice: 0,1
		this->agachado = false; // Sprite Indice: 2,3
		this->enAire = false;
		this->haciaArriba = false;


	}

	void agachate() {
		this->agachado = true;
	}
	void parate() {
		this->agachado = false;
	}

	Rectangle get_Posicion() {
		return this->areaDibujo;
	}

	void realizarSalto() {
		this->areaDibujo.Y -= 15;//CambioPosInicialenY
		this->enAire = true;
		this->haciaArriba = true;
	}

	void Dibujar(Graphics^ g, Bitmap^ img) {

		g->DrawImage(img, retornarAreaDibujo(), retornarFoco(img), GraphicsUnit::Pixel);

	}
	Rectangle retornarAreaDibujo() {
		if (this->enAire) {
			if (this->haciaArriba && this->areaDibujo.Y > int(this->Client.Height / 2.16) - 90) {
				this->areaDibujo.Y -= 15;
			}
			else {
				this->haciaArriba = false;
				this->areaDibujo.Y += 18;

				if (this->areaDibujo.Y == int(this->Client.Height / 2.16)) {
					this->enAire = false;

				}

			}
		}
		else {
			this->areaDibujo.Y = int(this->Client.Height / 2.16);
		}

		return this->areaDibujo;
	}
	Rectangle retornarFoco(Bitmap^ img) {

		Rectangle f;

		if (agachado) {
			this->indice == 2 ? this->indice = 3 : this->indice = 2;
		}
		else {
			this->indice == 0 ? this->indice = 1 : this->indice = 0;
		}

		f = Rectangle(indice*(img->Width / 4), 0, img->Width / 4, img->Height);

		return f;
	}

	bool get_en_el_Aire() {
		return this->enAire;
	}
};

class Controlador {
	Size Client;
	Dino* Barney;
	int indice_esc;
public:
	Controlador(Size _Client) {
		this->Client = _Client;
		this->Barney = new Dino(_Client);
		this->indice_esc = 0;
	}

	~Controlador() {
		delete Barney;
	}

	void animar(Graphics^ g, Bitmap^ img1, Bitmap^ img2) {


		g->Clear(Color::White);
		this->dibujar_Escenario(g, img2);

		this->Barney->Dibujar(g, img1);

	}

	void dino_Saltar() {
		this->Barney->realizarSalto();
	}

	void dino_Agachate() {
		this->Barney->agachate();
	}
	void dino_Parate() {
		this->Barney->parate();
	}
	bool En_el_aire() {
		return this->Barney->get_en_el_Aire();
	}

	void dibujar_Escenario(Graphics^ g, Bitmap^ img) {

		g->DrawImage(img, Rectangle(0, 0, Client.Width, Client.Height), obtenerSubImagen(img), GraphicsUnit::Pixel);
	}

	Rectangle obtenerSubImagen(Bitmap^ img) {

		Rectangle f;

		this->indice_esc > 4530 ? this->indice_esc = 0 : this->indice_esc += 10;

		f = Rectangle(indice_esc, 0, 700, img->Height);

		return f;
	}
};
