#include <stdexcept>
#ifdef WIN32
#include <winsock2.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
// #include <arpa/inet.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <unistd.h>
#endif
#include "common/socket_wrap.h"

int SocketWrap::nOfInstance_ = 0;

void SocketWrap::init()
{
#if WIN32
    if (nOfInstance_ == 0)
    {
        WORD sockVersion = MAKEWORD(2, 2);
        WSADATA wsaData;
        if (WSAStartup(sockVersion, &wsaData) != 0)
        {
            throw std::runtime_error("Could not start WSA");
        }
    }
#endif

    ++nOfInstance_;
}

void SocketWrap::deinit()
{
    --nOfInstance_;
#if WIN32
    if (nOfInstance_ == 0)
    {
        WSACleanup();
    }
#endif
}
