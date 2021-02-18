#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClientDlg.h"


void CMySocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	//TRACE("###OnConect");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X");
	str += _T("与服务器连接成功");
	dlg->m_list.AddString(str);
	CAsyncSocket::OnConnect(nErrorCode);
}


void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	TRACE("###OnReceve");
	CAsyncSocket::OnReceive(nErrorCode);
}
