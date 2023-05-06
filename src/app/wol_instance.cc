#include <cstdint>
#include <stdexcept>
#include <string>

#include "common/network_inc.h"
#include "app/wol_instance.h"
#include "common/status_code.h"
#include "utils/tools.h"


WakeOnLanInstance::WakeOnLanInstance()
{
    init();
    sockfd_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd_ < 0)
    {
        sockfd_ = InvalidSocket;
        return;
    }

    int optval = 1;
    int ret = setsockopt(sockfd_, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(optval));
    if (ret < 0)
    {
        sockfd_ = InvalidSocket;
    }
}

WakeOnLanInstance::~WakeOnLanInstance()
{
    if (sockfd_ > 0)
    {
#if WIN32
        closesocket(sockfd_);
#else
        close(sockfd_);
#endif
    }

    deinit();
}

int WakeOnLanInstance::sendMagicPacket(const char* macAddr, const char* ipAddr, int port)
{
    const std::string hardwareAddr{macAddr};
    const std::string etherAddr = utils::getEther(hardwareAddr);

    if (etherAddr.length() != 6)
    {
        return InvalidMACAddress;
    }

    // Build the message to send.
    std::string message(6, 0xFF);
    for (size_t i = 0; i < 16; ++i)
    {
        message += etherAddr;
    }

    // Set up address
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ipAddr);

    // Send the packet out.
    int ret = sendto(sockfd_, message.c_str(), message.length(), 0, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if (ret < 0)
    {
        return SendDataFailed;
    }

    return SuccessCode;
}

bool WakeOnLanInstance::isFailed() { return sockfd_ <= 0; }
