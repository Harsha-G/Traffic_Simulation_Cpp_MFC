
// Assignment_3Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "stdheader.h"


// CAssignment_3Dlg dialog
class CAssignment_3Dlg : public CDialogEx
{
// Construction
public:
	CAssignment_3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASSIGNMENT_3_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	//Traffic_Sim *ts;
	double m_dSimTime;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnTimer(UINT_PTR TimerVal);
	afx_msg void OnBnClickedButton1();
	CComboBox combobox1;
	CEdit test_input_1;
	CButton m_EndSimButton;
	CButton m_RunSimButton;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CStatic m_Sim_Spd_text;
	CStatic m_data_file_text;
};
