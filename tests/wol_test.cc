#include <iostream>

#include "app/wol_instance.h"

int main(int argc, char* argv[])
{
    constexpr char defaultIp[] = "255.255.255.255";
    constexpr int port = 9;
    std::string hardwareAddr = "c4:65:16:b2:64:18";
    if (argc > 1)
    {
        hardwareAddr = argv[1];
    }
    std::cout << hardwareAddr << std::endl;

    WakeOnLanInstance wolIns;
    if (wolIns.isFailed())
    {
        std::cout << "create socket fd fail." << std::endl;
        return -1;
    }

    int ret = wolIns.sendMagicPacket(hardwareAddr.c_str(), defaultIp, port);
    std::cout << "ret: " << ret << std::endl;

    return 0;
}
