
// ScreenGrapDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScreenGrap.h"
#include "ScreenGrapDlg.h"
#include "afxdialogex.h"
#include <windowsx.h>
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

AVISTREAMINFO strhdr;
PAVIFILE pfile;
PAVISTREAM ps; 
PAVISTREAM pComStream;
int nFrames = 0; 
HRESULT hr; 
AVICOMPRESSOPTIONS pCompressOption;   
AVICOMPRESSOPTIONS FAR * opts[1] = {&pCompressOption}; 
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CScreenGrapDlg 对话框




CScreenGrapDlg::CScreenGrapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScreenGrapDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenGrapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDCANCEL, CB_EXIT);
	DDX_Control(pDX, IDC_BUTTON1, CB_START);
	DDX_Control(pDX, IDC_BUTTON2, CB_SUSPEND);
	DDX_Control(pDX, IDC_BUTTON3, CB_STOP);
	DDX_Control(pDX, IDC_BUTTON4, CB_ROUTE);
	DDX_Control(pDX, IDC_EDIT1, CE_ROUTE);
}

BEGIN_MESSAGE_MAP(CScreenGrapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, &CScreenGrapDlg::OnBnClickedButton4)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CScreenGrapDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CScreenGrapDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CScreenGrapDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CScreenGrapDlg 消息处理程序

void CScreenGrapDlg::OnLButtonDown ( UINT nFlags, CPoint point )//实现窗口的移动
 {
 SendMessage( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y ) ); 
 CDialog::OnLButtonDown(nFlags, point);
 }

BOOL CScreenGrapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	my_hIcon = AfxGetApp()->LoadIcon(IDI_EXIT);
	CB_EXIT.SetIcon(my_hIcon);
	my_hIcon = AfxGetApp()->LoadIcon(IDI_START);
	CB_START.SetIcon(my_hIcon);
	my_hIcon = AfxGetApp()->LoadIcon(IDI_SUS);
	CB_SUSPEND.SetIcon(my_hIcon);
	my_hIcon = AfxGetApp()->LoadIcon(IDI_STOP);
	CB_STOP.SetIcon(my_hIcon);
	my_hIcon = AfxGetApp()->LoadIcon(IDI_ROUTE);
	CB_ROUTE.SetIcon(my_hIcon);
	
	CB_SUSPEND.EnableWindow(FALSE);
	CB_STOP.EnableWindow(FALSE);







	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CScreenGrapDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CScreenGrapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CScreenGrapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CScreenGrapDlg::OnBnClickedButton4()
{
	CString ReturnPach;
	TCHAR szPath[_MAX_PATH];
	BROWSEINFO bi;
	bi.hwndOwner=NULL;
	bi.pidlRoot=NULL;
	bi.lpszTitle=_T("文件浏览对话框");
	bi.pszDisplayName=szPath;
	bi.ulFlags=BIF_RETURNONLYFSDIRS;
	bi.lpfn=NULL;
	bi.lParam=NULL;
	LPITEMIDLIST pItemIDList=SHBrowseForFolder(&bi);
	if(pItemIDList)
	{
		if(SHGetPathFromIDList(pItemIDList,szPath))
			ReturnPach=szPath;
		m_IsPath=TRUE;
	}
	else
	{
		ReturnPach="";
	}
	CE_ROUTE.SetWindowTextA(ReturnPach);
	Path=ReturnPach;
}

bool  CScreenGrapDlg::GrapScreen()//抓取图片
{
	CDC* pDeskDC=GetDesktopWindow()->GetDC();
	CRect rc;
	GetDesktopWindow()->GetClientRect(rc);
	CDC memDC;
	memDC.CreateCompatibleDC(pDeskDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDeskDC,rc.Width(),rc.Height());
	memDC.SelectObject(&bmp);
	BITMAP bitmap;
	bmp.GetBitmap(&bitmap);
	memDC.BitBlt(0,0,bitmap.bmWidth,bitmap.bmHeight,pDeskDC,0,0,SRCCOPY);
	

		CPoint point;//扑捉鼠标
		GetCursorPos(&point);
		HICON hicon = (HICON)GetCursor();
		memDC.DrawIcon(point,hicon);


	DWORD size=bitmap.bmWidthBytes*bitmap.bmHeight;
	LPSTR lpData=(LPSTR)GlobalAllocPtr(GPTR,size);
	int panelsize  = 0;									//记录调色板大小
	if(bitmap.bmBitsPixel<16)
		for(int n=0;n<=bitmap.bmBitsPixel*sizeof(RGBQUAD);n++)//判断是否为真彩色位图
		panelsize = 2*2;
	BITMAPINFOHEADER *pBInfo = (BITMAPINFOHEADER*)LocalAlloc(LPTR,
		sizeof(BITMAPINFO)+panelsize);
	pBInfo->biBitCount       = bitmap.bmBitsPixel;
	pBInfo->biClrImportant   = 0;
	pBInfo->biCompression    = 0;
	pBInfo->biHeight         = bitmap.bmHeight;
	pBInfo->biPlanes         = bitmap.bmPlanes;
	pBInfo->biSize           = sizeof(BITMAPINFO);
	pBInfo->biSizeImage      = bitmap.bmWidthBytes*bitmap.bmHeight;
	pBInfo->biWidth          = bitmap.bmWidth;
	pBInfo->biXPelsPerMeter  = 0;
	pBInfo->biYPelsPerMeter  = 0;

	GetDIBits(memDC.m_hDC,bmp,0,pBInfo->biHeight,lpData,
		(BITMAPINFO*)pBInfo,DIB_RGB_COLORS);

	CString name,m_number;
	CTime time = CTime::GetCurrentTime();

	name = Path+"\\"+time.Format("%Y%m%d%H%M%S")+".bmp";
	BITMAPFILEHEADER bfh;
	bfh.bfReserved1 = bfh.bfReserved2 = 0;
	bfh.bfType      = ((WORD)('M'<< 8)|'B');
	bfh.bfSize      = 54+size;
	bfh.bfOffBits   = 54;
	CFile file;

	if(file.Open(name,CFile::modeCreate|CFile::modeWrite))
	{
		file.Write(&bfh,sizeof(BITMAPFILEHEADER));
		file.Write(pBInfo,sizeof(BITMAPINFOHEADER));
		file.Write(lpData,size);
		file.Close();
	}

	return FALSE;
}

void CScreenGrapDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//
	CE_ROUTE.GetWindowTextA(Path);//得到选择的路径
	if(Path=="")
	{
		MessageBox(_T("请先设置文件存储路径！"));
		return;
	}
	CB_START.EnableWindow(FALSE);
	CB_SUSPEND.EnableWindow(TRUE);
	CB_STOP.EnableWindow(TRUE);
	//
	AVIFileInit();
	m_IsTime = TRUE;
	SetTimer(1,100,NULL);
	AfxBeginThread(ThreadFunc,NULL);


}


void CScreenGrapDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
}


void CScreenGrapDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	AVIStreamClose(pComStream);
		AVIStreamClose(ps);
		if(pfile != NULL)
			AVIFileRelease(pfile);
		AVIFileExit();
	CB_START.EnableWindow(TRUE);
}


void CScreenGrapDlg::OnTimer(UINT nTimerID)
{

	if(m_IsTime)
	{
		m_IsTime = FALSE;
		
		CDC* pDeskDC =  GetDesktopWindow()->GetDC();		//获取桌面画布对象
		CRect rc;
		GetDesktopWindow()->GetClientRect(rc);				//获取屏幕的客户区域

		CDC  memDC;											//定义一个内存画布
		memDC.CreateCompatibleDC(pDeskDC);					//创建一个兼容的画布
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(pDeskDC,rc.Width(),rc.Height());	//创建兼容位图
		memDC.SelectObject(&bmp);							//选中位图对象	
		BITMAP bitmap;
		bmp.GetBitmap(&bitmap);
		memDC.BitBlt(0,0,bitmap.bmWidth,bitmap.bmHeight,pDeskDC,0,0,SRCCOPY);

		
			CPoint point;
			GetCursorPos(&point);
			HICON hicon = (HICON)GetCursor();
			memDC.DrawIcon(point,hicon);
		

		DWORD size=bitmap.bmWidthBytes*bitmap.bmHeight;

		BYTE* lpData = new BYTE[size];

		double panelsize  = 0;									//记录调色板大小
		if(bitmap.bmBitsPixel<16)							//判断是否为真彩色位图
			panelsize = pow(double(2),double(bitmap.bmBitsPixel*sizeof(RGBQUAD)));

		BITMAPINFOHEADER *pBInfo = new BITMAPINFOHEADER;
		pBInfo->biBitCount       = bitmap.bmBitsPixel;
		pBInfo->biClrImportant   = 0;
		pBInfo->biCompression    = 0;
		pBInfo->biHeight         = bitmap.bmHeight;
		pBInfo->biPlanes         = bitmap.bmPlanes;
		pBInfo->biSize           = sizeof(BITMAPINFOHEADER);
		pBInfo->biSizeImage      = bitmap.bmWidthBytes*bitmap.bmHeight;
		pBInfo->biWidth          = bitmap.bmWidth;
		pBInfo->biXPelsPerMeter  = 0;
		pBInfo->biYPelsPerMeter  = 0;
		BITMAPINFO bInfo;
		bInfo.bmiHeader = *pBInfo;
		GetDIBits(memDC.m_hDC,bmp,0,pBInfo->biHeight,lpData,&bInfo,DIB_RGB_COLORS);

		if(nFrames == 0)
		{
			
			if(Path.Right(1) != "\\")
				Path = Path + "\\";
			
			AVIFileOpen(&pfile,Path+"liyu1"+".avi",OF_WRITE | OF_CREATE,NULL);
			memset(&strhdr, 0, sizeof(strhdr));
			strhdr.fccType    = streamtypeVIDEO;
			strhdr.fccHandler = 0;
			strhdr.dwScale    = 1;
			strhdr.dwRate     = atoi("10");
			strhdr.dwSuggestedBufferSize = pBInfo->biSizeImage;
			SetRect(&strhdr.rcFrame,0,0,pBInfo->biWidth,pBInfo->biHeight);
			hr = AVIFileCreateStream(pfile,&ps,&strhdr); 

			opts[0]->fccType = streamtypeVIDEO;
			opts[0]->fccHandler = mmioStringToFOURCC("MSVC", 0);
			opts[0]->dwQuality = 7500;
			opts[0]->dwBytesPerSecond = 0;
			opts[0]->dwFlags = AVICOMPRESSF_VALID || AVICOMPRESSF_KEYFRAMES;
			opts[0]->lpFormat = 0;
			opts[0]->cbFormat = 0;
			opts[0]->dwInterleaveEvery = 0;

			AVIMakeCompressedStream(&pComStream,ps,&pCompressOption,NULL); 
			AVIStreamSetFormat(pComStream,0,pBInfo,sizeof(BITMAPINFOHEADER));
		}


		hr = AVIStreamWrite(pComStream,nFrames ,1,(LPBYTE)lpData,
			pBInfo->biSizeImage,AVIIF_KEYFRAME,NULL,NULL);
		nFrames++;
		
		delete []lpData;
		delete pBInfo ;	
	
		m_IsTime = TRUE;
	}
	
	CDialog::OnTimer(nTimerID);

}





UINT ThreadFunc(LPVOID pParam)
{
	
	MessageBox(NULL,_T("i am called by a thread."), _T("thread func"),MB_OK);
	return 0;
}
