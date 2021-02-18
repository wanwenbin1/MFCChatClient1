#pragma once
#include <afxsock.h>


class CMySocket :
    public CAsyncSocket
{
public:


    virtual void OnConnect(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
};

