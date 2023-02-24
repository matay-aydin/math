// Stirling approximation
#include <iostream>
#include <cmath>
#include <iomanip>
#define PI 3.14159265359
#define E 2.71828182846
using namespace std;

long factorial(unsigned int);
double stirling_approx(unsigned int);
double abs_err(double, double);
double rel_err(double, double);

int main() {
    for(int i = 0; i < 20; i++) {
        long int f = factorial(i);
        double s = stirling_approx(i);
        cout << setprecision(2);
        cout << scientific;
        cout << setw(3) << i  
            << setw(20) << f 
            << setw(20) << s
            << setw(20) << abs_err(f, s)
            << setw(20) << rel_err(f, s) << endl;
    }
    return 0;
}

long factorial(unsigned int n) {
    long int res = 1;
    while(n > 0) {
        res *= n;
        n--;
    }
    return res;
}

double stirling_approx(unsigned int n) {
    double s;
    s = sqrt(2 * PI * n) * pow((n / E), n);
    return s;
}

double abs_err(double num, double calc) {
    return abs(num - calc);
}

double rel_err(double num, double calc) {
    return abs(num - calc) / abs(num);
}
