
// MFCChatSeverDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatSever.h"
#include "MFCChatSeverDlg.h"
#include "afxdialogex.h"
//#include "CServeSocket.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "../MFCChatClient/resource.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCChatSeverDlg 对话框



CMFCChatSeverDlg::CMFCChatSeverDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSEVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatSeverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_list);
	DDX_Control(pDX, IDC_COLOUR_COMBOX, m_WordColour);
}

BEGIN_MESSAGE_MAP(CMFCChatSeverDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CMFCChatSeverDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CMFCChatSeverDlg::OnBnClickedDisconnectBtn)
	ON_BN_CLICKED(IDC_QQ_BTN, &CMFCChatSeverDlg::OnBnClickedQqBtn)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCChatSeverDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &CMFCChatSeverDlg::OnBnClickedClearBtn)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCChatSeverDlg 消息处理程序

BOOL CMFCChatSeverDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));

	m_WordColour.AddString(_T("黑色"));
	m_WordColour.AddString(_T("红色"));
	m_WordColour.AddString(_T("蓝色"));


	m_WordColour.SetCurSel(0);
	SetDlgItemText(IDC_COLOUR_COMBOX, _T("黑色"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatSeverDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCChatSeverDlg::OnPaint()
{
	//TRACE("###OnPaint");
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
		//1.dc
		CPaintDC dc(this);
		//2.目的区域
		CRect rect;
		GetClientRect(&rect);
		TRACE("widh=%d,hegth=%d",rect.Width(),rect.Height());
		//3.定义 创建
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);
		//4.载入图片资源
		CBitmap bmpBackroud;
		bmpBackroud.LoadBitmap(IDB_HILL_BITMAP111);
		//5.将图片资源载入bitmap位图
		BITMAP bBitmap;
		bmpBackroud.GetBitmap(&bBitmap);
		//6.将位图选入内存设备环境
		CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackroud);
		//7.开始绘制
		/*int x, int y, int nWidth, int nHeight, CDC* pSrcDC,
			int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, DWORD dwRop)*/
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp,
			0, 0, bBitmap.bmWidth, bBitmap.bmHeight, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatSeverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatSeverDlg::OnBnClickedStartBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_START_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(TRUE);

	MessageBox(TEXT("11111111111"));
	TRACE(TEXT("####Conect Btn"));
	CString strPort;
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	
	//LPCSTR szPort =(LPCSTR)strPort.GetBuffer();
	TRACE("####szPort=%s", szPort);
	int iPort = _ttoi(strPort);
	//创建服务器SOCKET的对象
	m_serve = new CServeSocket;
	//创建SOCK 套接字
	if (!m_serve->Create(iPort))
	{
		TRACE("###m_server Creat errorCode= %d", GetLastError());
		return;
	}
	
	if (!m_serve->Listen())
	{
		TRACE("###m_server Listen errorCode=%d", GetLastError());
		return;
	}
	/*CString str;
	m_tm = CTime::GetCurrentTime();
	str=m_tm.Format("%X");
	str += _T("建立服务");*/
	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("建立服务");
	strShow = CatShowString(strInfo, strMsg);
	m_list.AddString(strShow);
	UpdateData(FALSE);
	//清空编辑框
	//GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));

}





void CMFCChatSeverDlg::OnBnClickedDisconnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);

	m_serve->Close();
	
	if (m_serve!=NULL)
	{
		delete m_serve;
		m_serve = NULL;
	}
	
	if (m_chat!=NULL)
	{
		delete m_chat;
		m_chat = NULL;
	}
	CString strShow;
	strShow = CatShowString(_T(""), _T("服务器停止"));
	m_list.AddString(strShow);
	UpdateData(FALSE);
}


void CMFCChatSeverDlg::OnBnClickedQqBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}







void CMFCChatSeverDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(TEXT("sddfsfd"));
	MessageBox(TEXT("sddfsfd"));
	// TODO: 在此添加控件通知处理程序代码
	//TRACE("###Server Begin SendMsg");
	CString strTempl;
	GetDlgItem(IDC_SEND_EDIT)->GetWindowText(strTempl);

	USES_CONVERSION;
	char* szSendBuf = T2A(strTempl);
	//发送给服务端
	m_chat->Send(szSendBuf, SEND_MAX_BUF, 0);

	//显示到列表框
	//CString strShow = _T("服务端:");
	//CString strTime;
	//m_tm = CTime::GetCurrentTime();
	//strTime = m_tm.Format("%X");
	////2018 我:....
	//strShow = strTime + strShow;
	//strShow += strTempl;
	CString strShow;
	CString strInfo = _T("服务端:");
	CString strMsg = strTempl;
	strShow = CatShowString(strInfo, strMsg);
	m_list.AddString(strShow);
	UpdateData(FALSE);

	GetDlgItem(IDC_SEND_EDIT)->SetWindowTextW(_T(""));
}

CString CMFCChatSeverDlg::CatShowString(CString strInfo, CString strMsg)
{
	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X");
	CString strShow;
	strShow = strTime + strShow;
	strShow += strInfo;
	strShow += strMsg;
	return strShow;
}



void CMFCChatSeverDlg::OnBnClickedClearBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


HBRUSH CMFCChatSeverDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	CString strColor;
	int i=m_WordColour.GetCurSel();
	m_WordColour.GetLBText(i, strColor);
	//m_WordColorCombo.GetWindowText(strColor);
	if (strColor == _T("黑色"))
	{
		if (IDC_MSG_LIST == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID())
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
	}
	if (strColor == _T("红色"))
	{
		if (IDC_MSG_LIST == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID())
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
	}
	if (strColor == _T("蓝色"))
	{
		if (IDC_MSG_LIST == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID())
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
	}
	return hbr;
}
