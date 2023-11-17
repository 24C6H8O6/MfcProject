
// testClient2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "testClient2.h"
#include "testClient2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 포트번호
#define PORT 8888

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestClient2Dlg 대화 상자



CtestClient2Dlg::CtestClient2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTCLIENT2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestClient2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	// 추가한 부분
	DDX_Control(pDX, IDC_EDIT_SEND, m_edit_send);
	DDX_Control(pDX, IDC_LIST_MSG, m_list_msg);
	DDX_Control(pDX, IDC_EDIT_FILENAME, m_edit_fn);
}

BEGIN_MESSAGE_MAP(CtestClient2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CtestClient2Dlg::OnBnClickedBtnSend)
	// 추가한 부분
	ON_MESSAGE(WM_CLIENT_RECV, &CtestClient2Dlg::OnClientRecv)
	ON_BN_CLICKED(IDC_BUTTON1, &CtestClient2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CtestClient2Dlg 메시지 처리기

BOOL CtestClient2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 서버 연결 부분(클라이언트를 실행하면 바로 연결됨)
	m_ClientSocket.SetWnd(this->m_hWnd);
	m_ClientSocket.Create();
	if (m_ClientSocket.Connect(_T("127.0.0.1"), PORT) == FALSE) {
		AfxMessageBox(_T("ERROR : Failed to connect Server"));
		PostQuitMessage(0);
		return FALSE;
	}
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CtestClient2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CtestClient2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CtestClient2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

afx_msg LRESULT CtestClient2Dlg::OnClientRecv(WPARAM wParam, LPARAM lParam)
{
	CString msgCStr = (LPCTSTR)lParam;
	// CString을 사용하여 리스트에 메시지 추가
	m_list_msg.AddString(msgCStr);
	return 0;
}


void CtestClient2Dlg::OnBnClickedBtnSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str;
	// LPCTSTR(Long Pointer to Const TCHAR String)
	// 문자열을 가리키는 포인터 lpctstr 선언
	LPCTSTR lpctstr;
	// 다이얼로그의 컨트롤과 멤버 변수 간의 데이터를 동기화
	UpdateData(TRUE);
	// m_edit_send의 텍스트를 str에 저장
	m_edit_send.GetWindowTextW(str);
	// str을 TCHAR 문자열 포인터로 변환
	lpctstr = (LPCTSTR)str;
	// m_ClientSocket을 사용해 문자열을 서버로 전송
	// lstrlen(lpctstr)*2 : 유니코드 문자열의 길이를 바이트 단위로 2바이트씩 처리
	m_ClientSocket.Send(lpctstr,lstrlen(lpctstr)*2);
	// 윈도우의 텍스트 지우고
	m_edit_send.SetWindowTextW(_T(""));
	// 다이얼로그 데이터 업데이트
	UpdateData(FALSE);
}

// 파일 보내는 법
void CtestClient2Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	LPCTSTR strFileName;
	m_edit_fn.GetWindowTextW(str);
	strFileName = (LPCTSTR)str;
	CFile sourceFile;
	sourceFile.Open((LPCTSTR)strFileName, CFile::modeRead | CFile::typeBinary);
	bool isFile = true;
	m_ClientSocket.Send(&isFile, sizeof(bool));
	int nNameLen = str.GetLength();
	m_ClientSocket.Send(&nNameLen, 4);
	m_ClientSocket.Send((LPCTSTR)strFileName, nNameLen);
	byte* data = new byte[4096];
	DWORD dwRead;
	do
	{
		dwRead = sourceFile.Read(data, 4096);
		m_ClientSocket.Send(data, dwRead);
	} while (dwRead > 0);
	delete data;
	sourceFile.Close();
}
