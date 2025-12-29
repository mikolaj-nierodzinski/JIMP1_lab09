#include <bits/stdc++.h>
#define MIN -100.0
#define MAX 100.0
using namespace std;

string toString(int num) {
    int n = num;
    int dg = (n == 0) ? 1 : 0;
    int neg = (n < 0);

    if (neg) n = -n;

    int tmp = n;
    while(tmp > 0) {
        tmp /= 10;
        dg++;
    }

    string ret;
    ret.assign(dg + neg, ' ');

    for(int i = dg + neg - 1; i >= neg; i--) {
        ret[i] = '0' + (n % 10);
        n /= 10;
    }

    if(neg)
        ret[0] = '-';

    ret += ".txt";
    return ret;
}

double rand_double(double a, double b) {
    return a + (b - a) * ((double)rand() / RAND_MAX);
}

int main() {
    srand(time(NULL));

    for(int i = 13; i <= 20; i++) {
        int sz = rand() % (100) + 1;

        string file = "./dane/A" + toString(i);
        cout << file << '\n';
        std::ofstream fa(file);
        
        fa << sz << ' ' << sz << '\n';
        for(int j = 1; j <= sz; j++) {
            for(int k = 1; k <= sz; k++ ){
                double x = rand_double(MIN, MAX);
                fa << x << ' ';
            }
            fa << '\n';
        }
        fa.close();
        
        file = "./dane/b" + toString(i);
        cout << file << '\n';
        std::ofstream fb(file);
        fb << sz << ' ' << "1\n";
        for(int j = 1; j <= sz; j++) {
            double x = rand_double(MIN, MAX);
                fb << x << '\n';
        }
        fb.close();
    }

}