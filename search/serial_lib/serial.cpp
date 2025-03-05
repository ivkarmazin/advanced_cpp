#include "serial.h"
using namespace std;

double myproduct(const double& x, const double& y)
{
    return (x - y) * (x - y);
}

double euclid_dist(const vector<double>& a, const vector<double>& b)
{
    return inner_product(a.begin(), a.end(), b.begin(), 0.0L, plus<double>(), myproduct);
}

int find_closest(const vector<vector<double>>& vec, const vector<double>& v)
{
    vector<double> dists_all(vec.size(), 0);
    auto my_euclid_dist = [&](const vector<double>& a) {return euclid_dist(a,v);};
    transform(vec.begin(), vec.end(), dists_all.begin(), my_euclid_dist);
    /*
    for(int i = 0; i < vec.size(); i++){
        for(int j = 0; j < vec[0].size(); j++)
            cout << vec[i][j] << " ";
        cout << "--> " << dists_all[i] << "\n";
    }
    */
    return min_element(dists_all.begin(), dists_all.end()) - dists_all.begin();
}