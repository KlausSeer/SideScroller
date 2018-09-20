#pragma once
#include "Header.h"
#include "TaskList.h"
Controlador* controller;

void Saltar()
{
	controller->dino_Saltar();
}

void Pararse()
{
	controller->dino_Parate();
}

void Agacharse()
{
	controller->dino_Agachate();
}

namespace TrabajoParcialVersion2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		Graphics^ graficador;
		BufferedGraphicsContext^ espaceBuffer;
		BufferedGraphics^ buffer;
		Bitmap^ scenario;
		Bitmap^ spriteDin;
		TaskList* Tareas;
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->graficador = this->CreateGraphics();
			this->espaceBuffer = BufferedGraphicsManager::Current;
			this->buffer = this->espaceBuffer->Allocate(this->graficador, this->ClientRectangle);
			this->scenario = gcnew Bitmap("Recursos\\Escenario.png");
			this->spriteDin = gcnew Bitmap("Recursos\\Sprite.png");
			this->spriteDin->MakeTransparent(Color(this->spriteDin->GetPixel(0, 0)));
			this->Tareas = new TaskList();
			controller = new Controlador(this->ClientSize);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
				//delete controller;
			}

		}
	private: System::Windows::Forms::Timer^  timer1;
	protected:
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

		float timeDelay = 2.0f;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 70;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::animar);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(806, 325);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::Interaction_Key_Down);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::Interaction_Key_Press);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::Interaction_Key_Up);
			this->ResumeLayout(false);

		}
#pragma endregion

		void Añadir(void(*Fun)())
		{
			Task* nueva = new Task(Fun);
			Tareas->newTask(nueva);
		}


	private: System::Void animar(System::Object^  sender, System::EventArgs^  e) {

		Tareas->doTasks(timeDelay);
		controller->animar(this->buffer->Graphics, this->spriteDin, this->scenario);
		Tareas->CheckLive();
		this->buffer->Render();
	}
	private: System::Void Interaction_Key_Down(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		switch (e->KeyCode)
		{
		case Keys::Up:
			if (!(controller->En_el_aire())) {
				//INSERT DELAY HERE !!! <<<-----<<-----<<<<----<<<<------<<<<-----<<<-------<<<<
				//Saltar(); break;
				Añadir(Saltar); break;
			}
		case Keys::Down:
			//INSERT DELAY HERE !!! <<<-----<<-----<<<<----<<<<------<<<<-----<<<-------<<<<
			Añadir(Agacharse); break;
			break;
		default:
			break;
		}
	}


	private: System::Void Interaction_Key_Up(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		switch (e->KeyCode)
		{
		case Keys::Down:
			//INSERT DELAY HERE<<<----------------------------<-<-<-<-<-<--<-<-<<-<<
			Añadir(Pararse);
			break;
		default:
			break;

		}
	}
	private: System::Void Interaction_Key_Press(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {

	}
	};
}
