#include "pch.h"
#include "CChatSocket.h"
//#include "MFCChatSever.h"
#include "MFCChatSeverDlg.h"
#include "../MFCChatClient/MFCChatClient.h"


CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}

void CChatSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	TRACE("###Server OnReceive");
	CMFCChatSeverDlg* dlg = (CMFCChatSeverDlg*)AfxGetApp()->GetMainWnd();
	char szRecevBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecevBuf, SEND_MAX_BUF, 0);
	TRACE("###Server=%s", szRecevBuf);
	USES_CONVERSION;
	CString strRecvMSG = A2W(szRecevBuf);

	//CString strShow = _T("��:");
	//CString strTime;
	//dlg->m_tm = CTime::GetCurrentTime();
	//strTime =dlg->m_tm.Format("%X");
	////2018 ��:....
	//strShow = strTime + strShow;
	//strShow += strRecvMSG;
	CString strShow;
	CString strInfo = _T("��:");
	strShow=dlg->CatShowString(strInfo, strRecvMSG);

	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
}
