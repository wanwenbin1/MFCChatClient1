#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClientDlg.h"


void CMySocket::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	//TRACE("###OnConect");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X");
	str += _T("����������ӳɹ�");
	dlg->m_list.AddString(str);
	CAsyncSocket::OnConnect(nErrorCode);
}


void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	TRACE("###OnReceve");
	CAsyncSocket::OnReceive(nErrorCode);
}
