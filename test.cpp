#include <iostream>
#include "polinom.h"



int main(){
    int n = 2;
    double *x = new double [n];
    double *y = new double [n];
    for(int i = 0;i < n;i++){
        std :: cin >> x[i];
        std :: cin >> y[i];
    }
    std :: cout << "\n" << spline(x,y,1.5,n);

    return 0;
}