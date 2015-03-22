#pragma once
#include <windows.h>
#using "system.dll"

namespace SwagBot {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;
	//using namespace System::Text;
	//using namespace System::Windows::Input;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form {
	public:
		MyForm(void) {
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm() {
			if (components) {
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  cmdConnect;
	private: System::Windows::Forms::ComboBox^  cmbComm;
	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::Button^  cmdDisconnect;
	private: System::Windows::Forms::Timer^  tmrGetData;
	private: System::Windows::Forms::GroupBox^  frmSensor;
	private: System::Windows::Forms::Label^  lblSensor;
	private: System::Windows::Forms::Label^  lblRes0;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  lblRes5;

	private: System::Windows::Forms::Label^  lblRes4;

	private: System::Windows::Forms::Label^  lblRes3;

	private: System::Windows::Forms::Label^  lblRes2;

	private: System::Windows::Forms::Label^  lblRes1;
	private: System::Windows::Forms::PictureBox^  picBack;

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  picFront;
	private: System::Windows::Forms::PictureBox^  picCompass;






	private: System::ComponentModel::IContainer^  components;


	protected:

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
		void InitializeComponent(void) {
			this->components = (gcnew System::ComponentModel::Container());
			this->cmdConnect = (gcnew System::Windows::Forms::Button());
			this->cmbComm = (gcnew System::Windows::Forms::ComboBox());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->cmdDisconnect = (gcnew System::Windows::Forms::Button());
			this->tmrGetData = (gcnew System::Windows::Forms::Timer(this->components));
			this->frmSensor = (gcnew System::Windows::Forms::GroupBox());
			this->picFront = (gcnew System::Windows::Forms::PictureBox());
			this->picBack = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->lblRes5 = (gcnew System::Windows::Forms::Label());
			this->lblRes4 = (gcnew System::Windows::Forms::Label());
			this->lblRes3 = (gcnew System::Windows::Forms::Label());
			this->lblRes2 = (gcnew System::Windows::Forms::Label());
			this->lblRes1 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lblRes0 = (gcnew System::Windows::Forms::Label());
			this->lblSensor = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->picCompass = (gcnew System::Windows::Forms::PictureBox());
			this->frmSensor->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picFront))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picCompass))->BeginInit();
			this->SuspendLayout();
			// 
			// cmdConnect
			// 
			this->cmdConnect->Location = System::Drawing::Point(131, 12);
			this->cmdConnect->Name = L"cmdConnect";
			this->cmdConnect->Size = System::Drawing::Size(75, 21);
			this->cmdConnect->TabIndex = 0;
			this->cmdConnect->TabStop = false;
			this->cmdConnect->Text = L"Connect";
			this->cmdConnect->UseVisualStyleBackColor = true;
			this->cmdConnect->Click += gcnew System::EventHandler(this, &MyForm::cmdConnect_Click);
			// 
			// cmbComm
			// 
			this->cmbComm->FormattingEnabled = true;
			this->cmbComm->Location = System::Drawing::Point(12, 12);
			this->cmbComm->Name = L"cmbComm";
			this->cmbComm->Size = System::Drawing::Size(113, 21);
			this->cmbComm->TabIndex = 1;
			this->cmbComm->TabStop = false;
			// 
			// cmdDisconnect
			// 
			this->cmdDisconnect->Enabled = false;
			this->cmdDisconnect->Location = System::Drawing::Point(212, 12);
			this->cmdDisconnect->Name = L"cmdDisconnect";
			this->cmdDisconnect->Size = System::Drawing::Size(75, 21);
			this->cmdDisconnect->TabIndex = 2;
			this->cmdDisconnect->TabStop = false;
			this->cmdDisconnect->Text = L"Disconnect";
			this->cmdDisconnect->UseVisualStyleBackColor = true;
			this->cmdDisconnect->Click += gcnew System::EventHandler(this, &MyForm::cmdDisconnect_Click);
			// 
			// tmrGetData
			// 
			this->tmrGetData->Interval = 10;
			this->tmrGetData->Tick += gcnew System::EventHandler(this, &MyForm::tmrGetData_Tick);
			// 
			// frmSensor
			// 
			this->frmSensor->Controls->Add(this->picFront);
			this->frmSensor->Controls->Add(this->picBack);
			this->frmSensor->Controls->Add(this->pictureBox1);
			this->frmSensor->Controls->Add(this->lblRes5);
			this->frmSensor->Controls->Add(this->lblRes4);
			this->frmSensor->Controls->Add(this->lblRes3);
			this->frmSensor->Controls->Add(this->lblRes2);
			this->frmSensor->Controls->Add(this->lblRes1);
			this->frmSensor->Controls->Add(this->label5);
			this->frmSensor->Controls->Add(this->label4);
			this->frmSensor->Controls->Add(this->label3);
			this->frmSensor->Controls->Add(this->label2);
			this->frmSensor->Controls->Add(this->label1);
			this->frmSensor->Controls->Add(this->lblRes0);
			this->frmSensor->Controls->Add(this->lblSensor);
			this->frmSensor->Controls->Add(this->pictureBox3);
			this->frmSensor->Location = System::Drawing::Point(12, 67);
			this->frmSensor->Name = L"frmSensor";
			this->frmSensor->Size = System::Drawing::Size(322, 108);
			this->frmSensor->TabIndex = 4;
			this->frmSensor->TabStop = false;
			this->frmSensor->Text = L"Live SensorData";
			this->frmSensor->Enter += gcnew System::EventHandler(this, &MyForm::groupBox1_Enter);
			// 
			// picFront
			// 
			this->picFront->BackColor = System::Drawing::Color::Lime;
			this->picFront->Location = System::Drawing::Point(276, 55);
			this->picFront->Name = L"picFront";
			this->picFront->Size = System::Drawing::Size(35, 42);
			this->picFront->TabIndex = 18;
			this->picFront->TabStop = false;
			// 
			// picBack
			// 
			this->picBack->BackColor = System::Drawing::Color::White;
			this->picBack->Location = System::Drawing::Point(274, 20);
			this->picBack->Name = L"picBack";
			this->picBack->Size = System::Drawing::Size(39, 79);
			this->picBack->TabIndex = 16;
			this->picBack->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->pictureBox1->Location = System::Drawing::Point(272, 18);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(43, 83);
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			// 
			// lblRes5
			// 
			this->lblRes5->Location = System::Drawing::Point(116, 81);
			this->lblRes5->Name = L"lblRes5";
			this->lblRes5->Size = System::Drawing::Size(78, 13);
			this->lblRes5->TabIndex = 15;
			this->lblRes5->Text = L"N/A";
			// 
			// lblRes4
			// 
			this->lblRes4->Location = System::Drawing::Point(116, 68);
			this->lblRes4->Name = L"lblRes4";
			this->lblRes4->Size = System::Drawing::Size(78, 13);
			this->lblRes4->TabIndex = 14;
			this->lblRes4->Text = L"N/A";
			// 
			// lblRes3
			// 
			this->lblRes3->Location = System::Drawing::Point(116, 55);
			this->lblRes3->Name = L"lblRes3";
			this->lblRes3->Size = System::Drawing::Size(78, 13);
			this->lblRes3->TabIndex = 13;
			this->lblRes3->Text = L"N/A";
			// 
			// lblRes2
			// 
			this->lblRes2->Location = System::Drawing::Point(116, 42);
			this->lblRes2->Name = L"lblRes2";
			this->lblRes2->Size = System::Drawing::Size(78, 13);
			this->lblRes2->TabIndex = 12;
			this->lblRes2->Text = L"N/A";
			// 
			// lblRes1
			// 
			this->lblRes1->Location = System::Drawing::Point(116, 29);
			this->lblRes1->Name = L"lblRes1";
			this->lblRes1->Size = System::Drawing::Size(78, 13);
			this->lblRes1->TabIndex = 11;
			this->lblRes1->Text = L"N/A";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 81);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(71, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"BumperRight:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 68);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(64, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"BumperLeft:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 55);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(99, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"UltrasonicDistance:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 42);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(58, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"LedStatus:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 29);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 13);
			this->label1->TabIndex = 6;
			this->label1->Text = L"MotorRight";
			// 
			// lblRes0
			// 
			this->lblRes0->Location = System::Drawing::Point(116, 16);
			this->lblRes0->Name = L"lblRes0";
			this->lblRes0->Size = System::Drawing::Size(78, 13);
			this->lblRes0->TabIndex = 5;
			this->lblRes0->Text = L"N/A";
			// 
			// lblSensor
			// 
			this->lblSensor->AutoSize = true;
			this->lblSensor->Location = System::Drawing::Point(6, 16);
			this->lblSensor->Name = L"lblSensor";
			this->lblSensor->Size = System::Drawing::Size(58, 13);
			this->lblSensor->TabIndex = 4;
			this->lblSensor->Text = L"MotorLeft: ";
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->pictureBox3->Location = System::Drawing::Point(282, 12);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(23, 15);
			this->pictureBox3->TabIndex = 17;
			this->pictureBox3->TabStop = false;
			// 
			// picCompass
			// 
			this->picCompass->BackColor = System::Drawing::Color::Gray;
			this->picCompass->Location = System::Drawing::Point(12, 181);
			this->picCompass->Name = L"picCompass";
			this->picCompass->Size = System::Drawing::Size(80, 80);
			this->picCompass->TabIndex = 5;
			this->picCompass->TabStop = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(346, 328);
			this->Controls->Add(this->picCompass);
			this->Controls->Add(this->frmSensor);
			this->Controls->Add(this->cmdDisconnect);
			this->Controls->Add(this->cmbComm);
			this->Controls->Add(this->cmdConnect);
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->frmSensor->ResumeLayout(false);
			this->frmSensor->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picFront))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picCompass))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		String ^buffertest;

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 loadCommports();
				 setPercentage(1);

	}

	private: System::Void MyForm_KeyDown(Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
				 e->SuppressKeyPress = true;
	}


	private: System::Void MyForm_Unload(System::Object^  sender, System::EventArgs^  e) {
				 if (this->serialPort1->IsOpen) {
					 this->serialPort1->Close();
				 }
	}

	private: void loadCommports() {
				 this->cmbComm->Items->AddRange(serialPort1->GetPortNames());
				 if (this->cmbComm->Items->Count > 0) {
					 this->cmbComm->SelectedIndex = 0;
				 }
	}



	private: System::Void cmdConnect_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->cmbComm->SelectedIndex != -1) {

					 this->serialPort1->PortName = this->cmbComm->Text;
					 this->serialPort1->Open();
					 if (this->serialPort1->IsOpen) {
						 //serialPort1->Write("w");
						 setControlstate(false);

					 } else {
						 MessageBox::Show("Could not open '" + this->cmbComm->Text + "'!");
						 setControlstate(true);
					 }
				 }
	}

	private: void setControlstate(bool EnableControls) {
				 if (!EnableControls) {
					 this->tmrGetData->Enabled = true;
					 
					 this->cmdDisconnect->Enabled = true;
					 this->cmdConnect->Enabled = false;

					 this->cmbComm->Enabled = false;
					 this->Focus();

				 } else {
					 this->cmdDisconnect->Enabled = false;
					 this->cmdConnect->Enabled = false;

					 this->cmbComm->Enabled = true;
				 }
	}

	private: System::Void tmrGetData_Tick(System::Object^  sender, System::EventArgs^  e) {
				 char gchar;
				 array<String^>^ sensordata;

				 if (!this->serialPort1->IsOpen) return;

				 while (this->serialPort1->BytesToRead > 0) {
					 gchar = this->serialPort1->ReadChar();
					 if (gchar == ';') { //end of bufferdata
						 if (buffertest->Length > 10) {
							 sensordata = buffertest->Split(':');
							 buffertest = "";
							 if (sensordata->Length == 7) {
								 this->lblRes0->Text = sensordata[0];
								 this->lblRes1->Text = sensordata[1];
								 this->lblRes2->Text = sensordata[2];
								 this->lblRes3->Text = sensordata[3];
								 this->lblRes4->Text = sensordata[4];
								 this->lblRes5->Text = sensordata[5];
								 setPercentage(Convert::ToInt16(sensordata[6]));
							 }
						 }
					 } else {
						 buffertest += "" + Convert::ToChar(gchar);
					 }
				 }

				 if (GetAsyncKeyState(0x57)) {
					 this->serialPort1->Write("w");

				 } else if (GetAsyncKeyState(0x41)) {
					 this->serialPort1->Write("a");

				 } else if (GetAsyncKeyState(0x44)) {
					 this->serialPort1->Write("d");

				 } else if (GetAsyncKeyState(0x53)) {
					 this->serialPort1->Write("s");

				 } else if (GetAsyncKeyState(0x53)) {
					 this->serialPort1->Write("s");

				 } else if (GetAsyncKeyState(0x50)) {
					 this->serialPort1->Write("p");

				 } else if (GetAsyncKeyState(0x4D)) {
					 this->serialPort1->Write("m");

				 } else if (GetAsyncKeyState(0x4E)) {
					 this->serialPort1->Write("n");

				 }
	}


	private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {

	}

	private: System::Void cmdDisconnect_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->serialPort1->IsOpen) {
					 this->serialPort1->Close();
					 setControlstate(true);
				 }
	}

	private: void setPercentage(int percentage) {
				 if (percentage < 0) percentage = 0;
				 if (percentage > 100) percentage = 100;

				 this->picFront->Height = 75.0 / 100.0 * percentage;
				 this->picFront->Top = this->picBack->Top + (this->picBack->Height - this->picFront->Height - 2);

				 this->picFront->Refresh();
	}

	private: void pictureBox1_Paint(Object^ sender, System::Windows::Forms::PaintEventArgs^ e){
		/*Pen^ blackPen = gcnew Pen(Color::Black, 3.0f);

		// Create points that define line.
		Point point1 = Point(100, 100);
		Point point2 = Point(500, 100);

		// Draw line to screen.
		e->Graphics->DrawLine(blackPen, point1, point2);

		*/


	}
};
}
