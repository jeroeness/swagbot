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
			this->cmdRefresh = (gcnew System::Windows::Forms::Button());
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
			this->SuspendLayout();
			// 
			// cmdConnect
			// 
			this->cmdConnect->Location = System::Drawing::Point(179, 11);
			this->cmdConnect->Name = L"cmdConnect";
			this->cmdConnect->Size = System::Drawing::Size(81, 23);
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
			this->serialPort1->WriteTimeout = 500;
			// 
			// cmdDisconnect
			// 
			this->cmdDisconnect->Enabled = false;
			this->cmdDisconnect->Location = System::Drawing::Point(266, 11);
			this->cmdDisconnect->Name = L"cmdDisconnect";
			this->cmdDisconnect->Size = System::Drawing::Size(81, 23);
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
			this->frmSensor->Location = System::Drawing::Point(12, 40);
			this->frmSensor->Name = L"frmSensor";
			this->frmSensor->Size = System::Drawing::Size(333, 109);
			this->frmSensor->TabIndex = 4;
			this->frmSensor->TabStop = false;
			this->frmSensor->Text = L"Live SensorData";
			// 
			// lblRes6
			// 
			this->lblRes6->Location = System::Drawing::Point(235, 16);
			this->lblRes6->Name = L"lblRes6";
			this->lblRes6->Size = System::Drawing::Size(78, 13);
			this->lblRes6->TabIndex = 25;
			this->lblRes6->Text = L"N/A";
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
			this->picLed7->Visible = false;
			// 
			// picLed6
			// 
			this->picLed6->BackColor = System::Drawing::Color::Olive;
			this->picLed6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picLed6->Location = System::Drawing::Point(173, 44);
			this->picLed6->Name = L"picLed6";
			this->picLed6->Size = System::Drawing::Size(8, 11);
			this->picLed6->TabIndex = 23;
			this->picLed6->TabStop = false;
			// 
			// picFront
			// 
			this->picFront->BackColor = System::Drawing::Color::Lime;
			this->picFront->Location = System::Drawing::Point(305, 72);
			this->picFront->Name = L"picFront";
			this->picFront->Size = System::Drawing::Size(17, 24);
			this->picFront->TabIndex = 18;
			this->picFront->TabStop = false;
			// 
			// picBack
			// 
			this->picBack->BackColor = System::Drawing::Color::White;
			this->picBack->Location = System::Drawing::Point(303, 38);
			this->picBack->Name = L"picBack";
			this->picBack->Size = System::Drawing::Size(21, 60);
			this->picBack->TabIndex = 16;
			this->picBack->TabStop = false;
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
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::Gray;
			this->pictureBox3->Location = System::Drawing::Point(308, 32);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(11, 10);
			this->pictureBox3->TabIndex = 17;
			this->pictureBox3->TabStop = false;
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
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Gray;
			this->pictureBox1->Location = System::Drawing::Point(301, 36);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(25, 64);
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
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
			this->picCompass->Location = System::Drawing::Point(185, 162);
			this->picCompass->Name = L"picCompass";
			this->picCompass->Size = System::Drawing::Size(160, 160);
			this->picCompass->TabIndex = 5;
			this->picCompass->TabStop = false;
			this->picCompass->Click += gcnew System::EventHandler(this, &MyForm::picCompass_Click);
			this->picCompass->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::picCompass_Paint);
			// 
			// cmdRefresh
			// 
			this->cmdRefresh->Location = System::Drawing::Point(93, 11);
			this->cmdRefresh->Name = L"cmdRefresh";
			this->cmdRefresh->Size = System::Drawing::Size(80, 23);
			this->cmdRefresh->TabIndex = 19;
			this->cmdRefresh->TabStop = false;
			this->cmdRefresh->Text = L"Refresh";
			this->cmdRefresh->UseVisualStyleBackColor = true;
			this->cmdRefresh->Click += gcnew System::EventHandler(this, &MyForm::cmdRefresh_Click);
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
			this->frmControls->Location = System::Drawing::Point(12, 155);
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
			this->sStrip->Location = System::Drawing::Point(0, 334);
			this->sStrip->Name = L"sStrip";
			this->sStrip->Size = System::Drawing::Size(356, 22);
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
			this->lblConnection->Size = System::Drawing::Size(145, 17);
			this->lblConnection->Spring = true;
			this->lblConnection->Text = L"TimeOuts: 0";
			this->lblConnection->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			// 
			// tmrAlive
			// 
			this->tmrAlive->Interval = 300;
			this->tmrAlive->Tick += gcnew System::EventHandler(this, &MyForm::tmrAlive_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::WhiteSmoke;
			this->ClientSize = System::Drawing::Size(356, 356);
			this->Controls->Add(this->sStrip);
			this->Controls->Add(this->frmControls);
			this->Controls->Add(this->cmdRefresh);
			this->Controls->Add(this->picCompass);
			this->Controls->Add(this->frmSensor);
			this->Controls->Add(this->cmdDisconnect);
			this->Controls->Add(this->cmbComm);
			this->Controls->Add(this->cmdConnect);
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

		array<int>^ databuffer = gcnew array<int>(100);
		int bufferlen = 0;

		int TimeOutCount = 0;

		String ^buffertest;
		int compassDegrees = 0;
		double PI = 3.14159265359;



	private:
		
		void TriggerKeyState(int whatKey, bool whatState) {
			if (!this->serialPort1->IsOpen) return;

			if (whatState) { //if key was pressed
				if (keyDown[whatKey] == false) {
					keyDown[whatKey] = true;
					this->serialPort1->Write(keySendDown, whatKey, 1);
					keyLabels[whatKey]->BackColor = Color::Gray;
					//return;
				}
			} else {
				if (keyDown[whatKey] == true && MouseDown[whatKey] == false) {
					keyDown[whatKey] = false;
					this->serialPort1->Write(keySendUp, whatKey, 1);
					this->serialPort1->Write(keySendUp, whatKey, 1);//send the key twice to be sure the arduino gets it.
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
			loadCommports();
			setPercentage(100);
			keyLabels[0] = lblW;
			keyLabels[1] = lblA;
			keyLabels[2] = lblD;
			keyLabels[3] = lblS;
			keyLabels[4] = lblP;
			keyLabels[5] = lblM;
			keyLabels[6] = lblN;
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
			this->cmbComm->Items->Clear();
			this->cmbComm->Items->AddRange(serialPort1->GetPortNames());
			if (this->cmbComm->Items->Count > 0) {
				this->cmbComm->SelectedIndex = this->cmbComm->Items->Count-1;
				Connect();
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

				this->serialPort1->Open();
				if (this->serialPort1->IsOpen) {
					setStatusMessage("Connected!",false);
					setControlstate(false);
				} else {
					setStatusMessage("Could not open '" + this->cmbComm->Text + "'!",true);
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

		System::Void tmrAlive_Tick(System::Object^  sender, System::EventArgs^  e) {
			if (!this->serialPort1->IsOpen) return;
			
			this->serialPort1->Write(keySendUp,7,1); //send ack to arduino

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
			array<int>^ sensordata = gcnew array<int>(11);
			int i = 0;

			if (!this->serialPort1->IsOpen) return;

			while (this->serialPort1->BytesToRead > 0) {
				//gchar = this->serialPort1->ReadChar();
				gchar = this->serialPort1->ReadByte();
				TimeOutCount = 0;

				if (gchar == 255 && bufferlen >= 10) { //end of bufferdata
					
					setStatusMessage("Connected!", false);

					for (i = 0; i < 10; i++) {
						sensordata[i] = databuffer[bufferlen-10+i];
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
					setPercentage(sensordata[6]);
					compassDegrees = sensordata[7];
					this->picCompass->Refresh();

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

				} else {
					if (bufferlen < 100-1) {
						databuffer[bufferlen++] = gchar;
					}else{
						setStatusMessage("Buffer Overflow!",true);
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
			Application::DoEvents();
			Sleep(1000);
			Application::DoEvents();
			setStatusMessage("Resetting Arduino...", false);
			this->serialPort1->DtrEnable = true;
			Sleep(20);
			this->serialPort1->DtrEnable = false;
			Sleep(10);
			Disconnect();
			Application::DoEvents();
			Sleep(1000);
			Application::DoEvents();
			Connect();
		}

		void setStatusMessage(String ^ nMessage,bool isError){
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
				this->serialPort1->Close();
				setControlstate(true);
			}
		}

		System::Void cmdDisconnect_Click(System::Object^  sender, System::EventArgs^  e) {
			Disconnect();
		}

		void setPercentage(int percentage) {
			if (percentage < 0) percentage = 0;
			if (percentage > 100) percentage = 100;

			this->picFront->Height = (this->picBack->Height - 4) / 100.0 * percentage;
			this->picFront->Top = this->picBack->Top + (this->picBack->Height - this->picFront->Height - 2);

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

	private:
		System::Void picCompass_Click(System::Object^  sender, System::EventArgs^  e) {
			this->picCompass->Refresh();
		}

		System::Void cmdRefresh_Click(System::Object^  sender, System::EventArgs^  e) {
			loadCommports();
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

};
}
