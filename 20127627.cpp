#include "20127627_backtracking.cpp"
#include "20127627_warnsdorffHeuristic.cpp" 

using namespace std;

int main(int argc, char* argv[]){
    int x = stoi(argv[2]);
    int y = stoi(argv[4]);
    int m = stoi(argv[6]);
    warnsdorffHeuristic(x, y, m);
    backtracking(x, y, m);
    return 0;
}

