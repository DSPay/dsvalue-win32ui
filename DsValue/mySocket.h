#pragma once

// mySocket ÃüÁîÄ¿±ê

class CmySocket : public CAsyncSocket
{
public:
	CmySocket();
	virtual ~CmySocket();
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
private:
	CDialog *m_pWnd;
public:
	void SetParent(CDialog *pWnd);

};


