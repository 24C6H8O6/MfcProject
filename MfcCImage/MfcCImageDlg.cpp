﻿
// MfcCImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MfcCImage.h"
#include "MfcCImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMfcCImageDlg 대화 상자



CMfcCImageDlg::CMfcCImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfcCImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMfcCImageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMAGE, &CMfcCImageDlg::OnBnClickedBtnImage)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CMfcCImageDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CMfcCImageDlg::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMfcCImageDlg::OnBnClickedBtnAction)
END_MESSAGE_MAP()


// CMfcCImageDlg 메시지 처리기

BOOL CMfcCImageDlg::OnInitDialog()
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMfcCImageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMfcCImageDlg::OnPaint()
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
HCURSOR CMfcCImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMfcCImageDlg::OnBnClickedBtnImage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	// m_image의 첫번째 포인터의 값을 가져오겠다 는 의미
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	// 그라데이션
	
	/*for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			fm[j * nPitch + i] = (j % 0xff);
		}
	}*/
	
	

	// fm[0 * nPitch + 0] = 128;
	// fm[0 * nPitch + 1] = 128;
	// fm[1 * nPitch + 1] = 128;
	/*
	for (int j = 0; j < nHeight/2; j++) {
		for (int i = 0; i < nWidth/2; i++) {
			fm[j * nPitch + i] = 200;
		}
	}
	*/
	
	UpdateDisplay();
}

CString g_strFileImage = _T("C:\\Users\\user\\Downloads\\save.bmp");
void CMfcCImageDlg::OnBnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_image.Save(g_strFileImage);
}


void CMfcCImageDlg::OnBnClickedBtnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_image != NULL) {
		m_image.Destroy();
	}
	m_image.Load(g_strFileImage);

	UpdateDisplay();
}

void CMfcCImageDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

void CMfcCImageDlg::moveRect()
{
	// static을 쓰지 않고 int로만 하면 계속 0으로 초기화
	// static을 쓰면 값을 기억함
	static int nSttX = 0;
	static int nSttY = 0;
	int nGray = 80;
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	int nRadius = 20;
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	
	// 이미지를 항상 클리어하고 다시 그리는 부분
	// memset(fm, 0xff, nWidth * nHeight);

	// 그려지는게 메모리 밖으로 가면 죽음
	drawCircle(fm, nSttX, nSttY, nRadius, 0xff);
	drawCircle(fm, ++nSttX, ++nSttY, nRadius, nGray);

	// fm : 메모리 주소

	UpdateDisplay();
	CString strFile;
	strFile.Format(_T("D:\\d.jpg"), nSttX);
	m_image.Save(strFile);
}

void CMfcCImageDlg::OnBnClickedBtnAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (int i = 0; i < 400; i++) {
		moveRect();
		Sleep(10);
	}
		
}

BOOL CMfcCImageDlg::validImgPos(int x, int y) 
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	// 0,0 의 영역을 만듬
	CRect rect(0, 0, nWidth, nHeight);
	// CPoint 안의 x,y가  rect 영역에 들어가면 true, 안 들어가면 false
	// PtInRect : point in rectangle
	return rect.PtInRect(CPoint(x, y));
}

void CMfcCImageDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if(isInCircle(i,j,nCenterX,nCenterY,nRadius))
				fm[j * nPitch + i] = nGray;
		}
	}
};

bool CMfcCImageDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}