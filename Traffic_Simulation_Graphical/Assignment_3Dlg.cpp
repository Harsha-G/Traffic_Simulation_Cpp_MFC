
// Assignment_3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Assignment_3.h"
#include "Assignment_3Dlg.h"
#include "afxdialogex.h"
#include "stdheader.h"

#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAssignment_3Dlg dialog



CAssignment_3Dlg::CAssignment_3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ASSIGNMENT_3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAssignment_3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, combobox1);
	DDX_Control(pDX, IDC_EDIT1, test_input_1);
	DDX_Control(pDX, IDOK, m_EndSimButton);
	DDX_Control(pDX, IDC_BUTTON1, m_RunSimButton);
	DDX_Control(pDX, IDC_STATIC1, m_Sim_Spd_text);
	DDX_Control(pDX, IDC_STATIC2, m_data_file_text);
}

BEGIN_MESSAGE_MAP(CAssignment_3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAssignment_3Dlg::OnBnClickedButton1)
	ON_WM_SIZE()
	ON_WM_TIMER(&CAssignment_3Dlg::OnTimer)

END_MESSAGE_MAP()


// CAssignment_3Dlg message handlers

BOOL CAssignment_3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.



	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//=======================================================================================================
	combobox1.AddString(" 1X");
	combobox1.AddString(" 2X");
	combobox1.AddString(" 5X");
	combobox1.SelectString(0, " 1X");
	//=======================================================================================================

	test_input_1.SetWindowTextA("TrafficSim03.xml");

	//=======================================================================================================
	// Resize and reposition the window
	//int m_iWinWidth = 700;
	//int m_iWinHeight = 700;
	//this->SetWindowPos(NULL, 10, 10, m_iWinWidth, m_iWinHeight, 0); // Move and resize window
																	// Move all the widgets
	//m_EndSimButton.SetWindowPos(NULL, m_iWinWidth - 150, m_iWinHeight - 50, 100, 20, 0);
	//m_RunSimButton.SetWindowPos(NULL, m_iWinWidth - 275, m_iWinHeight - 50, 100, 20, 0);
	//combobox1.SetWindowPos(NULL, m_iWinWidth - 350, m_iWinHeight - 50, 50, 20, 0);
	//test_input_1.SetWindowPos(NULL, m_iWinWidth - 675, m_iWinHeight - 50, 200, 20, 0);
	//// Move the sim speed label
	//CStatic *label = (CStatic *)GetDlgItem(IDC_STATIC2);
	//label->SetWindowPos(NULL, m_iWinWidth - 450, m_iWinHeight - 50, 200, 20, 0);
	//// Move the data file label
	//label = (CStatic *)GetDlgItem(IDC_STATIC1);
	//label->SetWindowPos(NULL, m_iWinWidth - 775, m_iWinHeight - 50, 200, 20, 0);
	//=======================================================================================================

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAssignment_3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAssignment_3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		CDC *cdc_ = this->GetDC();
		CRect windowRect;
		this->GetClientRect(&windowRect);
		CRect r1;
		m_EndSimButton.GetClientRect(&r1);

		//cdc_->FillSolidRect(100, 100, 100, 100, (128,128,128));
		Traffic_Sim *ts = Traffic_Sim::get_instance();
		//ts->paint_map(cdc_);

		COLORREF Grey = RGB(150, 150, 150);
		COLORREF Black = RGB(0, 0, 0);
		COLORREF White = RGB(255, 255, 255);
		
		CPen penBlack;
		penBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen* pOldPen = cdc_->SelectObject(&penBlack);

		CBrush blackbrush;
		blackbrush.CreateSolidBrush(Black);

		CBrush whitebrush;
		whitebrush.CreateSolidBrush(White);

		windowRect.bottom = windowRect.bottom - r1.Height() - 20;
		cdc_->FillRect(&windowRect, &whitebrush);

		CPoint orig = cdc_->GetViewportOrg();
		cdc_->SetViewportOrg(10, 10);

		vector<Road> *rds = ts->map1.return_road_setptr();
		vector<Intersection> *intrs = ts->map1.return_intersection_setptr();

		for (int i = 0; i < rds->size(); i++) {
			vertex strt = rds->at(i).return_road_strt();
			vertex end = rds->at(i).return_road_end();

			vertex upper_left = rds->at(i).return_upper_left();
			vertex lower_right = rds->at(i).return_lower_right();

			int length = (int)(lower_right.return_x() - upper_left.return_x())+1;
			int width = (int)(lower_right.return_y() - upper_left.return_y()) + 1;

			cdc_->FillSolidRect((int)upper_left.return_x(), (int)upper_left.return_y(), length, width, Grey);
			cdc_->MoveTo((int)strt.return_x(), (int)strt.return_y());
			cdc_->LineTo((int)end.return_x(), (int)end.return_y());
			//cdc_->Rectangle(upper_left.return_x(), upper_left.return_y(), length, width);

		}

		//cdc_->SetDCBrushColor(Black);

		for (int j = 0; j < intrs->size(); j++) {
			vertex upper_left = intrs->at(j).return_upper_left();
			vertex lower_right = intrs->at(j).return_lower_right();

			int length = (int)(lower_right.return_x() - upper_left.return_x()) + 1;
			int width = (int)(lower_right.return_y() - upper_left.return_y()) + 1;

			intrs->at(j).draw_lights(cdc_);

			cdc_->FillSolidRect((int)upper_left.return_x(), (int)upper_left.return_y(), length, width, Grey);
			cdc_->FrameRect(CRect((int)upper_left.return_x(), (int)upper_left.return_y(), (int)lower_right.return_x()+1, (int)lower_right.return_y()+1), &blackbrush);
		}

		for (int i = 0; i < ts->_18_wheeler_truck_set.size(); i++) {
			int x_offset = 3;
			int y_offset = 3;
			vertex current = ts->_18_wheeler_truck_set[i].return_current_pt();
			//cdc_->FillSolidRect(current.return_x() , current.return_y() ,3,3, Black);
			ts->_18_wheeler_truck_set[i].Draw(cdc_);
		}

		for (int i = 0; i < ts->_8_cylinder_car_set.size(); i++) {
			int x_offset = 3;
			int y_offset = 3;
			vertex current = ts->_8_cylinder_car_set[i].return_current_pt();
			//cdc_->FillSolidRect(current.return_x() , current.return_y() , 3, 3, Black);
			ts->_8_cylinder_car_set[i].Draw(cdc_);

		}

		for (int i = 0; i < ts->_6_cylinder_car_set.size(); i++) {
			int x_offset = 3;
			int y_offset = 3;
			vertex current = ts->_6_cylinder_car_set[i].return_current_pt();
			//cdc_->FillSolidRect(current.return_x() , current.return_y() , 3, 3, Black);
			ts->_6_cylinder_car_set[i].Draw(cdc_);

		}

		for (int i = 0; i < ts->_4_cylinder_car_set.size(); i++) {
			int x_offset = 3;
			int y_offset = 3;
			vertex current = ts->_4_cylinder_car_set[i].return_current_pt();
			//cdc_->FillSolidRect(current.return_x() , current.return_y() , 3, 3, Black);
			ts->_4_cylinder_car_set[i].Draw(cdc_);

		}

		for (int i = 0; i < ts->_Panel_truck_set.size(); i++) {
			int x_offset = 3;
			int y_offset = 3;
			vertex current = ts->_Panel_truck_set[i].return_current_pt();
			//cdc_->FillSolidRect(current.return_x() , current.return_y() , 3, 3, Black);
			ts->_Panel_truck_set[i].Draw(cdc_);

		}

	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAssignment_3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAssignment_3Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	// Create a couple of K&R strings
	char datafile[64];
	char speedStr[10];

	int speed = 5;
	// Get the name of the data file from the text field
	test_input_1.GetWindowText(datafile, 63);
	// Get the speed to run
	combobox1.GetLBText(combobox1.GetCurSel(), speedStr);
	//if (strcmp(speedStr, " 1X") == 0) CWnd::SetTimer(1, 1000, 0);
	//else if (strcmp(speedStr, " 2X") == 0) CWnd::SetTimer(1, 500, 0);
	//else CWnd::SetTimer(1, 200, 0);

	if (strcmp(speedStr, " 1X") == 0) { CWnd::SetTimer(1, 1000, 0); speed = 1; }
	else if (strcmp(speedStr, " 2X") == 0) { CWnd::SetTimer(1, 500, 0); speed = 2; }
	else CWnd::SetTimer(1, 200, 0);

	// Get the traffic sim singleton 
	Traffic_Sim *ts = Traffic_Sim::get_instance();
	ts->set_Data_File(datafile);	// Give it the name of the data file

	m_dSimTime = 0.0;		// Init sim time-member variable defined in Prog3Dlg.h
							// Disable the run sim button so the user can't click it again
	m_RunSimButton.EnableWindow(false);
	//OnPaint();
	//ts->runSim();	// It's kickoff time
	ts->run_Simulation(speed);
	//OnPaint();
}


void CAssignment_3Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	 
	if (m_hWnd == NULL ||m_EndSimButton.m_hWnd == NULL) {
		return;
	}

	// Resize and reposition the window
	int m_iWinWidth = cx;
	int m_iWinHeight = cy;
	//this->SetWindowPos(NULL, 10, 10, m_iWinWidth, m_iWinHeight, 0); // Move and resize window
	// Move all the widgets
	//CRect r1, r2, r3, r4, r5,r6;
	//m_EndSimButton.GetClientRect(&r1);
	//m_RunSimButton.GetClientRect(&r2);
	//combobox1.GetClientRect(&r3);
	//m_Sim_Spd_text.GetClientRect(&r4);
	//test_input_1.GetClientRect(&r5);
	//m_data_file_text.GetClientRect(&r6);

	//int curx = m_iWinWidth - 10 - r1.Width();

	//m_EndSimButton.SetWindowPos(NULL, curx, m_iWinHeight - 10 - r1.Height(), r1.Width(), r1.Height(), 0); 
	//curx += -10 - r2.Width();
	//m_RunSimButton.SetWindowPos(NULL, curx, m_iWinHeight - 10 - r2.Height(), r2.Width(), r2.Height(), 0);
	//curx += -10 - r3.Width();

	//combobox1.SetWindowPos(NULL, curx, m_iWinHeight - 10 - r3.Height(), r3.Width(), r3.Height(), 0);
	//curx += -10 - r4.Width();

	//m_Sim_Spd_text.SetWindowPos(NULL,curx, m_iWinHeight - 10 - r4.Height(), r4.Width(), r4.Height(), 0);
	//curx += -10 - r5.Width();
	//test_input_1.SetWindowPos(NULL,curx, m_iWinHeight - 10 - r5.Height(), r5.Width(), r5.Height(), 0);
	//curx += -10 - r6.Width();
	//m_data_file_text.SetWindowPos(NULL,curx , m_iWinHeight - 10 - r6.Height(), r6.Width(), r6.Height(), 0);
	// Move the sim speed label
	//CStatic *label = (CStatic *)GetDlgItem(IDC_STATIC2);
	//label->SetWindowPos(NULL, m_iWinWidth - 450, m_iWinHeight - 50, 200, 20, 0);
	//// Move the data file label
	//label = (CStatic *)GetDlgItem(IDC_STATIC1);
	//label->SetWindowPos(NULL, m_iWinWidth - 775, m_iWinHeight - 50, 200, 20, 0);


	// TODO: Add your message handler code here
}

void CAssignment_3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// Perform any updates to the traffic sim state here before calling OnPaint
	m_dSimTime += 1.0; // Update sim time-member variable defined in programNameDlg.h 
	Traffic_Sim *ts = Traffic_Sim::get_instance();
	ts->update(m_dSimTime);
	OnPaint();  // Call the paint function to update the display

	CDialog::OnTimer(nIDEvent); // Pass on to super
}