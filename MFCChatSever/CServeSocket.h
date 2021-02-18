#pragma once
#include <afxsock.h>


class CServeSocket :
    public CAsyncSocket
{
public:
    CServeSocket();
    virtual ~CServeSocket();
    virtual void OnAccept(int nErrorCode);

};

