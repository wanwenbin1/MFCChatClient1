	
// MFCChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//#include "../MFCChatSever/MFCChatSeverDlg.h"
//#include "../MFCChatSever/MFCChatSeverDlg.cpp"
//using namespace CMFCChatSeverDlg;


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


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
	DDX_Control(pDX, IDC_COLOUR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONECT_BTN, &CMFCChatClientDlg::OnBnClickedConectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_SAVENAME_BTN, &CMFCChatClientDlg::OnBnClickedSavenameBtn)
	
	ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCChatClientDlg::OnBnClickedClearmsgBtn)
	ON_BN_CLICKED(IDC_AUTOSEND_CHECK, &CMFCChatClientDlg::OnBnClickedAutosendCheck)
	ON_BN_CLICKED(IDC_DISCONECT_BTN, &CMFCChatClientDlg::OnBnClickedDisconectBtn)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	WCHAR wszName[MAX_PATH] = {0};
	WCHAR strPath[MAX_PATH] = { 0 };

	GetCurrentDirectoryW(MAX_PATH, strPath);
	TRACE("####strPath=%ls", strPath);

	CString strFilePath;
	strFilePath.Format(L"%ls\\Test111.ini", strPath);

	
	DWORD dwNum=  GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL, wszName, MAX_PATH, strFilePath); ;
	if (dwNum>0)
	{
		TRACE("####wszName=%ls", wszName);
		SetDlgItemText(IDC_NAME_EDIT, wszName);
		UpdateData(FALSE);
	}
	else
	{
		WritePrivateProfileStringW(_T("CLIENT"),_T("NAME"),L"客户端",strFilePath);
		SetDlgItemText(IDC_NAME_EDIT, L"客户端");
		UpdateData(FALSE);
	}
	
	//初始化控件
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);

	m_WordColorCombo.AddString(_T("黑色"));
	m_WordColorCombo.AddString(_T("红色"));
	m_WordColorCombo.AddString(_T("蓝色"));
	m_WordColorCombo.AddString(_T("绿色"));

	m_WordColorCombo.SetCurSel(0);
	SetDlgItemText(IDC_COLOUR_COMBO, _T("黑色"));




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatClientDlg::OnPaint()
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
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);

		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);

		CBitmap aBitmap;
		aBitmap.LoadBitmap(IDB_HILL_BITMAP1);

		BITMAP bitmap;
		aBitmap.GetBitmap(&bitmap);

		CBitmap *bBitmap = dcBmp.SelectObject(&aBitmap);


		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);


















		/*CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC  dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);
		CBitmap aBitmap;
		aBitmap.LoadBitmap(IDB_HILL_BITMAP);
		BITMAP bitmap;
		aBitmap.GetBitmap(&bitmap);
		CBitmap* pbmpOld = dcBmp.SelectObject(&aBitmap);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);*/


		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatClientDlg::OnBnClickedConectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_CONECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(TRUE);
	TRACE(TEXT("[CharClient]Conect Btn"));
	CString strPort, strIP;
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	LPCSTR szIP =(LPCSTR) T2A(strIP);
	//LPCSTR szPort =(LPCSTR)strPort.GetBuffer();
	//TRACE("[CharClient]szPort=%s,szIP=%s", szPort,szIP);
	int iPort = _ttoi(strPort);
	TRACE("###m_client Creat Sucess....");
	//创建套接字
	m_client = new CMySocket;

	
	if (!m_client->Create())
	{
		TRACE("###m_client Creat error %d", GetLastError());
		return;
	}
	else
	{
		TRACE("###m_client Creat Sucess");
	}
	if (m_client->Connect(strIP, iPort)==SOCKET_ERROR)
	{
		TRACE("###m_client Conect error %d", GetLastError());
		return;
	}

}


void CMFCChatClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strName;
	GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(strName);
	CString strTempl;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowText(strTempl);
	strTempl = strName + _T(":") + strTempl;
	USES_CONVERSION;
	char* szSendBuf = T2A(strTempl);
	//发送给服务端
	m_client->Send(szSendBuf, SEND_MAX_BUF);
	//显示到列表框
	CString strShow;
	
	CString strInfo = _T("");
	
	strShow = CatShowString(strInfo,strTempl);
	m_list.AddString(strShow);
	UpdateData(FALSE);
}

CString CMFCChatClientDlg::CatShowString(CString strInfo, CString strMsg)
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


void CMFCChatClientDlg::OnBnClickedSavenameBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//保存昵称
	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName);
	if (strName.GetLength()<=0)
	{
		MessageBox(_T("昵称不能为空"));
		return;
	}
	if (IDOK == AfxMessageBox(_T("真的要修改昵称吗?"), MB_OKCANCEL))
	{

		
		WCHAR strPath[MAX_PATH] = { 0 };

		GetCurrentDirectoryW(MAX_PATH, strPath);
		TRACE("####strPath=%ls", strPath);

		CString strFilePath;
		strFilePath.Format(L"%ls\\Test111.ini", strPath);

		GetDlgItemText(IDC_NAME_EDIT, strName);
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
		MessageBox(strFilePath);
	}
}




void CMFCChatClientDlg::OnBnClickedClearmsgBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCChatClientDlg::OnBnClickedAutosendCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(TRUE);
	}

}


void CMFCChatClientDlg::OnBnClickedDisconectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//d控制控件
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONECT_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONECT_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);
	//回收资源
	m_client->Close();
	if (m_client!=NULL)
	{
		delete m_client;
		m_client = NULL;
	}
	//显示到列表框
	CString strShow;
	strShow = CatShowString(_T(""), _T("断开与服务器的连接"));
}


HBRUSH CMFCChatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	CString strColor;
	m_WordColorCombo.GetWindowText(strColor);
	if (strColor=="黑色")
	{
		if (IDC_LIST1==pWnd->GetDlgCtrlID()||IDC_SENDMSG_EDIT==pWnd->GetDlgCtrlID())
		{
			pDC->SetTextColor(RGB(0,0,0));
		}
	}
	if (strColor == "红色")
	{
		if (IDC_LIST1 == pWnd->GetDlgCtrlID() || IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID())
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
	}
	if (strColor == "蓝色")
	{
		if (IDC_LIST1 == pWnd->GetDlgCtrlID() || IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID())
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
	}



	return hbr;
}
