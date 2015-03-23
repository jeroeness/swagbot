#pragma once
#include <windows.h>
#using "System.Drawing.dll"
#include <math.h>

namespace SwagBot {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;

	using namespace System::Text;

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



	private: System::Windows::Forms::Label^  lblRes1;
	private: System::Windows::Forms::PictureBox^  picBack;

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  picFront;
	private: System::Windows::Forms::PictureBox^  picCompass;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::PictureBox^  picLed0;
	private: System::Windows::Forms::PictureBox^  picLed7;

	private: System::Windows::Forms::PictureBox^  picLed6;

	private: System::Windows::Forms::PictureBox^  picLed5;

	private: System::Windows::Forms::PictureBox^  picLed4;

	private: System::Windows::Forms::PictureBox^  picLed3;

	private: System::Windows::Forms::PictureBox^  picLed2;

	private: System::Windows::Forms::PictureBox^  picLed1;
	private: System::Windows::Forms::Button^  cmdRefresh;
	private: System::Windows::Forms::Button^  button1;









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
			this->picLed7 = (gcnew System::Windows::Forms::PictureBox());
			this->picLed6 = (gcnew System::Windows::Forms::PictureBox());
			this->picLed5 = (gcnew System::Windows::Forms::PictureBox());
			this->picLed4 = (gcnew System::Windows::Forms::PictureBox());
			this->picLed3 = (gcnew System::Windows::Forms::PictureBox());
			this->picLed2 = (gcnew System::Windows::Forms::PictureBox());
			this->picLed1 = (gcnew System::Windows::Forms::PictureBox());
			this->picLed0 = (gcnew System::Windows::Forms::PictureBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->lblRes5 = (gcnew System::Windows::Forms::Label());
			this->lblRes4 = (gcnew System::Windows::Forms::Label());
			this->lblRes3 = (gcnew System::Windows::Forms::Label());
			this->lblRes1 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lblRes0 = (gcnew System::Windows::Forms::Label());
			this->lblSensor = (gcnew System::Windows::Forms::Label());
			this->picCompass = (gcnew System::Windows::Forms::PictureBox());
			this->picFront = (gcnew System::Windows::Forms::PictureBox());
			this->picBack = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->cmdRefresh = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->frmSensor->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed0))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picCompass))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picFront))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// cmdConnect
			// 
			this->cmdConnect->Location = System::Drawing::Point(174, 11);
			this->cmdConnect->Name = L"cmdConnect";
			this->cmdConnect->Size = System::Drawing::Size(75, 23);
			this->cmdConnect->TabIndex = 0;
			this->cmdConnect->TabStop = false;
			this->cmdConnect->Text = L"Connect";
			this->cmdConnect->UseVisualStyleBackColor = true;
			this->cmdConnect->Click += gcnew System::EventHandler(this, &MyForm::cmdConnect_Click);
			// 
			// cmbComm
			// 
			this->cmbComm->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbComm->FormattingEnabled = true;
			this->cmbComm->Location = System::Drawing::Point(12, 12);
			this->cmbComm->Name = L"cmbComm";
			this->cmbComm->Size = System::Drawing::Size(75, 21);
			this->cmbComm->TabIndex = 1;
			this->cmbComm->TabStop = false;
			// 
			// serialPort1
			// 
			this->serialPort1->DiscardNull = true;
			// 
			// cmdDisconnect
			// 
			this->cmdDisconnect->Enabled = false;
			this->cmdDisconnect->Location = System::Drawing::Point(255, 11);
			this->cmdDisconnect->Name = L"cmdDisconnect";
			this->cmdDisconnect->Size = System::Drawing::Size(75, 23);
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
			this->frmSensor->Controls->Add(this->picLed7);
			this->frmSensor->Controls->Add(this->picLed6);
			this->frmSensor->Controls->Add(this->picLed5);
			this->frmSensor->Controls->Add(this->picLed4);
			this->frmSensor->Controls->Add(this->picLed3);
			this->frmSensor->Controls->Add(this->picLed2);
			this->frmSensor->Controls->Add(this->picLed1);
			this->frmSensor->Controls->Add(this->picLed0);
			this->frmSensor->Controls->Add(this->label6);
			this->frmSensor->Controls->Add(this->lblRes5);
			this->frmSensor->Controls->Add(this->lblRes4);
			this->frmSensor->Controls->Add(this->lblRes3);
			this->frmSensor->Controls->Add(this->lblRes1);
			this->frmSensor->Controls->Add(this->label5);
			this->frmSensor->Controls->Add(this->label4);
			this->frmSensor->Controls->Add(this->label3);
			this->frmSensor->Controls->Add(this->label2);
			this->frmSensor->Controls->Add(this->label1);
			this->frmSensor->Controls->Add(this->lblRes0);
			this->frmSensor->Controls->Add(this->lblSensor);
			this->frmSensor->Location = System::Drawing::Point(12, 67);
			this->frmSensor->Name = L"frmSensor";
			this->frmSensor->Size = System::Drawing::Size(322, 108);
			this->frmSensor->TabIndex = 4;
			this->frmSensor->TabStop = false;
			this->frmSensor->Text = L"Live SensorData";
			this->frmSensor->Enter += gcnew System::EventHandler(this, &MyForm::groupBox1_Enter);
			// 
			// picLed7
			// 
			this->picLed7->BackColor = System::Drawing::Color::DarkRed;
			this->picLed7->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed7->Location = System::Drawing::Point(182, 44);
			this->picLed7->Name = L"picLed7";
			this->picLed7->Size = System::Drawing::Size(8, 11);
			this->picLed7->TabIndex = 24;
			this->picLed7->TabStop = false;
			// 
			// picLed6
			// 
			this->picLed6->BackColor = System::Drawing::Color::DarkRed;
			this->picLed6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed6->Location = System::Drawing::Point(173, 44);
			this->picLed6->Name = L"picLed6";
			this->picLed6->Size = System::Drawing::Size(8, 11);
			this->picLed6->TabIndex = 23;
			this->picLed6->TabStop = false;
			// 
			// picLed5
			// 
			this->picLed5->BackColor = System::Drawing::Color::DarkRed;
			this->picLed5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed5->Location = System::Drawing::Point(164, 44);
			this->picLed5->Name = L"picLed5";
			this->picLed5->Size = System::Drawing::Size(8, 11);
			this->picLed5->TabIndex = 22;
			this->picLed5->TabStop = false;
			// 
			// picLed4
			// 
			this->picLed4->BackColor = System::Drawing::Color::DarkRed;
			this->picLed4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed4->Location = System::Drawing::Point(155, 44);
			this->picLed4->Name = L"picLed4";
			this->picLed4->Size = System::Drawing::Size(8, 11);
			this->picLed4->TabIndex = 21;
			this->picLed4->TabStop = false;
			// 
			// picLed3
			// 
			this->picLed3->BackColor = System::Drawing::Color::DarkGreen;
			this->picLed3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed3->Location = System::Drawing::Point(146, 44);
			this->picLed3->Name = L"picLed3";
			this->picLed3->Size = System::Drawing::Size(8, 11);
			this->picLed3->TabIndex = 20;
			this->picLed3->TabStop = false;
			// 
			// picLed2
			// 
			this->picLed2->BackColor = System::Drawing::Color::DarkRed;
			this->picLed2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed2->Location = System::Drawing::Point(137, 44);
			this->picLed2->Name = L"picLed2";
			this->picLed2->Size = System::Drawing::Size(8, 11);
			this->picLed2->TabIndex = 19;
			this->picLed2->TabStop = false;
			// 
			// picLed1
			// 
			this->picLed1->BackColor = System::Drawing::Color::DarkRed;
			this->picLed1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed1->Location = System::Drawing::Point(128, 44);
			this->picLed1->Name = L"picLed1";
			this->picLed1->Size = System::Drawing::Size(8, 11);
			this->picLed1->TabIndex = 18;
			this->picLed1->TabStop = false;
			// 
			// picLed0
			// 
			this->picLed0->BackColor = System::Drawing::Color::DarkGreen;
			this->picLed0->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed0->Location = System::Drawing::Point(119, 44);
			this->picLed0->Name = L"picLed0";
			this->picLed0->Size = System::Drawing::Size(8, 11);
			this->picLed0->TabIndex = 17;
			this->picLed0->TabStop = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(200, 16);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(37, 13);
			this->label6->TabIndex = 16;
			this->label6->Text = L"Mode:";
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
			// picCompass
			// 
			this->picCompass->Location = System::Drawing::Point(12, 181);
			this->picCompass->Name = L"picCompass";
			this->picCompass->Size = System::Drawing::Size(160, 160);
			this->picCompass->TabIndex = 5;
			this->picCompass->TabStop = false;
			this->picCompass->Click += gcnew System::EventHandler(this, &MyForm::picCompass_Click);
			this->picCompass->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::picCompass_Paint);
			// 
			// picFront
			// 
			this->picFront->BackColor = System::Drawing::Color::Lime;
			this->picFront->Location = System::Drawing::Point(188, 224);
			this->picFront->Name = L"picFront";
			this->picFront->Size = System::Drawing::Size(35, 113);
			this->picFront->TabIndex = 18;
			this->picFront->TabStop = false;
			// 
			// picBack
			// 
			this->picBack->BackColor = System::Drawing::Color::White;
			this->picBack->Location = System::Drawing::Point(186, 189);
			this->picBack->Name = L"picBack";
			this->picBack->Size = System::Drawing::Size(39, 150);
			this->picBack->TabIndex = 16;
			this->picBack->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Gray;
			this->pictureBox1->Location = System::Drawing::Point(184, 187);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(43, 154);
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::Gray;
			this->pictureBox3->Location = System::Drawing::Point(194, 181);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(23, 15);
			this->pictureBox3->TabIndex = 17;
			this->pictureBox3->TabStop = false;
			// 
			// cmdRefresh
			// 
			this->cmdRefresh->Location = System::Drawing::Point(93, 11);
			this->cmdRefresh->Name = L"cmdRefresh";
			this->cmdRefresh->Size = System::Drawing::Size(75, 23);
			this->cmdRefresh->TabIndex = 19;
			this->cmdRefresh->TabStop = false;
			this->cmdRefresh->Text = L"Refresh";
			this->cmdRefresh->UseVisualStyleBackColor = true;
			this->cmdRefresh->Click += gcnew System::EventHandler(this, &MyForm::cmdRefresh_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(383, 67);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 20;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(495, 370);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->cmdRefresh);
			this->Controls->Add(this->picFront);
			this->Controls->Add(this->picBack);
			this->Controls->Add(this->picCompass);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->frmSensor);
			this->Controls->Add(this->cmdDisconnect);
			this->Controls->Add(this->cmbComm);
			this->Controls->Add(this->cmdConnect);
			this->Controls->Add(this->pictureBox3);
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->frmSensor->ResumeLayout(false);
			this->frmSensor->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed0))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picCompass))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picFront))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	String ^buffertest;
	int compassDegrees = 0;
	double PI = 3.14159265359;

	public: static array<int>^ keyCode = gcnew array<int>(7) { 0x57, 0x41, 0x44, 0x53, 0x50, 0x4D, 0x4E };
	public: static array<bool>^ keyDown = gcnew array<bool>(7) { false, false, false, false, false, false, false };
	public: static array<char>^ keySendUp = gcnew array<char>(7) { 'W', 'A', 'D', 'S', 'P', 'M', 'N' };
	public: static array<char>^ keySendDown = gcnew array<char>(7) { 'w', 'a', 'd', 's', 'p', 'm', 'n' };



	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
				 loadCommports();
				 setPercentage(100);

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
				this->cmbComm->Items->Clear();
				this->cmbComm->Items->AddRange(serialPort1->GetPortNames());
				if (this->cmbComm->Items->Count > 0) {
					this->cmbComm->SelectedIndex = 0;
				}
	}



	private: System::Void cmdConnect_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->cmbComm->SelectedIndex != -1) {

					 this->serialPort1->PortName = this->cmbComm->Text;
					 this->serialPort1->Parity = System::IO::Ports::Parity::None;
					 this->serialPort1->DataBits = 8;

					 this->serialPort1->Open();
					 if (this->serialPort1->IsOpen) {
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
					 this->cmdRefresh->Enabled = false;

					 this->cmbComm->Enabled = false;

					 this->Focus();
				 } else {
					 this->cmdDisconnect->Enabled = false;
					 this->cmdConnect->Enabled = true;
					 this->cmdRefresh->Enabled = true;

					 this->cmbComm->Enabled = true;
				 }
	}

	private: System::Void tmrGetData_Tick(System::Object^  sender, System::EventArgs^  e) {
				 int gchar;
				 array<wchar_t>^ sensordata;

				 if (!this->serialPort1->IsOpen) return;

				 while (this->serialPort1->BytesToRead > 0) {
					 //gchar = this->serialPort1->ReadChar();
					 gchar = this->serialPort1->ReadByte();

					 if (gchar == 255) { //end of bufferdata
						 sensordata = buffertest->ToCharArray();//->Split(':');
						 buffertest = "";
						 if (sensordata->Length == 8) {
							 this->lblRes0->Text = "" + (sensordata[0] - 128);
							 this->lblRes1->Text = "" + (sensordata[1] - 128);
							 int leds = sensordata[2];

							 if (1 & leds) {
								 this->picLed0->BackColor = Color::Lime;
							 } else {
								 this->picLed0->BackColor = Color::DarkGreen;
							 }
							 if (2 & leds) {
								 this->picLed1->BackColor = Color::Red;
							 } else {
								 this->picLed1->BackColor = Color::DarkRed;
							 }
							 if (4 & leds) {
								 this->picLed2->BackColor = Color::Red;
							 } else {
								 this->picLed2->BackColor = Color::DarkRed;
							 }
							 if (8 & leds) {
								 this->picLed3->BackColor = Color::Lime;
							 } else {
								 this->picLed3->BackColor = Color::DarkGreen;
							 }
							 if (16 & leds) {
								 this->picLed4->BackColor = Color::Red;
							 } else {
								 this->picLed4->BackColor = Color::DarkRed;
							 }
							 if (32 & leds) {
								 this->picLed5->BackColor = Color::Red;
							 } else {
								 this->picLed5->BackColor = Color::DarkRed;
							 }
							 if (64 & leds) {
								 this->picLed6->BackColor = Color::Red;
							 } else {
								 this->picLed6->BackColor = Color::DarkRed;
							 }
							 if (128 & leds) {
								 this->picLed7->BackColor = Color::Red;
							 } else {
								 this->picLed7->BackColor = Color::DarkRed;
							 }

							 this->lblRes3->Text = (Convert::ToUInt16(sensordata[3])).ToString();
							 this->lblRes4->Text = "" + Convert::ToUInt16(sensordata[4]);
							 this->lblRes5->Text = "" + Convert::ToUInt16(sensordata[5]);
							 setPercentage(sensordata[6]);
							 compassDegrees = Convert::ToUInt16(sensordata[7]);
							 this->picCompass->Refresh();
						 }
					 } else {
						 buffertest += "" + Convert::ToChar(gchar);
					 }
				 }

				 int i = 0;

				 for (i = 0; i < 7; i++) {
					 if (GetAsyncKeyState(keyCode[i])) {
						 if (!keyDown[i]) {
							 this->serialPort1->Write(Convert::ToString(keySendUp[i]));
							 keyDown[i] = true;
						 }
					 } else {
						 if (keyDown[i]) {
							 keyDown[i] = false;
							 this->serialPort1->Write(Convert::ToString(keySendUp[i]));
						 }
					 }
				 }

	}


	private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {

	}

	private: System::Void cmdDisconnect_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->serialPort1->IsOpen) {
					 this->tmrGetData->Enabled = false;
					 this->serialPort1->Close();
					 setControlstate(true);
				 }
	}

	private: void setPercentage(int percentage) {
				 if (percentage < 0) percentage = 0;
				 if (percentage > 100) percentage = 100;

				 this->picFront->Height = (this->picBack->Height - 4) / 100.0 * percentage;
				 this->picFront->Top = this->picBack->Top + (this->picBack->Height - this->picFront->Height - 2);

				 this->picFront->Refresh();
	}

	private: double byteToDeg(int x) {
				 return (double)x / 128.0 * PI - (0.499*PI);
	}

	private: void picCompass_Paint(Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
				 Pen^ redPen = gcnew Pen(Color::Red, 3.0f);
				 Pen^ blackPen = gcnew Pen(Color::Black, 2.0f);
				 Pen^ backgroundPen = gcnew Pen(Color::Gray, 3.0f);
				 StringFormat^ alignText = gcnew StringFormat;
				 String ^ degrees = "" + Math::Round(compassDegrees / 255.0 * 360.0);

				 System::Drawing::Font^ myFont = gcnew System::Drawing::Font("consolas", 14);

				 int size = 160 / 2;


				 // Create points that define line.
				 Point point1 = Point(size, size);

				 e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

				 float x = byteToDeg(compassDegrees);
				 Point point2 = Point(Math::Cos(x) * (size*0.7) + size, Math::Sin(x) * (size*0.7) + size);
				 Point point3 = Point(Math::Cos(x) * (-size*0.7) + size, Math::Sin(x) * (-size*0.7) + size);


				 e->Graphics->DrawEllipse(backgroundPen, 2, 2, size * 2 - 4, size * 2 - 4);
				 e->Graphics->FillEllipse(Brushes::White, 2, 2, size * 2 - 4, size * 2 - 4);

				 e->Graphics->DrawLine(redPen, point1, point2);
				 e->Graphics->DrawLine(blackPen, point1, point3);

				 e->Graphics->FillEllipse(Brushes::White, (int)(size - 14 * 1.5), (int)(size - 14 * 1.5), (int)(14 * 3), (int)(14 * 3));


				 alignText->Alignment = StringAlignment::Center;
				 alignText->LineAlignment = StringAlignment::Center;

				 e->Graphics->DrawString(degrees, myFont, Brushes::Blue, point1.X, point1.Y, alignText);

				 e->Graphics->DrawString("N", myFont, Brushes::Blue, size, 15, alignText);
				 e->Graphics->DrawString("E", myFont, Brushes::Blue, size * 2 - 10, size, alignText);
				 e->Graphics->DrawString("S", myFont, Brushes::Blue, size, size * 2 - 10, alignText);
				 e->Graphics->DrawString("W", myFont, Brushes::Blue, 10, size, alignText);

	}


	private: System::Void picCompass_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->picCompass->Refresh();
	}


	private: System::Void cmdRefresh_Click(System::Object^  sender, System::EventArgs^  e) {
				 loadCommports();
	}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 compassDegrees += 10;
			 this->picCompass->Refresh();
}
};
}
