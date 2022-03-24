#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static int cx1[8] = {1, 1, 2, 2, -1, -1, -2, -2};
static int cy1[8] = {2, -2, 1, -1, 2, -2, 1, -1};

bool safeInterval(int **a, int x, int y, int size){
    return ((x >= 0 && y >= 0) && (x < size && y < size)) && (a[x][y] < 0);
}

int validNeighbor(int **a, int x, int y, int size){
    int count = 0;
    for (int i = 0; i < 8; ++i)
        if (safeInterval(a, (x + cx1[i]), (y + cy1[i]), size))
            count++;
    return count;
}

bool nextMove(int **a, int *x, int *y, int size, unsigned long long &move)
{
    int min_deg_idx = -1;
    int c;
    int min_deg = 8;
    int x1, y1;

    int random = rand() % size;
    for (int count = 0; count < 8; ++count){
        int i = (random + count) % 8;
        x1 = *x + cx1[i];
        y1 = *y + cy1[i];
        move++;
        if ((safeInterval(a, x1, y1, size)) && (c = validNeighbor(a, x1, y1, size)) < min_deg){
            min_deg_idx = i;
            min_deg = c;
        }
    }
    if (min_deg_idx == -1)
        return false;
    x1 = *x + cx1[min_deg_idx];
    y1 = *y + cy1[min_deg_idx];
    a[x1][y1] = a[*x][*y] + 1;
    *x = x1;
    *y = y1;
    return true;
}

bool findTour(int **a, int ix, int iy, int size, unsigned long long &move){
    int sx = ix - 1;
    int sy = iy - 1;

    int x = sx, y = sy;
    a[x][y] = 1;
    for (int i = 0; i < size * size - 1; ++i){
        if (!nextMove(a, &x, &y, size, move))
            return false;
    }
    return true;
}

void WrFile1(string fileName, int x, int y, int m, unsigned long long move, double time, int **a){
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

void warnsdorffHeuristic(int x, int y, int size){
    clock_t start = clock();
    unsigned long long move = 0;
    int **a = new int *[size];
    for (int i = 0; i < size; i++)
        a[i] = new int[size];

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; j++)
            a[i][j] = -1;

    srand(time(NULL));
    while (!findTour(a, x, y, size, move)){
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; j++)
                a[i][j] = -1;
    }
    clock_t end = clock();
    double time = end - start;
    WrFile1("20127627_heuristic.txt", x, y, size, move, time, a);
    for (int i = 0; i < size; i++)
        delete[]a[i];
    delete[]a;
}
