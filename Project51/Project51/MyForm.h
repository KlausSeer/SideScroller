#pragma once
#include "TaskList.h"
#include "Controller.h"

Controller* controller;

void Saltar()
{
	controller->dino_Saltar();
}



namespace LagRunner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:

		Graphics^ graficador;
		BufferedGraphicsContext^ espaceBuffer;
		BufferedGraphics^ buffer;
		System::Drawing::Font^ fuente;
		System::Drawing::Font^ fuenteS;

		TaskList* Tareas;

		Bitmap^ scenario;
		Bitmap^ spriteDin;
		Bitmap^ car;
		SoundPlayer^ lvlsong;
		SoundPlayer^ youLose;

		float timeDelay = 1.5f;
		float timeElapsed = 0.0f;
		int Score = 0;




		
	private: System::Windows::Forms::Timer^  MyTimer;

			 
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
			this->scenario = gcnew Bitmap("Resources\\Scenario.png");
			this->spriteDin = gcnew Bitmap("Resources\\Sprite.png");
			this->car = gcnew Bitmap("Resources\\Enemy.png");
			this->spriteDin->MakeTransparent(Color(this->spriteDin->GetPixel(0, 0)));
			this->car->MakeTransparent(Color(this->car->GetPixel(0, 0)));
			this->Tareas = new TaskList();
			this->lvlsong = gcnew SoundPlayer("Resources\\naruto.wav");
			this->youLose = gcnew SoundPlayer("Resources\\youlose.wav");
			controller = new Controller(this->ClientSize);
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
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

	
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->MyTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// MyTimer
			// 
			this->MyTimer->Enabled = true;
			this->MyTimer->Interval = 45;
			this->MyTimer->Tick += gcnew System::EventHandler(this, &MyForm::animate);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(806, 372);
			this->Name = L"MyForm";
			this->Text = L"Lag Game";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::interaction_Key_Down);
			
			this->ResumeLayout(false);

		}
#pragma endregion
		void Añadir(void(*Fun)())
		{
			Task* nueva = new Task(Fun);
			Tareas->newTask(nueva);
		}

	private: System::Void animate(System::Object^  sender, System::EventArgs^  e) {

		if (!(controller->game_over())) {
			Tareas->doTasks(timeDelay);
			controller->animar(this->buffer->Graphics, this->spriteDin, this->scenario, this->car);
			Tareas->CheckLive();
			this->buffer->Graphics->DrawString("Score: " + Score.ToString(), fuenteS, Brushes::Red, Rectangle(this->ClientSize.Width-210, 15, 300, 60));
			if (timeElapsed > 1)
			{
				Score++;
				timeElapsed = 0.0f;
			}
			if (Score == 0 && timeElapsed == 0.0f)
				lvlsong->Play();
			timeElapsed += 0.05f;
		}	else {
			lvlsong->Stop();
			
			this->buffer->Graphics->DrawString("YOU LOSED", fuente, Brushes::Red, Rectangle(this->ClientRectangle));
			this->Score = 0;
			youLose->Play();

			this->MyTimer->Enabled = false;
			this->buffer->Graphics->DrawString("PRESS R TO RESTART", fuente, Brushes::Green, Rectangle(this->ClientSize.Width - 665, this->ClientSize.Height / 2.4, 800, 60));
			

		}

		this->buffer->Render();
	}
	private: System::Void interaction_Key_Down(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {

		switch (e->KeyCode)
		{
		case Keys::Space:
		
			Añadir(Saltar); break;

		case Keys::R:
			
			controller->Restart(this->ClientSize);
			this->MyTimer->Enabled = true;
			youLose->Stop();
			Score = 0;
			timeElapsed = 0.0f;
			Tareas->Clear();
		
		break;
			
		default:
			break;
		}


	}


	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		fuente = gcnew System::Drawing::Font("Arial", 40);
		fuenteS = gcnew System::Drawing::Font("Arial", 30);
		youLose->Load();
		lvlsong->Load();
	}

};
}
