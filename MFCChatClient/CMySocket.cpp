#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClientDlg.h"
#include "MFCChatClient.h"


void CMySocket::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	//TRACE("###OnConect");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
#if 0
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X");
	str += _T("����������ӳɹ�");
	dlg->m_list.AddString(str);
#endif
	CString strShow;
	CString strInfo = _T("��:");
	CString strMsg = _T("����������ӳɹ�");
	strShow =dlg-> CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnConnect(nErrorCode);
}


void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	TRACE("###CMySocket OnReceve");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecevBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecevBuf, SEND_MAX_BUF, 0);
	TRACE("###Server=%s", szRecevBuf);
	USES_CONVERSION;
	CString strRecvMSG = A2W(szRecevBuf);
	//CString strShow = _T("�����:");
	//CString strTime;
	//dlg->m_tm = CTime::GetCurrentTime();
	//strTime = dlg->m_tm.Format("%X");
	////2018 �����:....
	//strShow = strTime + strShow;
	//strShow += strRecvMSG;

	CString strShow;
	CString strInfo = _T("������:");
	strShow = dlg->CatShowString(strInfo, strRecvMSG);

	dlg->m_list.AddString(strShow);
	//dlg->m_list.UpdateData(FALSE);
	CAsyncSocket::OnReceive(nErrorCode);
}
