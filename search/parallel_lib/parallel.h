#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
using namespace std;

double myproduct(const double& x, const double& y);

double euclid_dist(const vector<double>& a, const vector<double>& b);

int find_closest(const vector<vector<double>>& vec, const vector<double>& v);