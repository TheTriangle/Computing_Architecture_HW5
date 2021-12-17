//------------------------------------------------------------------------------
// main.cpp - содержит главную функцию,
// обеспечивающую простое тестирование
//------------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <thread>
#include <iostream>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std;

struct ThreadParams {
    int i;
};

int maxPiecesAm = 0;
int totalPiecesAm = 0;
mutex consoleMutex;
mutex cooksMutex;
mutex potsMutex;
condition_variable wakeCondition;
thread cooksThread;
bool gameFinished = false;

void *hannibalLive (ThreadParams *params);
void *cookAndSleep(void *params);
bool takeFromPot(int hannum);
bool takeFromPot(int hannum);

int main(int argc, char* argv[]) {
    int hannibalsAm = 0;
    int piecesAm = 0;
    cin >> hannibalsAm >> piecesAm;

    totalPiecesAm = piecesAm;
    maxPiecesAm = piecesAm;

    cooksThread = thread(cookAndSleep, nullptr);
    ThreadParams params[hannibalsAm];

    thread hanThreads[hannibalsAm];
    for (int i = 0; i < hannibalsAm; i++) {
        params[i].i = i;
        hanThreads[i] = thread(hannibalLive, (&params[i]));
    }

    this_thread::sleep_for(6000ms);
    gameFinished = true;
    for(int i = 0; i < hannibalsAm; i++) {
        hanThreads[i].join();
    }
    wakeCondition.notify_one();
    cooksThread.join();
    cout << "THE END";
    return 0;
}


void *hannibalLive (ThreadParams *params) {
    while(!gameFinished) {
        if (!takeFromPot(params->i)) {
            wakeCondition.notify_one();
        }
        this_thread::sleep_for(100ms);
    }
    return nullptr;
}

void *cookAndSleep(void *params) {
    while(!gameFinished) {
        unique_lock<mutex> lk(cooksMutex);

        wakeCondition.wait(lk);
        if (gameFinished) break;
        potsMutex.lock();

        consoleMutex.lock();
        cout << "chef woke up and cooked\n";
        consoleMutex.unlock();

        if (totalPiecesAm == 0) {
            totalPiecesAm = maxPiecesAm;
        }
        potsMutex.unlock();
    }
}

bool takeFromPot(int hannum) {
    bool successfullytaken = false;
    potsMutex.lock();
    if (totalPiecesAm != 0) {
        consoleMutex.lock();
        cout << hannum << " hannibal took a piece\n";
        consoleMutex.unlock();

        successfullytaken = true;
        totalPiecesAm--;
    }
    potsMutex.unlock();
    return successfullytaken;
}
