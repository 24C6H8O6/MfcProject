
// testClient2Dlg.h: 헤더 파일
//

#pragma once
#include "ClientSocket.h"

// CtestClient2Dlg 대화 상자
class CtestClient2Dlg : public CDialogEx
{
// 생성입니다.
private:
	CClientSocket m_ClientSocket;

public:
	CtestClient2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CListBox m_list_msg;
	CEdit m_edit_send;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTCLIENT2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	afx_msg LRESULT OnClientRecv(WPARAM wParam, LPARAM lParam);

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSend();
};
