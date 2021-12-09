#include "parallel.h"
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
    int fd[2], n = vec.size(), procs = get_nprocs(), start, finish, argmin_i, argmin[procs], ans;
    double dist, minimal = numeric_limits<double>::max();
    vector<double> dists(int(n / procs), 0);
    auto my_euclid_dist = [&](const vector<double>& a) {return euclid_dist(a,v);};
    pipe(fd);
    for(int i = 0; i < procs; i++) 
    {
        if(fork() == 0)
        {
            start = i * int(n / procs);
            finish = (i + 1) * int(n / procs);
            transform(vec.begin() + start, vec.begin() + finish, dists.begin(), my_euclid_dist);
            argmin_i = start + min_element(dists.begin(), dists.end()) - dists.begin();
            write(fd[1], &argmin_i, sizeof(argmin_i));
            //printf("pid %d from ppid %d sent %d\n",getpid(),getppid(),argmin_i);
            _exit(i);
        }
    }
    int status;
    for(int i=0;i<4;i++)
    { 
        close(fd[1]);
        read(fd[0], &argmin[i], sizeof(argmin[i]));
        wait(&status);
        //printf("Parent received value: %d, ", argmin[i]);
        //printf("%d \n", WEXITSTATUS(status));
        dist = my_euclid_dist(vec[argmin[i]]);
        if (minimal > dist)
        {
            minimal = dist;
            ans = argmin[i];
        }
        //cout << ans << "\n";
    }
    return ans;
}