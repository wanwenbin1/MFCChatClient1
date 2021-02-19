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
	CString strName;
	CString strInfo = _T("��:");
	
	CString strMsg = _T("����������ӳɹ�");
	strShow =dlg-> CatShowString(strName, strMsg);
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
	CString strInfo = _T("�����");
	strShow = dlg->CatShowString(strInfo, strRecvMSG);

	dlg->m_list.AddString(strShow);
	//ѡ�е�ѡ��ť
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck())
	{
		//�Զ� �ظ�
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, strAutoSendMsg);
		 
		//2.
		CString strName;
		dlg->GetDlgItemText(IDC_NAME_EDIT, strAutoSendMsg);
		CString strMsg = strName+("[�Զ��ظ�]") + strAutoSendMsg;
		char* sendBuf = T2A(strMsg);
		dlg->m_client->Send(sendBuf, SEND_MAX_BUF, 0);
		CString strShow;
		strShow = dlg->CatShowString(_T(""), strMsg);
		dlg->m_list.AddString(strShow);
		dlg->m_list.UpdateData(FALSE);
	}

	//dlg->m_list.UpdateData(FALSE);
	CAsyncSocket::OnReceive(nErrorCode);
}
