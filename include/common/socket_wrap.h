#pragma once

class SocketWrap
{
protected:
    static void init();
    static void deinit();

    static int nOfInstance_;
};