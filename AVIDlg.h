// AVIDlg.h : header file
//
#include "video.h"
#if !defined(AFX_AVIDLG_H__0D263936_89EE_4649_B4F0_9DBD2E1FD0F2__INCLUDED_)
#define AFX_AVIDLG_H__0D263936_89EE_4649_B4F0_9DBD2E1FD0F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAVIDlg dialog

class CAVIDlg : public CDialog
{
// Construction
public:
	CAVIDlg(CWnd* pParent = NULL);	// standard constructor

	video *vi;
	CString strAviFilePath;
	LONG lImgWidth;
	LONG lImgHeight;
	LONG lImgLength;
	bool bImgPro;
	CWinThread* ImgProThreadProc;
	static UINT lpImgProThreadProc(LPVOID lpParam);

// Dialog Data
	//{{AFX_DATA(CAVIDlg)
	enum { IDD = IDD_AVI_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAVIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAVIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpenBtn();
	afx_msg void OnProBtn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedreducehalf();
	afx_msg void OnBnClickeddely1();
	afx_msg void OnBnClickeddely2();
	afx_msg void OnBnClickeddely3();
	afx_msg void OnBnClickeddely4();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIDLG_H__0D263936_89EE_4649_B4F0_9DBD2E1FD0F2__INCLUDED_)
