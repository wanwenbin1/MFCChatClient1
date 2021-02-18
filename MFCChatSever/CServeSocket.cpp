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



	CAsyncSocket::OnAccept(nErrorCode);
}
