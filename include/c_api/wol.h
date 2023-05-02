#pragma once

#define SuccessCode 0
#define UnknownError -1
#define CreateSocketFail -2
#define InvalidMACAddress -3
#define InvalidIPAddress -4
#define SendDataFail -5

/**
 * @brief create sock fd
 *
 * @return int success if greater than 0
 */
int startupSocket();

void closeSocket(int sockfd);

/**
 * @brief sent wol magic packet
 *
 * @param sockfd sock fd
 * @param macAddr mac address, default to ff.ff.ff.ff.ff.ff
 * @param ipAddr ip address, default to 255.255.255.255
 * @param port default to 9
 * @return int the status of function called
 */
int sendMagicPacket(int sockfd, const char* macAddr, const char* ipAddr, int port);
