// ClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "testServer2.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수

// 윈도우 핸들
void CClientSocket::SetWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

//
void CClientSocket::OnReceive(int nErrorCode)
{
	// 문자열 저장하는 변수 strTmp, strIPAddress 초기화
	CString strTmp = _T(""), strIPAddress = _T("");
	// unsigned integer 변수 uPortNumber 선언 후 0으로 초기화
	UINT uPortNumber = 0;
	// 1024바이트 크기의 TCHAR 타입의 버퍼 strBuffer 선언
	TCHAR strBuffer[1024];
	// 0으로 초기화
	ZeroMemory(strBuffer, sizeof(strBuffer));
	// 클라이언트 소켓의 상대편 정보를 가져와서 IP주소와 포트 번호 저장
	GetPeerName(strIPAddress, uPortNumber);
	// 데이터를 수신했을 때 0보다 크면
	if (Receive(strBuffer, sizeof(strBuffer)) > 0) {
		// 수신된 데이터와 상대편의 IP주소,포트번호를 포매팅해 strTmp로 저장
		strTmp.Format(_T("[%s : %d]: %s"), strIPAddress, uPortNumber, strBuffer);
	}
	// Main Window에 WM_CLIENT_MSG_RECV 메시지로 strTmp를 보냄
	// 0은 부가적인 데이터 사용 X
	SendMessage(m_hWnd, WM_CLIENT_MSG_RECV, 0, (LPARAM)((LPCTSTR)strTmp));
	// 부모 클래스의 OnReceive 함수 호출
	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{
	SendMessage(m_hWnd, WM_CLIENT_CLOSE, 0, (LPARAM)this);
	CSocket::OnClose(nErrorCode);
}