#include <arpa/inet.h>
#include <cstdint>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#include "c_api/wol.h"
#include "utils/tools.h"

int startupSocket()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0)
    {
        return CreateSocketFail;
    }

    int optval = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(optval));
    if (ret < 0)
    {
        return CreateSocketFail;
    }

    return sockfd;
}

void closeSocket(int sockfd)
{
    if (sockfd < 0)
        return;

    close(sockfd);
}

int sendMagicPacket(int sockfd, const char* macAddr, const char* ipAddr, int port)
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
    int ret = sendto(sockfd, message.c_str(), message.length(), 0, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if (ret < 0)
    {
        return SendDataFail;
    }

    return SuccessCode;
}