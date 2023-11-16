// ClientSocket.cpp: 구현 파일
//

#include "pch.h"
#include "testClient2.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수


void CClientSocket::SetWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

// 소켓이 메시지를 수신할 때 발동
void CClientSocket::OnReceive(int nErrorCode)
{
	// 버퍼 저장 크기
	TCHAR szBuffer[1024];
	// 버퍼를 0으로 초기화
	ZeroMemory(szBuffer, sizeof(szBuffer));
	// 수신된 데이터 szBuffer의 크기가 0보다 크다면
	if (Receive(szBuffer, sizeof(szBuffer)) > 0){
		// m_Wnd가 알도록 WM_CLIENT_RECV라는 메시지로 szBuffer를 보냄
		SendMessage(m_hWnd, WM_CLIENT_RECV, 0, (LPARAM)szBuffer);
	}
	// 추가적 기본 동작 수행
	CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{
	ShutDown();
	Close();

	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("ERROR : Disconnected from server!"));
	PostQuitMessage(0);
}