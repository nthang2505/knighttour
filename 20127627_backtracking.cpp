#include <iostream>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

static int cx[8] = {1, 2, -1, 1, -2, 2, -2, -1};
static int cy[8] = {2, 1, 2, -2, 1, -1, -1, -2};

void WrFile(string fileName, int x, int y, int m, unsigned long long move, double time, int **a){
    fstream file;
    file.open(fileName, ios::out);
    file << x << " " << y << " " << m << endl;
    file << move << endl;
    file << time << endl;
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < m; ++j)
            file << a[i][j] << " ";
        file << endl;
    }
    file.close();
}

bool safeInterval(int x, int y, int **a, int size){
    return ( x >= 0 && x < size && y >= 0 && y < size && a[x][y] == -1);
}

bool findTour(int x, int y, int step, int **a, int size, unsigned long long &move, clock_t &start){
    if (step == size*size + 1)
        return true;
    clock_t check = clock();
    double checktime = check - start;
    if (checktime >= 5*1000)
        return true;
    
    int nextStepx, nextStepy;
    for (int i = 0; i < 8; i++){
        nextStepx = x + cx[i];
        nextStepy = y + cy[i];

        if (safeInterval(nextStepx, nextStepy, a, size)){
            move++;
            a[nextStepx][nextStepy] = step;

            if (findTour(nextStepx, nextStepy, step + 1, a, size, move, start))
                return true;
            else
                a[nextStepx][nextStepy] = -1;
        }
    }
    return false;
}

void backtracking(int x, int y, int size){
    unsigned long long move = 0;
    int **a = new int *[size];
    for (int i = 0; i < size; i++)
        a[i] = new int[size];

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; j++)
            a[i][j] = -1;

    a[x-1][y-1]  = 1;

    clock_t start = clock();
    findTour(x-1, y-1, 2, a, size, move, start);
    clock_t end = clock();
    double time = end - start;
    WrFile("20127627_backtrack.txt", x, y, size, move, time, a);
    for (int i = 0; i < size; i++)
        delete[]a[i];
    delete[]a;
}