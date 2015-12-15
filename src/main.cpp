#include "SocketHandler.h"

int main()
{
    WaterTank wt = WaterTank();
    SocketHandler* sh = new SocketHandler(&wt, "localhost", 12345);
    wt.setSocketHandler(sh);

    sh->t.join();
    delete sh;
    return 0;
}
