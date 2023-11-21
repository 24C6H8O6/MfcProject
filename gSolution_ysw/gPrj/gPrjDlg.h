
// gPrjDlg.h: 헤더 파일

// 추가된 부분(4-3)
#include "DlgImage.h"

#pragma once


// CgPrjDlg 대화 상자
class CgPrjDlg : public CDialogEx
{
// 생성입니다.
public:
	CgPrjDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 추가(4-3)
	CDlgImage *m_pDlgImage;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GPRJ_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	int m_edit_radius=0;
	int n_Parent_Width = 960;
	int n_Parent_Height = 640;
	afx_msg void OnBnClickedBtnMakeCircle();
	void drawCross(CDC* pDC, int x, int y, int nRadius);
	void drawCircle(CDC* pDC, int x, int y, int nRadius);
	CEdit m_edit_X;
	CEdit m_edit_Y;
};
