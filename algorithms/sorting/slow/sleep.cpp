#include <iostream>
#include <vector>
#include <thread>
#include <unistd.h>
using std::vector;
using std::cout;
using std::endl;
using std::thread;

void sortThread (int x) {
    usleep(10000 * x);
    cout << x << " ";
}
 
int main() {
    vector<thread*> threads; 
    srand((unsigned)time(NULL)); 
    
    for (int x = 0; x < 10; ++x ) {
        int r = rand() % 20 + 5;
        cout << r << " ";
        thread* t = new thread(sortThread, r);
        threads.push_back(t);
    }

    cout << endl << "sorted:" << endl;
 
    for (auto t = threads.begin(); t != threads.end(); ++t) {
        (*t)->join();
        delete (*t);
    }
 
    cout << endl << endl;
    return 0;
}
 