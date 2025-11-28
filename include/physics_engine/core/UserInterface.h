#include <Windows.h>
#include <thread>
#include <atomic>

//Global Defines
#define ReadThreadSleepingTime 10

class UserInterface {
    private:

    public:
        UserInterface() = default;
        

        void readResWin();
};