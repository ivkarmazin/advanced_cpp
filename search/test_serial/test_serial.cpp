#include "serial.h"
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
using namespace std;

#define MULTIPLE 64 * 3 * 5 //960
#define TIMES 1000
#define MAX 1000
#define SIZE 100

void fill_row(std::vector<double>& row)
{
    std::generate(row.begin(), row.end(), [](){ return rand() % MAX; }); 
}

void fill_matrix(std::vector<std::vector<double>>& mat)
{
    std::for_each(mat.begin(), mat.end(), fill_row);
}

TEST(SerialSearch, Test1) 
{
    srand(time(0));
    int m = SIZE, n = MULTIPLE * TIMES;
    vector<double>  v(m, 0), v_close1(m, 3 * MAX /10), 
                    v_close2(m, 2 * MAX /10), v_close3(m, MAX /10);
    vector<vector<double>> vec(n, vector<double> (m));
    fill_matrix(vec);
    vec[10] = v_close1;
    EXPECT_EQ(find_closest(vec,v) , 10);
    vec[11] = v_close2;
    EXPECT_EQ(find_closest(vec,v) , 11);
    vec[12] = v_close3;
    EXPECT_EQ(find_closest(vec,v) , 12);
}