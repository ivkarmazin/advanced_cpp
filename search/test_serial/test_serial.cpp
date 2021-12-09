#include "serial.h"
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"

using namespace std;

void fill_row(std::vector<double>& row)
{
    std::generate(row.begin(), row.end(), [](){ return rand() % 1000; }); 
}

void fill_matrix(std::vector<std::vector<double>>& mat)
{
    std::for_each(mat.begin(), mat.end(), fill_row);
}

TEST(SerialSearch, Test1) 
{
    srand(time(0));
    int m = 10, n = 960*1000;
    vector<double> v(m, 0), v_close1(m, 3), v_close2(m, 2), v_close3(m, 1);
    vector<vector<double>> vec(n, vector<double> (m));
    fill_matrix(vec);
    vec[10] = v_close1;
    EXPECT_EQ(find_closest(vec,v) , 10);
    vec[11] = v_close2;
    EXPECT_EQ(find_closest(vec,v) , 11);
    vec[12] = v_close3;
    EXPECT_EQ(find_closest(vec,v) , 12);
}