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
	dlg->m_chat = new CChatSocket;
	//��ʼ��������
	Accept(*(dlg->m_chat));
	/*CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str=dlg->m_tm.Format("%X");
	str += _T("�ͻ������ӳɹ�");*/
	
	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("�ͻ������ӳɹ�");
	strShow =dlg-> CatShowString(strInfo, strMsg);

	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);
	CAsyncSocket::OnAccept(nErrorCode);
}
