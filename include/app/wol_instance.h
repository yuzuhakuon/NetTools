#pragma once
#include "common/socket_wrap.h"

class WakeOnLanInstance : public SocketWrap
{
public:
    WakeOnLanInstance();
    ~WakeOnLanInstance();

    /**
     * @brief sent wol magic packet
     *
     * @param macAddr mac address, default to ff.ff.ff.ff.ff.ff
     * @param ipAddr ip address, default to 255.255.255.255
     * @param port default to 9
     * @return int the status of function called
     */
    int sendMagicPacket(const char* macAddr, const char* ipAddr, int portF);

    bool isFailed();

private:
    int sockfd_{-1};
};