#pragma once
#include <windows.h>
#using "System.Drawing.dll"
#include <math.h>
//#include <Dwmapi.h>


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



		private: System::Windows::Forms::GroupBox^  frmControls;
		private: System::Windows::Forms::Label^  lblD;

		private: System::Windows::Forms::Label^  lblS;

		private: System::Windows::Forms::Label^  lblA;

		private: System::Windows::Forms::Label^  lblW;
		private: System::Windows::Forms::Label^  lblP;
		private: System::Windows::Forms::Label^  lblM;
		private: System::Windows::Forms::Label^  lblN;
		private: System::Windows::Forms::Label^  lblKeyInfo;
		private: System::Windows::Forms::Label^  lblRes6;
		private: System::Windows::Forms::StatusStrip^  sStrip;
		private: System::Windows::Forms::ToolStripStatusLabel^  lblStatus;
		private: System::Windows::Forms::Timer^  tmrAlive;
		private: System::Windows::Forms::ToolStripStatusLabel^  lblConnection;
		private: System::Windows::Forms::Label^  lblRes7;
		private: System::Windows::Forms::Label^  label7;
		private: System::Windows::Forms::Timer^  tmrRefresh;

		private: System::Windows::Forms::Button^  cmdConnect;
		private: System::Windows::Forms::CheckBox^  chkReconnect;
		private: System::Windows::Forms::Button^  cmdReset;
		private: System::Windows::Forms::GroupBox^  frmArduino;
		private: System::Windows::Forms::Button^  cmdUpload;
		private: System::Windows::Forms::GroupBox^  frmComm;


















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
			this->cmbComm = (gcnew System::Windows::Forms::ComboBox());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->cmdDisconnect = (gcnew System::Windows::Forms::Button());
			this->tmrGetData = (gcnew System::Windows::Forms::Timer(this->components));
			this->frmSensor = (gcnew System::Windows::Forms::GroupBox());
			this->lblRes7 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->lblRes6 = (gcnew System::Windows::Forms::Label());
			this->picLed7 = (gcnew System::Windows::Forms::PictureBox());
			this->picLed6 = (gcnew System::Windows::Forms::PictureBox());
			this->picFront = (gcnew System::Windows::Forms::PictureBox());
			this->picBack = (gcnew System::Windows::Forms::PictureBox());
			this->picLed5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->picLed4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
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
			this->frmControls = (gcnew System::Windows::Forms::GroupBox());
			this->lblKeyInfo = (gcnew System::Windows::Forms::Label());
			this->lblN = (gcnew System::Windows::Forms::Label());
			this->lblD = (gcnew System::Windows::Forms::Label());
			this->lblM = (gcnew System::Windows::Forms::Label());
			this->lblS = (gcnew System::Windows::Forms::Label());
			this->lblA = (gcnew System::Windows::Forms::Label());
			this->lblP = (gcnew System::Windows::Forms::Label());
			this->lblW = (gcnew System::Windows::Forms::Label());
			this->sStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->lblStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->lblConnection = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->tmrAlive = (gcnew System::Windows::Forms::Timer(this->components));
			this->tmrRefresh = (gcnew System::Windows::Forms::Timer(this->components));
			this->cmdConnect = (gcnew System::Windows::Forms::Button());
			this->chkReconnect = (gcnew System::Windows::Forms::CheckBox());
			this->cmdReset = (gcnew System::Windows::Forms::Button());
			this->frmArduino = (gcnew System::Windows::Forms::GroupBox());
			this->cmdUpload = (gcnew System::Windows::Forms::Button());
			this->frmComm = (gcnew System::Windows::Forms::GroupBox());
			this->frmSensor->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picFront))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed0))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picCompass))->BeginInit();
			this->frmControls->SuspendLayout();
			this->sStrip->SuspendLayout();
			this->frmArduino->SuspendLayout();
			this->frmComm->SuspendLayout();
			this->SuspendLayout();
			// 
			// cmbComm
			// 
			this->cmbComm->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbComm->FormattingEnabled = true;
			this->cmbComm->Location = System::Drawing::Point(6, 16);
			this->cmbComm->Name = L"cmbComm";
			this->cmbComm->Size = System::Drawing::Size(75, 21);
			this->cmbComm->TabIndex = 1;
			this->cmbComm->TabStop = false;
			// 
			// serialPort1
			// 
			this->serialPort1->BaudRate = 19200;
			this->serialPort1->WriteTimeout = 500;
			// 
			// cmdDisconnect
			// 
			this->cmdDisconnect->Enabled = false;
			this->cmdDisconnect->Location = System::Drawing::Point(86, 42);
			this->cmdDisconnect->Name = L"cmdDisconnect";
			this->cmdDisconnect->Size = System::Drawing::Size(102, 23);
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
			this->frmSensor->Controls->Add(this->lblRes7);
			this->frmSensor->Controls->Add(this->label7);
			this->frmSensor->Controls->Add(this->lblRes6);
			this->frmSensor->Controls->Add(this->picLed7);
			this->frmSensor->Controls->Add(this->picLed6);
			this->frmSensor->Controls->Add(this->picFront);
			this->frmSensor->Controls->Add(this->picBack);
			this->frmSensor->Controls->Add(this->picLed5);
			this->frmSensor->Controls->Add(this->pictureBox3);
			this->frmSensor->Controls->Add(this->picLed4);
			this->frmSensor->Controls->Add(this->pictureBox1);
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
			this->frmSensor->Location = System::Drawing::Point(6, 77);
			this->frmSensor->Name = L"frmSensor";
			this->frmSensor->Size = System::Drawing::Size(333, 109);
			this->frmSensor->TabIndex = 4;
			this->frmSensor->TabStop = false;
			this->frmSensor->Text = L"Live SensorData";
			// 
			// lblRes7
			// 
			this->lblRes7->Location = System::Drawing::Point(195, 29);
			this->lblRes7->Name = L"lblRes7";
			this->lblRes7->Size = System::Drawing::Size(102, 13);
			this->lblRes7->TabIndex = 27;
			this->lblRes7->Text = L"N/A";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(160, 29);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(34, 13);
			this->label7->TabIndex = 26;
			this->label7->Text = L"Face:";
			// 
			// lblRes6
			// 
			this->lblRes6->Location = System::Drawing::Point(195, 16);
			this->lblRes6->Name = L"lblRes6";
			this->lblRes6->Size = System::Drawing::Size(78, 13);
			this->lblRes6->TabIndex = 25;
			this->lblRes6->Text = L"N/A";
			// 
			// picLed7
			// 
			this->picLed7->BackColor = System::Drawing::Color::DarkRed;
			this->picLed7->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed7->Location = System::Drawing::Point(168, 44);
			this->picLed7->Name = L"picLed7";
			this->picLed7->Size = System::Drawing::Size(8, 11);
			this->picLed7->TabIndex = 24;
			this->picLed7->TabStop = false;
			this->picLed7->Visible = false;
			// 
			// picLed6
			// 
			this->picLed6->BackColor = System::Drawing::Color::Olive;
			this->picLed6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed6->Location = System::Drawing::Point(159, 44);
			this->picLed6->Name = L"picLed6";
			this->picLed6->Size = System::Drawing::Size(8, 11);
			this->picLed6->TabIndex = 23;
			this->picLed6->TabStop = false;
			this->picLed6->Visible = false;
			// 
			// picFront
			// 
			this->picFront->BackColor = System::Drawing::Color::Lime;
			this->picFront->Location = System::Drawing::Point(305, 44);
			this->picFront->Name = L"picFront";
			this->picFront->Size = System::Drawing::Size(18, 52);
			this->picFront->TabIndex = 18;
			this->picFront->TabStop = false;
			this->picFront->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::picFront_Paint);
			// 
			// picBack
			// 
			this->picBack->BackColor = System::Drawing::Color::White;
			this->picBack->Location = System::Drawing::Point(303, 20);
			this->picBack->Name = L"picBack";
			this->picBack->Size = System::Drawing::Size(22, 78);
			this->picBack->TabIndex = 16;
			this->picBack->TabStop = false;
			// 
			// picLed5
			// 
			this->picLed5->BackColor = System::Drawing::Color::DarkRed;
			this->picLed5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed5->Location = System::Drawing::Point(150, 44);
			this->picLed5->Name = L"picLed5";
			this->picLed5->Size = System::Drawing::Size(8, 11);
			this->picLed5->TabIndex = 22;
			this->picLed5->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::Gray;
			this->pictureBox3->Location = System::Drawing::Point(308, 13);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(12, 10);
			this->pictureBox3->TabIndex = 17;
			this->pictureBox3->TabStop = false;
			// 
			// picLed4
			// 
			this->picLed4->BackColor = System::Drawing::Color::DarkRed;
			this->picLed4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed4->Location = System::Drawing::Point(141, 44);
			this->picLed4->Name = L"picLed4";
			this->picLed4->Size = System::Drawing::Size(8, 11);
			this->picLed4->TabIndex = 21;
			this->picLed4->TabStop = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Gray;
			this->pictureBox1->Location = System::Drawing::Point(301, 18);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(26, 82);
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			// 
			// picLed3
			// 
			this->picLed3->BackColor = System::Drawing::Color::DarkGreen;
			this->picLed3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed3->Location = System::Drawing::Point(132, 44);
			this->picLed3->Name = L"picLed3";
			this->picLed3->Size = System::Drawing::Size(8, 11);
			this->picLed3->TabIndex = 20;
			this->picLed3->TabStop = false;
			// 
			// picLed2
			// 
			this->picLed2->BackColor = System::Drawing::Color::DarkRed;
			this->picLed2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed2->Location = System::Drawing::Point(123, 44);
			this->picLed2->Name = L"picLed2";
			this->picLed2->Size = System::Drawing::Size(8, 11);
			this->picLed2->TabIndex = 19;
			this->picLed2->TabStop = false;
			// 
			// picLed1
			// 
			this->picLed1->BackColor = System::Drawing::Color::DarkRed;
			this->picLed1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed1->Location = System::Drawing::Point(114, 44);
			this->picLed1->Name = L"picLed1";
			this->picLed1->Size = System::Drawing::Size(8, 11);
			this->picLed1->TabIndex = 18;
			this->picLed1->TabStop = false;
			// 
			// picLed0
			// 
			this->picLed0->BackColor = System::Drawing::Color::DarkGreen;
			this->picLed0->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed0->Location = System::Drawing::Point(105, 44);
			this->picLed0->Name = L"picLed0";
			this->picLed0->Size = System::Drawing::Size(8, 11);
			this->picLed0->TabIndex = 17;
			this->picLed0->TabStop = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(160, 16);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(37, 13);
			this->label6->TabIndex = 16;
			this->label6->Text = L"Mode:";
			// 
			// lblRes5
			// 
			this->lblRes5->Location = System::Drawing::Point(102, 81);
			this->lblRes5->Name = L"lblRes5";
			this->lblRes5->Size = System::Drawing::Size(78, 13);
			this->lblRes5->TabIndex = 15;
			this->lblRes5->Text = L"N/A";
			// 
			// lblRes4
			// 
			this->lblRes4->Location = System::Drawing::Point(102, 68);
			this->lblRes4->Name = L"lblRes4";
			this->lblRes4->Size = System::Drawing::Size(78, 13);
			this->lblRes4->TabIndex = 14;
			this->lblRes4->Text = L"N/A";
			// 
			// lblRes3
			// 
			this->lblRes3->Location = System::Drawing::Point(102, 55);
			this->lblRes3->Name = L"lblRes3";
			this->lblRes3->Size = System::Drawing::Size(78, 13);
			this->lblRes3->TabIndex = 13;
			this->lblRes3->Text = L"N/A";
			// 
			// lblRes1
			// 
			this->lblRes1->Location = System::Drawing::Point(102, 29);
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
			this->lblRes0->Location = System::Drawing::Point(102, 16);
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
			this->picCompass->Location = System::Drawing::Point(179, 195);
			this->picCompass->Name = L"picCompass";
			this->picCompass->Size = System::Drawing::Size(160, 160);
			this->picCompass->TabIndex = 5;
			this->picCompass->TabStop = false;
			this->picCompass->Click += gcnew System::EventHandler(this, &MyForm::picCompass_Click);
			this->picCompass->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::picCompass_Paint);
			// 
			// frmControls
			// 
			this->frmControls->Controls->Add(this->lblKeyInfo);
			this->frmControls->Controls->Add(this->lblN);
			this->frmControls->Controls->Add(this->lblD);
			this->frmControls->Controls->Add(this->lblM);
			this->frmControls->Controls->Add(this->lblS);
			this->frmControls->Controls->Add(this->lblA);
			this->frmControls->Controls->Add(this->lblP);
			this->frmControls->Controls->Add(this->lblW);
			this->frmControls->Location = System::Drawing::Point(6, 190);
			this->frmControls->Name = L"frmControls";
			this->frmControls->Size = System::Drawing::Size(165, 167);
			this->frmControls->TabIndex = 22;
			this->frmControls->TabStop = false;
			this->frmControls->Text = L"Controls";
			// 
			// lblKeyInfo
			// 
			this->lblKeyInfo->Location = System::Drawing::Point(7, 145);
			this->lblKeyInfo->Name = L"lblKeyInfo";
			this->lblKeyInfo->Size = System::Drawing::Size(151, 13);
			this->lblKeyInfo->TabIndex = 29;
			// 
			// lblN
			// 
			this->lblN->BackColor = System::Drawing::Color::White;
			this->lblN->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblN->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblN->Location = System::Drawing::Point(59, 113);
			this->lblN->Name = L"lblN";
			this->lblN->Size = System::Drawing::Size(47, 25);
			this->lblN->TabIndex = 28;
			this->lblN->Text = L"N";
			this->lblN->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblN->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblN_MouseDown);
			this->lblN->MouseEnter += gcnew System::EventHandler(this, &MyForm::lblN_MouseEnter);
			this->lblN->MouseLeave += gcnew System::EventHandler(this, &MyForm::lblN_MouseLeave);
			this->lblN->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblN_MouseUp);
			// 
			// lblD
			// 
			this->lblD->BackColor = System::Drawing::Color::White;
			this->lblD->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblD->Location = System::Drawing::Point(112, 61);
			this->lblD->Name = L"lblD";
			this->lblD->Size = System::Drawing::Size(47, 41);
			this->lblD->TabIndex = 25;
			this->lblD->Text = L"D";
			this->lblD->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblD->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblD_MouseDown);
			this->lblD->MouseEnter += gcnew System::EventHandler(this, &MyForm::lblD_MouseEnter);
			this->lblD->MouseLeave += gcnew System::EventHandler(this, &MyForm::lblD_MouseLeave);
			this->lblD->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblD_MouseUp);
			// 
			// lblM
			// 
			this->lblM->AccessibleDescription = L"";
			this->lblM->BackColor = System::Drawing::Color::White;
			this->lblM->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblM->Location = System::Drawing::Point(6, 113);
			this->lblM->Name = L"lblM";
			this->lblM->Size = System::Drawing::Size(47, 25);
			this->lblM->TabIndex = 27;
			this->lblM->Tag = L"hallsodisodisod asd";
			this->lblM->Text = L"M";
			this->lblM->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblM->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblM_MouseDown);
			this->lblM->MouseEnter += gcnew System::EventHandler(this, &MyForm::lblM_MouseEnter);
			this->lblM->MouseLeave += gcnew System::EventHandler(this, &MyForm::lblM_MouseLeave);
			this->lblM->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblM_MouseUp);
			// 
			// lblS
			// 
			this->lblS->BackColor = System::Drawing::Color::White;
			this->lblS->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblS->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblS->Location = System::Drawing::Point(59, 61);
			this->lblS->Name = L"lblS";
			this->lblS->Size = System::Drawing::Size(47, 41);
			this->lblS->TabIndex = 24;
			this->lblS->Text = L"S";
			this->lblS->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblS->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblS_MouseDown);
			this->lblS->MouseEnter += gcnew System::EventHandler(this, &MyForm::lblS_MouseEnter);
			this->lblS->MouseLeave += gcnew System::EventHandler(this, &MyForm::lblS_MouseLeave);
			this->lblS->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblS_MouseUp);
			// 
			// lblA
			// 
			this->lblA->BackColor = System::Drawing::Color::White;
			this->lblA->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblA->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblA->Location = System::Drawing::Point(6, 61);
			this->lblA->Name = L"lblA";
			this->lblA->Size = System::Drawing::Size(47, 41);
			this->lblA->TabIndex = 23;
			this->lblA->Text = L"A";
			this->lblA->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblA->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblA_MouseDown);
			this->lblA->MouseEnter += gcnew System::EventHandler(this, &MyForm::lblA_MouseEnter);
			this->lblA->MouseLeave += gcnew System::EventHandler(this, &MyForm::lblA_MouseLeave);
			this->lblA->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblA_MouseUp);
			// 
			// lblP
			// 
			this->lblP->BackColor = System::Drawing::Color::White;
			this->lblP->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblP->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblP->Location = System::Drawing::Point(112, 113);
			this->lblP->Name = L"lblP";
			this->lblP->Size = System::Drawing::Size(47, 25);
			this->lblP->TabIndex = 26;
			this->lblP->Text = L"P";
			this->lblP->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblP->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblP_MouseDown);
			this->lblP->MouseEnter += gcnew System::EventHandler(this, &MyForm::lblP_MouseEnter);
			this->lblP->MouseLeave += gcnew System::EventHandler(this, &MyForm::lblP_MouseLeave);
			this->lblP->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblP_MouseUp);
			// 
			// lblW
			// 
			this->lblW->BackColor = System::Drawing::Color::White;
			this->lblW->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblW->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblW->Location = System::Drawing::Point(59, 14);
			this->lblW->Name = L"lblW";
			this->lblW->Size = System::Drawing::Size(47, 41);
			this->lblW->TabIndex = 22;
			this->lblW->Text = L"W";
			this->lblW->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblW->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblW_MouseDown);
			this->lblW->MouseEnter += gcnew System::EventHandler(this, &MyForm::lblW_MouseEnter);
			this->lblW->MouseLeave += gcnew System::EventHandler(this, &MyForm::lblW_MouseLeave);
			this->lblW->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::lblW_MouseUp);
			// 
			// sStrip
			// 
			this->sStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->lblStatus, this->lblConnection });
			this->sStrip->Location = System::Drawing::Point(0, 363);
			this->sStrip->Name = L"sStrip";
			this->sStrip->Size = System::Drawing::Size(345, 22);
			this->sStrip->TabIndex = 23;
			this->sStrip->Text = L"statusStrip1";
			// 
			// lblStatus
			// 
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(196, 17);
			this->lblStatus->Text = L"Select CommPort and click connect";
			// 
			// lblConnection
			// 
			this->lblConnection->ForeColor = System::Drawing::Color::Red;
			this->lblConnection->Name = L"lblConnection";
			this->lblConnection->Size = System::Drawing::Size(134, 17);
			this->lblConnection->Spring = true;
			this->lblConnection->Text = L"TimeOuts: 0";
			this->lblConnection->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// tmrAlive
			// 
			this->tmrAlive->Interval = 300;
			this->tmrAlive->Tick += gcnew System::EventHandler(this, &MyForm::tmrAlive_Tick);
			// 
			// tmrRefresh
			// 
			this->tmrRefresh->Enabled = true;
			this->tmrRefresh->Tick += gcnew System::EventHandler(this, &MyForm::tmrRefresh_Tick);
			// 
			// cmdConnect
			// 
			this->cmdConnect->BackColor = System::Drawing::Color::Red;
			this->cmdConnect->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->cmdConnect->ForeColor = System::Drawing::Color::Lime;
			this->cmdConnect->Location = System::Drawing::Point(5, 42);
			this->cmdConnect->Name = L"cmdConnect";
			this->cmdConnect->Size = System::Drawing::Size(77, 23);
			this->cmdConnect->TabIndex = 25;
			this->cmdConnect->TabStop = false;
			this->cmdConnect->Text = L"Connect";
			this->cmdConnect->UseVisualStyleBackColor = false;
			this->cmdConnect->Click += gcnew System::EventHandler(this, &MyForm::cmdConnect_Click);
			// 
			// chkReconnect
			// 
			this->chkReconnect->AutoSize = true;
			this->chkReconnect->Location = System::Drawing::Point(88, 19);
			this->chkReconnect->Name = L"chkReconnect";
			this->chkReconnect->Size = System::Drawing::Size(104, 17);
			this->chkReconnect->TabIndex = 26;
			this->chkReconnect->Text = L"Auto Reconnect";
			this->chkReconnect->UseVisualStyleBackColor = true;
			// 
			// cmdReset
			// 
			this->cmdReset->Location = System::Drawing::Point(6, 15);
			this->cmdReset->Name = L"cmdReset";
			this->cmdReset->Size = System::Drawing::Size(117, 23);
			this->cmdReset->TabIndex = 27;
			this->cmdReset->TabStop = false;
			this->cmdReset->Text = L"Reset Arduino";
			this->cmdReset->UseVisualStyleBackColor = true;
			this->cmdReset->Click += gcnew System::EventHandler(this, &MyForm::cmdReset_Click);
			// 
			// frmArduino
			// 
			this->frmArduino->Controls->Add(this->cmdUpload);
			this->frmArduino->Controls->Add(this->cmdReset);
			this->frmArduino->Location = System::Drawing::Point(210, 2);
			this->frmArduino->Name = L"frmArduino";
			this->frmArduino->Size = System::Drawing::Size(129, 72);
			this->frmArduino->TabIndex = 28;
			this->frmArduino->TabStop = false;
			this->frmArduino->Text = L"Arduino Options";
			// 
			// cmdUpload
			// 
			this->cmdUpload->Location = System::Drawing::Point(6, 41);
			this->cmdUpload->Name = L"cmdUpload";
			this->cmdUpload->Size = System::Drawing::Size(117, 23);
			this->cmdUpload->TabIndex = 28;
			this->cmdUpload->TabStop = false;
			this->cmdUpload->Text = L"Upload Program";
			this->cmdUpload->UseVisualStyleBackColor = true;
			this->cmdUpload->Click += gcnew System::EventHandler(this, &MyForm::cmdUpload_Click);
			// 
			// frmComm
			// 
			this->frmComm->Controls->Add(this->cmbComm);
			this->frmComm->Controls->Add(this->cmdConnect);
			this->frmComm->Controls->Add(this->chkReconnect);
			this->frmComm->Controls->Add(this->cmdDisconnect);
			this->frmComm->Location = System::Drawing::Point(6, 2);
			this->frmComm->Name = L"frmComm";
			this->frmComm->Size = System::Drawing::Size(194, 72);
			this->frmComm->TabIndex = 29;
			this->frmComm->TabStop = false;
			this->frmComm->Text = L"Commport Selection";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(345, 385);
			this->Controls->Add(this->frmComm);
			this->Controls->Add(this->frmArduino);
			this->Controls->Add(this->sStrip);
			this->Controls->Add(this->frmControls);
			this->Controls->Add(this->picCompass);
			this->Controls->Add(this->frmSensor);
			this->DoubleBuffered = true;
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->Text = L"SwagBot Controller v1.302.999 rev: 30202";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->frmSensor->ResumeLayout(false);
			this->frmSensor->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picFront))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picLed0))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picCompass))->EndInit();
			this->frmControls->ResumeLayout(false);
			this->sStrip->ResumeLayout(false);
			this->sStrip->PerformLayout();
			this->frmArduino->ResumeLayout(false);
			this->frmComm->ResumeLayout(false);
			this->frmComm->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}



#pragma endregion


#define KEY_UP false
#define KEY_DOWN true

		private:
		static array<int>^ keyCode = gcnew array<int>(7) { 0x57, 0x41, 0x44, 0x53, 0x50, 0x4D, 0x4E };
		static array<bool>^ keyDown = gcnew array<bool>(7) { false, false, false, false, false, false, false };
		static array<unsigned char>^ keySendUp = gcnew array<unsigned char>(8) { 'W', 'A', 'D', 'S', 'P', 'M', 'N', 'F' };
		static array<unsigned char>^ keySendDown = gcnew array<unsigned char>(8) { 'w', 'a', 'd', 's', 'p', 'm', 'n', 'f' };
		static array<Label^>^ keyLabels = gcnew array<Label^>(7) {};
		static array<bool>^ MouseDown = gcnew array<bool>(7) {};
		static array<String ^>^ Faces = gcnew array<String ^>(7) { "Green Smiley", "Angry Smiley", "Compass", "Bumper Unpressed", "Bumper Pressed", "TEST", "UNKNOWN_FACE" };


		array<int>^ databuffer = gcnew array<int>(100);
		int bufferlen = 0;

		int TimeOutCount = 0;

		String ^buffertest;
		int compassDegrees = 0;
		double PI = 3.14159265359;
		int batteryVoltage = 0;



		private:

		void TriggerKeyState(int whatKey, bool whatState) {
			if (!this->serialPort1->IsOpen) return;

			if (whatState) { //if key was pressed
				if (keyDown[whatKey] == false) {
					keyDown[whatKey] = true;
					try {
						this->serialPort1->Write(keySendDown, whatKey, 1);
					} catch (System::IO::IOException^) {
						setStatusMessage("COMMPORT DISCONNECTED!", true);
						Disconnect();
						return;
					}

					keyLabels[whatKey]->BackColor = Color::Gray;
					//return;
				}
			} else {
				if (keyDown[whatKey] == true && MouseDown[whatKey] == false) {
					keyDown[whatKey] = false;
					try {
						this->serialPort1->Write(keySendUp, whatKey, 1);
						this->serialPort1->Write(keySendUp, whatKey, 1);//send the key twice to be sure the arduino gets it.
					} catch (System::IO::IOException^) {
						setStatusMessage("COMMPORT DISCONNECTED!", true);
						Disconnect();
						return;
					}
					keyLabels[whatKey]->BackColor = Color::White;
				}
			}

			if (MouseDown[whatKey] == true || keyDown[whatKey] == true) {
				keyLabels[whatKey]->BackColor = Color::Gray;
			} else {
				keyLabels[whatKey]->BackColor = Color::White;
			}

		}

		System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
			/*MARGINS margins;

			margins.cyTopHeight = 100;
			margins.cxLeftWidth = 1;
			margins.cyBottomHeight = 1;
			margins.cxRightWidth = 1;

			this->BackColor = Color::Black;

			DwmExtendFrameIntoClientArea((HWND)(this->Handle.ToInt32()), &margins);
			*/

			loadCommports();
			setPercentage(100);
			keyLabels[0] = lblW;
			keyLabels[1] = lblA;
			keyLabels[2] = lblD;
			keyLabels[3] = lblS;
			keyLabels[4] = lblP;
			keyLabels[5] = lblM;
			keyLabels[6] = lblN;

			//Connect();
		}

		System::Void MyForm_KeyDown(Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
			e->SuppressKeyPress = true;
		}


		System::Void MyForm_Unload(System::Object^  sender, System::EventArgs^  e) {
			if (this->serialPort1->IsOpen) {
				this->serialPort1->Close();
			}
		}

		void loadCommports() {
			if (this->cmbComm->DroppedDown) return;
			int j = this->cmbComm->SelectedIndex;

			this->cmbComm->Items->Clear();
			this->cmbComm->Items->AddRange(serialPort1->GetPortNames());
			if (this->cmbComm->Items->Count > 0 && j == -1) {
				this->cmbComm->SelectedIndex = this->cmbComm->Items->Count - 1;
			} else if (j != -1) {
				if (this->cmbComm->Items->Count > j) {
					this->cmbComm->SelectedIndex = j;
				}
			}
		}

		System::Void cmdConnect_Click(System::Object^  sender, System::EventArgs^  e) {
			Connect();
		}

		void Connect() {
			if (this->serialPort1->IsOpen) {
				Disconnect();
				return;
			}

			if (this->cmbComm->SelectedIndex != -1) {

				this->serialPort1->PortName = this->cmbComm->Text;
				this->serialPort1->Parity = System::IO::Ports::Parity::None;
				this->serialPort1->DataBits = 8;

				try {
					this->serialPort1->Open();

				} catch (UnauthorizedAccessException ^) {
					setStatusMessage("Could not open '" + this->cmbComm->Text + "'!", true);
					setControlstate(true);
					return;
				}


				if (this->serialPort1->IsOpen) {
					setStatusMessage("Connected!", false);
					setControlstate(false);
				} else {
					setStatusMessage("Could not open '" + this->cmbComm->Text + "'!", true);
					setControlstate(true);
				}
			}
		}

		void setControlstate(bool EnableControls) {
			if (!EnableControls) {
				this->tmrGetData->Enabled = true;
				this->tmrAlive->Enabled = true;

				this->cmdDisconnect->Enabled = true;
				this->cmdConnect->Enabled = false;
				this->cmdReset->Enabled = false;
				this->cmdUpload->Enabled = false;

				this->cmbComm->Enabled = false;

				this->Focus();
			} else {
				this->cmdDisconnect->Enabled = false;
				this->cmdConnect->Enabled = true;
				this->cmdReset->Enabled = true;
				this->cmdUpload->Enabled = true;

				this->cmbComm->Enabled = true;

			}
		}

		System::Void tmrAlive_Tick(System::Object^  sender, System::EventArgs^  e) {
			if (!this->serialPort1->IsOpen) return;
			try {
				this->serialPort1->Write(keySendUp, 7, 1); //send ack to arduino
			} catch (System::IO::IOException^) {
				setStatusMessage("COMMPORT DISCONNECTED!", true);
				Disconnect();
				return;
			}


			TimeOutCount++;
			if (TimeOutCount > 3 && TimeOutCount < 10) {
				setStatusMessage("Timing out...", false);
			} else if (TimeOutCount == 10) {
				setStatusMessage("Connection Lost!", true);
				ForceReconnect();
				TimeOutCount = 0;
			}
		}

		System::Void tmrGetData_Tick(System::Object^  sender, System::EventArgs^  e) {
			int gchar;
			array<int>^ sensordata = gcnew array<int>(12);
			int i = 0;

			if (!this->serialPort1->IsOpen) return;

			while (this->serialPort1->BytesToRead > 0) {
				//gchar = this->serialPort1->ReadChar();
				//try {
				gchar = this->serialPort1->ReadByte();
				//} //catch() {

				//}

				TimeOutCount = 0;

				if (gchar == 255 && bufferlen >= 11) { //end of bufferdata

					setStatusMessage("Connected!", false);

					for (i = 0; i < 11; i++) {
						sensordata[i] = databuffer[bufferlen - 11 + i];
					}

					bufferlen = 0;

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
						this->picLed6->BackColor = Color::Yellow;
					} else {
						this->picLed6->BackColor = Color::Olive;
					}
					if (128 & leds) {
						this->picLed7->BackColor = Color::Red;
					} else {
						this->picLed7->BackColor = Color::DarkRed;
					}

					this->lblRes3->Text = "" + sensordata[3];
					this->lblRes4->Text = "" + sensordata[4];
					this->lblRes5->Text = "" + sensordata[5];


					batteryVoltage = sensordata[6];
					compassDegrees = sensordata[7];
					this->picCompass->Refresh();
					setPercentage(sensordata[6]);
					this->picCompass->Refresh();

					//picFront
					if (sensordata[8] == 0) {
						this->lblRes6->Text = "Manual Mode";
					} else {
						this->lblRes6->Text = "Automatic Mode";
					}
					this->lblConnection->Text = "TimeOuts: " + sensordata[9];
					if (sensordata[9] > 8) {
						this->lblConnection->ForeColor = Color::Red;
					} else if (sensordata[9] > 8) {
						this->lblConnection->ForeColor = Color::Olive;
					} else {
						this->lblConnection->ForeColor = Color::Black;
					}

					if (sensordata[10] >= 0 && sensordata[10] <= 5) {
						this->lblRes7->Text = Faces[sensordata[10]];
					} else {
						this->lblRes7->Text = Faces[6];
					}



				} else if (gchar == 255) {
					bufferlen = 0;
				} else {
					if (bufferlen < 100 - 1) {
						databuffer[bufferlen++] = gchar;
					} else {
						setStatusMessage("Buffer Overflow!", true);
						ForceReconnect();
						bufferlen = 0;
						databuffer[bufferlen] = 0;
						return;
					}
					//buffertest += "" + Convert::ToChar(gchar);
				}
			}

			for (i = 0; i < 7; i++) {
				this->TriggerKeyState(i, GetAsyncKeyState(keyCode[i]) != 0);
			}

		}

		void ForceReconnect() {
			if (this->chkReconnect->Checked == false) {
				Disconnect();
				return;
			}
			Application::DoEvents();
			Sleep(1000);
			Application::DoEvents();
			ResetArduino();
			Application::DoEvents();
			Sleep(1000);
			Application::DoEvents();
			Connect();
		}

		void ResetArduino() {
			setStatusMessage("Resetting Arduino...", false);
			Application::DoEvents();
			Sleep(100);
			this->serialPort1->DtrEnable = true;
			Sleep(20);
			this->serialPort1->DtrEnable = false;
			Sleep(10);
			Application::DoEvents();
			setStatusMessage("Done!", false);
			Disconnect();
		}

		void setStatusMessage(String ^ nMessage, bool isError) {
			if (isError) {
				this->lblStatus->Text = nMessage;
				this->lblStatus->ForeColor = Color::Red;
			} else {
				this->lblStatus->Text = nMessage;
				this->lblStatus->ForeColor = Color::Black;
			}
		}

		void Disconnect() {
			if (this->serialPort1->IsOpen) {
				this->tmrGetData->Enabled = false;
				this->tmrAlive->Enabled = false;
				try {
					this->serialPort1->Close();
				} catch (System::IO::IOException^) {

				}
				loadCommports();
				setControlstate(true);
			}
		}

		System::Void cmdDisconnect_Click(System::Object^  sender, System::EventArgs^  e) {
			Disconnect();
		}

		void setPercentage(int percentage) {
			if (percentage < 0) percentage = 0;
			if (percentage > 100) percentage = 100;

			this->picFront->Height = (int)((this->picBack->Height - 4) / 100.0 * percentage);
			this->picFront->Top = this->picBack->Top + (this->picBack->Height - this->picFront->Height - 2);

			//this->lblVoltage->Text = (percentage / 10.0) + "V";

			this->picFront->Refresh();
		}

		double byteToDeg(int x) {
			return (double)x / 128.0 * PI - (0.499*PI);
		}

		void picCompass_Paint(Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			Pen^ redPen = gcnew Pen(Color::Red, 3.0f);
			Pen^ blackPen = gcnew Pen(Color::Black, 2.0f);
			Pen^ backgroundPen = gcnew Pen(Color::Gray, 3.0f);
			StringFormat^ alignText = gcnew StringFormat;
			String ^ degrees = "" + Math::Round(compassDegrees / 255.0 * 360.0);

			System::Drawing::Font^ myFont = gcnew System::Drawing::Font("consolas", 14);

			System::Drawing::Font^ debugFont = gcnew System::Drawing::Font("consolas", 10);


			int size = 160 / 2;

			e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			double x = byteToDeg(compassDegrees);
			int point2X = (int)(Math::Cos(x) * (size*0.7) + size);
			int point2Y = (int)(Math::Sin(x) * (size*0.7) + size);
			int point3X = (int)(Math::Cos(x) * (-size*0.7) + size);
			int point3Y = (int)(Math::Sin(x) * (-size*0.7) + size);

			e->Graphics->DrawEllipse(backgroundPen, 2, 2, size * 2 - 4, size * 2 - 4);
			e->Graphics->FillEllipse(Brushes::White, 2, 2, size * 2 - 4, size * 2 - 4);

			e->Graphics->DrawLine(redPen, size, size, point2X, point2Y);
			e->Graphics->DrawLine(blackPen, size, size, point3X, point3Y);

			e->Graphics->FillEllipse(Brushes::White, (int)(size - 14 * 1.5), (int)(size - 14 * 1.5), 14 * 3, 14 * 3);


			alignText->Alignment = StringAlignment::Center;
			alignText->LineAlignment = StringAlignment::Center;

			e->Graphics->DrawString(degrees, myFont, Brushes::Blue, (float)size, (float)size, alignText);

			e->Graphics->DrawString("N", myFont, Brushes::Blue, (float)size, 15.0, alignText);
			e->Graphics->DrawString("E", myFont, Brushes::Blue, (float)(size * 2.0 - 10.0), (float)size, alignText);
			e->Graphics->DrawString("S", myFont, Brushes::Blue, (float)size, (float)(size * 2.0 - 10.0), alignText);
			e->Graphics->DrawString("W", myFont, Brushes::Blue, 10.0, (float)size, alignText);

			e->Graphics->DrawString("" + compassDegrees, debugFont, Brushes::Blue, this->picCompass->Width - 13, this->picCompass->Height - 7, alignText);
			

		}

		void picFront_Paint(Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
			StringFormat^ alignText = gcnew StringFormat;
			alignText->Alignment = StringAlignment::Center;
			alignText->LineAlignment = StringAlignment::Center;

			e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

			System::Drawing::Font^ myFont = gcnew System::Drawing::Font("Verdana", 7); //Microsoft Sans Serif

			e->Graphics->DrawString((batteryVoltage / 10.0) + "", myFont, Brushes::Gray, this->picFront->Width / 2, this->picFront->Height - 6, alignText);
		}

		private:
		System::Void picCompass_Click(System::Object^  sender, System::EventArgs^  e) {
			this->picCompass->Refresh();
		}

		System::Void lblW_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[0] = false;
			this->TriggerKeyState(0, KEY_UP);
		}

		System::Void lblW_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[0] = true;
			this->TriggerKeyState(0, KEY_DOWN);
		}

		System::Void lblW_MouseLeave(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "";
		}

		System::Void lblW_MouseEnter(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "Forward";
		}

		System::Void lblA_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[1] = false;
			this->TriggerKeyState(1, KEY_UP);
		}

		System::Void lblA_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[1] = true;
			this->TriggerKeyState(1, KEY_DOWN);
		}

		System::Void lblA_MouseLeave(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "";
		}

		System::Void lblA_MouseEnter(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "Left";
		}

		System::Void lblD_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[2] = false;
			this->TriggerKeyState(2, KEY_UP);
		}

		System::Void lblD_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[2] = true;
			this->TriggerKeyState(2, KEY_DOWN);
		}

		System::Void lblD_MouseLeave(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "";
		}

		System::Void lblD_MouseEnter(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "Right";
		}

		System::Void lblS_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[3] = false;
			this->TriggerKeyState(3, KEY_UP);
		}

		System::Void lblS_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[3] = true;
			this->TriggerKeyState(3, KEY_DOWN);
		}

		System::Void lblS_MouseLeave(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "";
		}

		System::Void lblS_MouseEnter(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "Back";
		}

		System::Void lblP_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[4] = false;
			this->TriggerKeyState(4, KEY_UP);
		}

		System::Void lblP_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[4] = true;
			this->TriggerKeyState(4, KEY_DOWN);
		}

		System::Void lblP_MouseLeave(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "";
		}

		System::Void lblP_MouseEnter(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "Get SensorData";
		}

		System::Void lblM_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[5] = false;
			this->TriggerKeyState(5, KEY_UP);
		}

		System::Void lblM_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[5] = true;
			this->TriggerKeyState(5, KEY_DOWN);
		}

		System::Void lblM_MouseLeave(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "";
		}

		System::Void lblM_MouseEnter(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "Manual Mode";
		}

		System::Void lblN_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[6] = false;
			this->TriggerKeyState(6, KEY_UP);
		}

		System::Void lblN_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
			MouseDown[6] = true;
			this->TriggerKeyState(6, KEY_DOWN);
		}

		System::Void lblN_MouseLeave(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "";
		}

		System::Void lblN_MouseEnter(System::Object^ sender, System::EventArgs^) {
			this->lblKeyInfo->Text = "Automatic Mode";
		}

		System::Void tmrRefresh_Tick(System::Object^  sender, System::EventArgs^  e) {
			if (this->cmdConnect->Enabled == true) {
				loadCommports();
			}

		}

		System::Void cmdReset_Click(System::Object^  sender, System::EventArgs^  e) {
			Connect();
			Application::DoEvents();
			Sleep(200);
			ResetArduino();
			Application::DoEvents();
			Sleep(200);

		}
		System::Void cmdUpload_Click(System::Object^  sender, System::EventArgs^  e) {
			Connect();
			Application::DoEvents();
			Sleep(200);
			ResetArduino();
			Application::DoEvents();
			Sleep(200);
			ShellExecute((HWND) this->Handle.ToInt32(), TEXT("open"), TEXT("flashRicardoLaptop.bat"), TEXT(""), TEXT("C:\\Users\\Jucko13\\Documents\\GitHub\\swagbot\\software\\arduino\\src\\"), SW_SHOWNORMAL);
		}


	};
}
