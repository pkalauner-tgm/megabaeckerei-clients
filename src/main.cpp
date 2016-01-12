#include "SocketHandler.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    cout << "Megabaeckerei-Watertank" << endl;
    cout << "-----------------------" << endl;
    cout << endl;

    WaterTank wt = WaterTank();
    SocketHandler* sh = new SocketHandler(&wt, "127.0.0.1", 12345);
    wt.setSocketHandler(sh);

    sh->t.join();
    delete sh;
    return 0;
}
