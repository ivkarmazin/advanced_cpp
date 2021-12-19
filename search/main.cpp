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

#define MULTIPLE 64 * 3 * 5  //960
#define TIMES 1000
#define MAX 1000
#define SIZE 100
#define LOOPS 3
#define ANS 12345

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
    int m = SIZE, n = MULTIPLE * TIMES, ans;
    vector<double> v(m, 0), v_close(m, MAX / 10);
    vector<vector<double>> vec(n, vector<double> (m)); // data base
    fill_matrix(vec);
    vec[ANS] = v_close;

    auto begin = chrono::steady_clock::now();
    for (int i = 0; i < LOOPS; i++)
        ans = find_closest(vec,v);
    cout << "answer: " << ans << "th vector\n";
    auto end = chrono::steady_clock::now();
    cout << "search time, avg. on " << LOOPS << " loops: " << 
        chrono::duration_cast<chrono::milliseconds>(end - begin).count() / LOOPS << "ms\n";
}
