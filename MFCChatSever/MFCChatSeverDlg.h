
// MFCChatSeverDlg.h: 头文件
//

#pragma once

#include "CServeSocket.h"
#include "CChatSocket.h"

// CMFCChatSeverDlg 对话框
class CMFCChatSeverDlg : public CDialogEx
{
// 构造
public:
	CMFCChatSeverDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATSEVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartBtn();
	CListBox m_list;
	CServeSocket* m_serve;
	CChatSocket* m_chat;
	//CTime m_tm;
	
	afx_msg void OnBnClickedDisconnectBtn();
	afx_msg void OnBnClickedQqBtn();
	
	afx_msg void OnBnClickedButton3();
	CString CatShowString(CString strInfo,CString strMsg);
	afx_msg void OnBnClickedClearBtn();
	CComboBox m_WordColour;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
