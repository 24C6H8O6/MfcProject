// ServerSocket.cpp: 구현 파일
//

#include "pch.h"
#include "testServer2.h"
#include "ServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 멤버 함수
void CServerSocket::SetWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

// 서버가 클라이언트 연결을 시도하면
void CServerSocket::OnAccept(int nErrorCode)
{
	CClientSocket* pClient = new CClientSocket;
	// 클라이언트를 수락하려 하고
	if (Accept(*pClient))
	{
		pClient->SetWnd(m_hWnd);
	}
	else
	{
		delete pClient;
		AfxMessageBox(_T("ERROR : Failed can't accept new Client!"));
	}
	// 윈도우에 WM_ACCEPT_SOCKET 메시지로 클라이언트 소켓 정보를 전달
	// WM_ACCEPT_SOCKET 메시지로 testServer2Dlg.cpp의 
	// ON_MESSAGE(WM_ACCEPT_SOCKET, &CtestServer2Dlg::OnAcceptSocket) 이 코드가 실행되어
	// CtestServer2Dlg::OnAcceptSocket 함수 실행
	SendMessage(m_hWnd, WM_ACCEPT_SOCKET, 0, (LPARAM)pClient);
	CSocket::OnAccept(nErrorCode);
}