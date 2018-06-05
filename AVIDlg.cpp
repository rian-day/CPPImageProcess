// AVIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AVI.h"
#include "AVIDlg.h"
#include <vfw.h> // ����VFWͷ�ļ�
#include "video.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVIDlg dialog

CAVIDlg::CAVIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAVIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAVIDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAVIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAVIDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAVIDlg, CDialog)
	//{{AFX_MSG_MAP(CAVIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_BTN, OnOpenBtn)
	ON_BN_CLICKED(IDC_PRO_BTN, OnProBtn)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(reduceHalf, &CAVIDlg::OnBnClickedreducehalf)
	ON_BN_CLICKED(dely1, &CAVIDlg::OnBnClickeddely1)
	ON_BN_CLICKED(dely2, &CAVIDlg::OnBnClickeddely2)
	ON_BN_CLICKED(dely3, &CAVIDlg::OnBnClickeddely3)
	ON_BN_CLICKED(dely4, &CAVIDlg::OnBnClickeddely4)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVIDlg message handlers

BOOL CAVIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	// TODO: Add extra initialization here
	strAviFilePath = "";
	bImgPro = false;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAVIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAVIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAVIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAVIDlg::OnOpenBtn() 
{
	// TODO: Add your control notification handler code here
	PAVIFILE pavif;	 // AVI�ļ�ָ��
	AVIFILEINFO pfinfo; // AVI�ļ���Ϣ

	if(bImgPro)return;

	// �ļ��򿪶Ի���
	CFileDialog dlg(true,"*.avi",NULL,NULL,"*.avi|*.avi||");
	if (dlg.DoModal()==IDOK)
	{
		strAviFilePath = dlg.GetPathName();
	}else
	{
		return;
	}
	
	// ����Ƶ�ļ�,��ȡ��Ƶ������Ϣ
	AVIFileInit(); // ��ʼ��AVI��
	AVIFileOpen(&pavif,strAviFilePath,OF_READ,NULL); // ��ֻ���ķ�ʽ��AVI�ļ�
	AVIFileInfo(pavif,&pfinfo,sizeof(AVIFILEINFO)); // ��ȡAVI�ļ���Ϣ

	// ��ȡavi�ļ��ĳ�����Ϣ
	lImgWidth  = pfinfo.dwWidth; // ��
	lImgHeight = pfinfo.dwHeight; // ��
	lImgLength = pfinfo.dwLength;


	AVIFileRelease(pavif); // �ͷ�avi�ļ�
	AVIFileExit();	// �ͷ�avi��	
}

// ��Ƶ�źŴ����߳�
UINT CAVIDlg::lpImgProThreadProc(LPVOID lpParam)
{
	CAVIDlg *pDlgWnd = (CAVIDlg*)lpParam; // ������ָ��

	PAVIFILE pfile;	 // AVI�ļ�ָ��
	AVIFILEINFO pfi; // AVI�ļ���Ϣ
	PAVISTREAM pavi; // AVI��
	AVISTREAMINFO psi; // AVI����Ϣ
	PGETFRAME pgf; // ���֡��ָ��
	BITMAPINFOHEADER bmih; // λͼ��Ϣͷ
	BYTE *lpbuff; // ��Ƶ����ָ��
	long lNumFrames; // ��֡��
	long lFirstFrame; // ��ʼ֡

	int position_x = pDlgWnd->vi->x;
	int position_y = pDlgWnd->vi->y;
	int width = pDlgWnd->vi->width;
	int height = pDlgWnd->vi->height;
	int my_speed = pDlgWnd->vi->speed;
	
	// ��ʼ��AVI��
	AVIFileInit(); 

	// ��ֻ���ķ�ʽ��AVI�ļ�
	int res = AVIFileOpen(&pfile, pDlgWnd->strAviFilePath, OF_READ,NULL);
	int n = GetLastError();
	if (res!=AVIERR_OK)
	{
		//an error occures
		if (pfile!=NULL)
			AVIFileRelease(pfile);
		return -1;
	}
	 
	// ��ȡAVI�ļ���Ϣ
	AVIFileInfo(pfile,&pfi,sizeof(AVIFILEINFO)); 
	
	// �����Ƶ��
	res = AVIFileGetStream(pfile,&pavi,streamtypeVIDEO,0);   
	if (res!=AVIERR_OK)
	{
		if (pavi!=NULL)
			AVIStreamRelease(pavi);
		AVIFileExit();
		return -1;
	}
	
	// ���AVI����Ϣ
	AVIStreamInfo(pavi,&psi,sizeof(AVISTREAMINFO)); 
	
	// ��ʼ֡���
	lFirstFrame=AVIStreamStart(pavi); 
	if (lFirstFrame==-1)
	{
		//Error getteing the frame inside the stream
		if (pavi!=NULL)
			AVIStreamRelease(pavi);
		AVIFileExit();
		return -1;
	}
	
	// AVI���ĳ���,��֡��
	lNumFrames = AVIStreamLength(pavi);
	if (lNumFrames==-1)
	{
		//Error getteing the number of frames inside the stream
		if (pavi!=NULL)
			AVIStreamRelease(pavi);
		AVIFileExit();
		return -1;
	}

	// ����λͼ����
	memset(&bmih,0,sizeof(BITMAPINFOHEADER));
	bmih.biBitCount=24;
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = pfi.dwWidth;
	bmih.biHeight = pfi.dwHeight;
	bmih.biCompression =BI_RGB;
	bmih.biPlanes =1;
	bmih.biXPelsPerMeter = 3780;
	bmih.biYPelsPerMeter = 3780;
	
	BITMAPFILEHEADER  bmfh;
	bmfh.bfSize  =  sizeof(bmfh);
    bmfh.bfOffBits  =  sizeof(bmfh)  +  sizeof(bmih);
	bmfh.bfType  =  (int)'M'*  256  +  'B';
	//bmfh.bfType=0x424D;
    bmfh.bfReserved1  =  0;
	bmfh.bfReserved2  =  0;


	CClientDC dc(pDlgWnd);
	
	//��ȡδѹ������Ƶ֡,����ѹ����Ƶ֡
	pgf=AVIStreamGetFrameOpen(pavi,&bmih); 
	
	if(pgf==NULL)
	{
		AfxMessageBox("��ȡ��ѹ������Ƶ֡ʧ��!");
		return -1;
	}
	
	CString totalframe;
	totalframe.Format("%d", lNumFrames);
	pDlgWnd->GetDlgItem(totalFrame)->SetWindowText(_T(totalframe));
	int index=0;
	for(int i = lFirstFrame ; i < lNumFrames ; i++) // ѭ������ÿһ֡
	{
		index = i-lFirstFrame;

		// ���ָ��֡���ڴ��ַ
		lpbuff=(BYTE *)AVIStreamGetFrame(pgf,index) + sizeof(BITMAPINFOHEADER);

		//--------------------------�����㷨--------------------------//
		//__Begin
		// ��ҶȻ�(������չ)
		//__End		
		//--------------------------�����㷨--------------------------//

		//***********************************************************************
		// �ò��������ڶԻ����Ͻ�����ʾ
		// StretchDIBits()ֻ����ʾRGB��ʽ������,��ʾǰ�����Ƶ����תΪ��Ӧ�ĸ�ʽ
		//***********************************************************************
		
		::SetStretchBltMode(dc.m_hDC, COLORONCOLOR); 

		// ���Ų���ʾ��ǰ֡��RGBͼ
		StretchDIBits(dc.m_hDC,position_x, position_y,width,height,0,0,
			bmih.biWidth, bmih.biHeight, /*����ʾͼ������*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);	
		//StretchDIBits(dc.m_hDC, bmih.biWidth / 2, bmih.biHeight / 2, bmih.biWidth / 2, bmih.biHeight / 2, 0, 0,
			//bmih.biWidth, bmih.biHeight, /*����ʾͼ������*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);
		//StretchDIBits(dc.m_hDC, 0, bmih.biHeight / 2, bmih.biWidth / 2, bmih.biHeight / 2, 0, 0,
			//bmih.biWidth, bmih.biHeight, /*����ʾͼ������*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);
		//StretchDIBits(dc.m_hDC, bmih.biWidth / 2, 0, bmih.biWidth / 2, bmih.biHeight / 2, 0, 0,
			//bmih.biWidth, bmih.biHeight, /*����ʾͼ������*/lpbuff, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, SRCCOPY);

        //****************************************************************************
		// ��ʱ:����ÿ֡�����ʱ����(��λΪms,�������޸�)
		//****************************************************************************
		Sleep(my_speed);
		CString currentframe ;
		currentframe.Format("%d", i);
		pDlgWnd->GetDlgItem(currentFrame)->SetWindowText(_T(currentframe));
	}

	AVIStreamGetFrameClose(pgf);
	AVIFileRelease(pfile);
	AVIFileExit();	

	//AfxMessageBox("��Ƶ���ݴ������!");
	pDlgWnd->bImgPro = false;
	return 0;
}

void CAVIDlg::OnProBtn() 
{
	// TODO: Add your control notification handler code here
	// ����ͼ�����߳�
	if(!bImgPro)
	{
		// �ļ���Ϊ�������ѵ����ļ�
		if(strAviFilePath == "")
		{
			AfxMessageBox("���ȵ���AVI��Ƶ�ļ�!");
			return;
		}

		// �����߳�
		video *vi = new video(100, 0, 0, this->lImgWidth, this->lImgHeight);
		this->vi = vi;
		ImgProThreadProc = AfxBeginThread(lpImgProThreadProc, this);
		ImgProThreadProc->m_bAutoDelete = true;
		bImgPro = true;
	}else
	{
		AfxMessageBox("���ڽ�����Ƶ���ݴ���...");
	}
	
	return;	
}




void CAVIDlg::OnBnClickedreducehalf()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ļ���Ϊ�������ѵ����ļ�
	if (strAviFilePath == "")
	{
		AfxMessageBox("���ȵ���AVI��Ƶ�ļ�!");
		return;
	}

	// �����߳�
	video *vi = new video(100, 0, 0, this->lImgWidth/2, this->lImgHeight/2);
	this->vi = vi;
	ImgProThreadProc = AfxBeginThread(lpImgProThreadProc, this);
	ImgProThreadProc->m_bAutoDelete = true;
	bImgPro = true;
}




void CAVIDlg::OnBnClickeddely1()
{
	// TODO: Add your control notification handler code here
	// ����ͼ�����߳�
	if (true)
	{
		// �ļ���Ϊ�������ѵ����ļ�
		if (strAviFilePath == "")
		{
			AfxMessageBox("���ȵ���AVI��Ƶ�ļ�!");
			return;
		}

		// �����߳�
		video *vi = new video(100,0,0,this->lImgWidth/2, this->lImgHeight / 2);
		this->vi = vi;
		ImgProThreadProc = AfxBeginThread(lpImgProThreadProc, this);
		ImgProThreadProc->m_bAutoDelete = true;
		bImgPro = true;
	}
	else
	{
		AfxMessageBox("���ڽ�����Ƶ���ݴ���...");
	}

	return;
}


void CAVIDlg::OnBnClickeddely2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// TODO: Add your control notification handler code here
	// ����ͼ�����߳�
	if (true)
	{
		// �ļ���Ϊ�������ѵ����ļ�
		if (strAviFilePath == "")
		{
			AfxMessageBox("���ȵ���AVI��Ƶ�ļ�!");
			return;
		}

		// �����߳�
		video *vi = new video(500, this->lImgWidth / 2, 0, this->lImgWidth / 2, this->lImgHeight / 2);
		this->vi = vi;
		ImgProThreadProc = AfxBeginThread(lpImgProThreadProc, this);
		ImgProThreadProc->m_bAutoDelete = true;
		bImgPro = true;
	}
	else
	{
		AfxMessageBox("���ڽ�����Ƶ���ݴ���...");
	}

	return;
}


void CAVIDlg::OnBnClickeddely3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (true)
	{
		// �ļ���Ϊ�������ѵ����ļ�
		if (strAviFilePath == "")
		{
			AfxMessageBox("���ȵ���AVI��Ƶ�ļ�!");
			return;
		}

		// �����߳�
		video *vi = new video(1000, 0, this->lImgHeight / 2, this->lImgWidth / 2, this->lImgHeight / 2);
		this->vi = vi;
		ImgProThreadProc = AfxBeginThread(lpImgProThreadProc, this);
		ImgProThreadProc->m_bAutoDelete = true;
		bImgPro = true;
	}
	else
	{
		AfxMessageBox("���ڽ�����Ƶ���ݴ���...");
	}

	return;
}


void CAVIDlg::OnBnClickeddely4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (true)
	{
		// �ļ���Ϊ�������ѵ����ļ�
		if (strAviFilePath == "")
		{
			AfxMessageBox("���ȵ���AVI��Ƶ�ļ�!");
			return;
		}

		// �����߳�
		video *vi = new video(2000, this->lImgWidth / 2, this->lImgHeight / 2, this->lImgWidth / 2, this->lImgHeight / 2);
		this->vi = vi;
		ImgProThreadProc = AfxBeginThread(lpImgProThreadProc, this);
		ImgProThreadProc->m_bAutoDelete = true;
		bImgPro = true;
	}
	else
	{
		AfxMessageBox("���ڽ�����Ƶ���ݴ���...");
	}

	return;
}

