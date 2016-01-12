#include "SocketHandler.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    cout << "Megabaeckerei-Oven" << endl;
    cout << "------------------" << endl;
    cout << endl;

    Oven wt = Oven();
    SocketHandler* sh = new SocketHandler(&wt, "127.0.0.1", 12345);
    wt.setSocketHandler(sh);

    sh->t.join();
    delete sh;
    return 0;
}
