
#include <pthread.h>
#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string salesFiles[] = {"/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales1.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales2.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales3.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales4.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales5.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales6.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales7.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales8.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales9.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales10.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales11.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales12.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales13.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales14.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales15.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales16.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales17.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales18.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales19.txt",
                       "/Users/AnaRatkovic/CLionProjects/StapleMax/cmake-build-debug/sales20.txt"
                        };
// Inventory
int numPens     = 100;
int numPaper    = 200;
int numToner    = 40;
int numLaptops  = 15;

const int NUM_THREADS = 20;

pthread_mutex_t mutexLock;

// Multithreaded method
void* sales (void* threadArg){

    ifstream* file = (ifstream*) threadArg;
    string line;
    long countLines;

    while (*file >> line) {
        countLines++;
        if (line == "pen"){
            pthread_mutex_lock(&mutexLock);
            if (numPens > 0) {
                numPens--;
                pthread_mutex_unlock(&mutexLock);
            } else {
                numPens = 100;
                numPens--;
                pthread_mutex_unlock(&mutexLock);
            }
        }
        if (line == "paper") {
            pthread_mutex_lock(&mutexLock);
            if (numPaper > 0) {
                numPaper--;
                pthread_mutex_unlock(&mutexLock);
            } else {
                numPaper = 200;
                numPaper--;
                pthread_mutex_unlock(&mutexLock);

            }
        }
        if (line == "toner") {
            pthread_mutex_lock(&mutexLock);
            if (numToner > 0){
                numToner--;
                pthread_mutex_unlock(&mutexLock);
            } else {
                numToner = 40;
                numToner--;
                pthread_mutex_unlock(&mutexLock);
            }
        }
        if (line == "laptop") {
            pthread_mutex_lock(&mutexLock);
            if (numLaptops > 0){
                numLaptops--;
                pthread_mutex_unlock(&mutexLock);
            } else {
                numLaptops = 15;
                numLaptops--;
                pthread_mutex_unlock(&mutexLock);

            }
        }

    }
    delete file;
    return (void*)countLines;

}

int main() {

    // Array of threads
    pthread_t threadIds[NUM_THREADS];
    pthread_mutex_init(&mutexLock, NULL);
    int error = -1;

    void* value;
    long sum;

    for (int i = 0; i < 20; i++) {
        ifstream* inFile = new ifstream;
        inFile->open(salesFiles[i]);
        error = pthread_create(&threadIds[i], NULL, sales, (void *) inFile);
        if (error != 0) {
            cout << "FATAL ERROR creating thread " << i + 1 << ": " << strerror(error) << endl;
            exit(1);
        }
    }
    for (int i = 0; i< 20; i++) {
        error = pthread_join(threadIds[i], &value);
        sum += (long)value;
        if (error != 0) {
            cout << "WARNING - failed to join thread " << i + 1 << ": " << strerror(error) << endl;

        }
    }

    pthread_mutex_destroy(&mutexLock);

    cout << "Pen count = "      << numPens      << endl;
    cout << "Paper count = "    << numPaper     << endl;
    cout << "Toner count = "    << numToner     << endl;
    cout << "Laptop count = "   << numLaptops   << endl;

    cout << "Total sold: " << sum << endl;

    return 0;
}

