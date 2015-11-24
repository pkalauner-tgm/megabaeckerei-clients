#include "SocketHandler.h"

int main()
{
    WaterTank wt = WaterTank();
    SocketHandler* sh = new SocketHandler(&wt, "127.0.0.1", 12345);
    Sleep(1000);
    for (int i=1;i<=5;i++) {
        sh->sendMessage("test " + std::to_string(i));
        Sleep(500);
    }
    delete sh;
    return 0;
}
