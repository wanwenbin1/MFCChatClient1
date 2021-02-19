#include "pch.h"
#include "MFCChatSeverDlg.h"
#include "CServeSocket.h"


CServeSocket::CServeSocket()
{
}

CServeSocket::~CServeSocket()
{
}

void CServeSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类


	TRACE("####OnAccept");
	CMFCChatSeverDlg* dlg = (CMFCChatSeverDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_chat = new CChatSocket;
	//开始接收连接
	Accept(*(dlg->m_chat));
	/*CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str=dlg->m_tm.Format("%X");
	str += _T("客户端连接成功");*/
	
	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("客户端连接成功");
	strShow =dlg-> CatShowString(strInfo, strMsg);

	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);
	CAsyncSocket::OnAccept(nErrorCode);
}
