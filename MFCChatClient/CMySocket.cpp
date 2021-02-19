#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClientDlg.h"
#include "MFCChatClient.h"


void CMySocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	//TRACE("###OnConect");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
#if 0
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X");
	str += _T("与服务器连接成功");
	dlg->m_list.AddString(str);
#endif
	CString strShow;
	CString strInfo = _T("我:");
	CString strMsg = _T("与服务器连接成功");
	strShow =dlg-> CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnConnect(nErrorCode);
}


void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	TRACE("###CMySocket OnReceve");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecevBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecevBuf, SEND_MAX_BUF, 0);
	TRACE("###Server=%s", szRecevBuf);
	USES_CONVERSION;
	CString strRecvMSG = A2W(szRecevBuf);
	//CString strShow = _T("服务端:");
	//CString strTime;
	//dlg->m_tm = CTime::GetCurrentTime();
	//strTime = dlg->m_tm.Format("%X");
	////2018 服务端:....
	//strShow = strTime + strShow;
	//strShow += strRecvMSG;

	CString strShow;
	CString strInfo = _T("服务器:");
	strShow = dlg->CatShowString(strInfo, strRecvMSG);

	dlg->m_list.AddString(strShow);
	//dlg->m_list.UpdateData(FALSE);
	CAsyncSocket::OnReceive(nErrorCode);
}
