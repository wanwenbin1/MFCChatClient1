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
	// TODO: �ڴ����ר�ô����/����û���


	TRACE("####OnAccept");
	CMFCChatSeverDlg* dlg = (CMFCChatSeverDlg*)AfxGetApp()->GetMainWnd();



	CAsyncSocket::OnAccept(nErrorCode);
}
