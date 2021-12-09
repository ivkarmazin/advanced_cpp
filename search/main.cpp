#if __has_include("serial.h")
#include "serial.h"
#endif
#if __has_include("parallel.h")
#include "parallel.h"
#endif
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

#define MULTIPLE 64*3*5  //960
#define TIMES 1000
#define MAX 1000

void fill_row(std::vector<double>& row)
{
    std::generate(row.begin(), row.end(), [](){ return rand() % MAX; }); 
}

void fill_matrix(std::vector<std::vector<double>>& mat)
{
    std::for_each(mat.begin(), mat.end(), fill_row);
}

int main()
{
    srand(time(0));
    int m = 100, n = MULTIPLE*TIMES, ans;
    vector<double> v(m, 0), v_close(m, 1);
    vector<vector<double>> vec(n, vector<double> (m));
    fill_matrix(vec);
    vec[5] = v_close;

    auto begin = chrono::steady_clock::now();
    for (int i = 0; i < 3; i++)
        ans = find_closest(vec,v);
    cout << "answer: " << ans << "\n";
    auto end = chrono::steady_clock::now();
    cout << "search time, avg. on 3 loops: " 
        << chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 3 << "ms \n";
}
