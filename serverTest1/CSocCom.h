#pragma once

// CSocCom 명령 대상
// 통신용 소켓
#define UM_RECEIVE WM_USER+2

class CSocCom : public CSocket
{
public:
	CSocCom();
	virtual ~CSocCom();

	HWND m_hWnd;
	void CSocCom::Init(HWND hWnd);
	virtual void OnReceive(int nErrorCode);
};


