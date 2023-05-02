#include "utils/tools.h"

namespace utils
{
std::string getEther(const std::string& hardwareAddr)
{
    std::string etherAddr;

    for (size_t i = 0; i < hardwareAddr.length();)
    {
        auto hex = std::stoul(hardwareAddr.substr(i, 2), nullptr, 16);
        etherAddr.push_back(hex & 0xFF);

        i += 2;
        // We might get a colon here, but it is not required.
        if (hardwareAddr[i] == ':')
            ++i;
    }

    return etherAddr;
}
} // namespace utils