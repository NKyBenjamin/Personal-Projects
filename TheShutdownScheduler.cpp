// Copyright by N'Ky Benjamin. All rights reserved.

#include <iostream>
#include <thread>
#include <chrono>
#include <windows.h>
#include <sstream>

using namespace std;

void notification(const string& message) {
    MessageBoxA(NULL, message.c_str(), "SHUTDOWN REMINDER!", MB_OK | MB_ICONINFORMATION);
}

void timeNotify(const string& message) {
    MessageBoxA(NULL, message.c_str(), "THE TIME HAS BEEN SET!", MB_OK | MB_ICONINFORMATION);
}

void timedShutdown(int hour, int minute) {
    while (true) {
        time_t time_now = time(0);
        tm *localTime = localtime(&time_now);

        int currentHr = localTime->tm_hour;
        int currentMin = localTime->tm_min;
        int minutesLeft = (hour - currentHr) * 60 + (minute - currentMin);

        if (minutesLeft == 10) {
            notification("We are shutting down in 10 minutes! Be prepared!");
        }
        else if (minutesLeft == 3) {
            notification("Better save your work or hop off the game! You have 3 minutes left!");
        }
        
        if (minutesLeft <= 0) {
            cout << "Currently Shutting Down Your Computer, N'Ky! Goodnight!" << endl;
            system("shutdown /s /t 0");
            break;
        }

        this_thread::sleep_for(chrono::minutes(1));
    }
}

int main() {
    int hour;
    int minute;

    cout << "What's the time for shutdown? Enter your time in 24-hour format and leave a space in between your hour and minutes!\n For example: 3:59pm = 15 59 :" << endl;
    cout << "Enter here: ";
    cin >> hour >> minute;

    FreeConsole();

    stringstream mess;
    mess << "Device currently set to shutdown at " << hour << ":" << minute << "! Make sure to prepare and plan, and you will get a notification when 10 minutes are left!" << endl;
    timeNotify(mess.str());
    timedShutdown(hour, minute); 

    return 0;
}

