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

void fill_row(std::vector<double>& row)
{
    std::generate(row.begin(), row.end(), [](){ return rand() % 1000; }); 
}

void fill_matrix(std::vector<std::vector<double>>& mat)
{
    std::for_each(mat.begin(), mat.end(), fill_row);
}

int main()
{
    srand(time(0));
    int m = 100, n = 960*1000, ans;
    vector<double> v(m, 0), v_close(m, 1);
    vector<vector<double>> vec(n, vector<double> (m));
    fill_matrix(vec);
    vec[5] = v_close;

    auto begin = chrono::steady_clock::now();
    for (int i = 0; i < 5; i++)
        ans = find_closest(vec,v);
    cout << "answer: " << ans << "\n";
    auto end = chrono::steady_clock::now();
    cout << "search time, avg. on 5 loops: " 
        << chrono::duration_cast<chrono::milliseconds>(end - begin).count() / 5 << "ms \n";
}
