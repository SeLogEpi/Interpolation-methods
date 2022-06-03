#include <iostream>
#include <fstream>
#include <cmath>
#include "Gnup.h"
#include "polinom.h"


using namespace std;


int main(){
    std :: ifstream F("input.txt");
    int size;
    F >> size;
    double *x = new double [size];
    double *y = new double [size];

    for(int i = 0;i < size;i++){
        F >> x[i];
        F >> y[i];
    }
    double x1,x2,x3;
    F >> x1; F >> x2; F >> x3;
    F.close();
    double Tochka[3] = {x1,x2,x3};
    cout<< "Lagrange interpolation polynomial" <<endl;
    cout << "Ln(" << x1 << ")= " << lagrange(x,y,x1,size) << " " << endl;
    cout << "Ln(" << x2 << ")= "<< lagrange(x,y,x2,size) << " " << endl;
    cout << "Ln(" << x3 << ")= "<< lagrange(x,y,x3,size) << " " << endl;

    cout<< "Newton's interpolation polynomial" <<endl;
    cout << "f(" << x1 << ")= "<< Newton(x,y,x1,size) <<endl;
    cout << "f(" << x2 << ")= "<< Newton(x,y,x2,size) <<endl;
    cout << "f(" << x3 << ")= "<< Newton(x,y,x3,size) <<endl;


    cout<< "Canonical polynomial" <<endl;
    cout << "P(" << x1 << ")= "<< canonical(x,y,x1,size) <<endl;
    cout << "P(" << x2 << ")= "<< canonical(x,y,x2,size) <<endl;
    cout << "P(" << x3 << ")= "<< canonical(x,y,x3,size) <<endl;

    cout<< "spline interpolation" <<endl;
    cout << "f(" << x1 << ")= "<< spline(x,y,x1,size) <<endl;
    cout << "f(" << x2 << ")= "<< spline(x,y,x2,size) <<endl;
    cout << "f(" << x3 << ")= "<< spline(x,y,x3,size) <<endl;

    double Ln[3] = {lagrange(x,y,x1,size),lagrange(x,y,x2,size),lagrange(x,y,x3,size)};
    double f[3] = {Newton(x,y,x1,size),Newton(x,y,x2,size),Newton(x,y,x3,size)};
    double P[3] = {canonical(x,y,x1,size),canonical(x,y,x2,size),canonical(x,y,x3,size)};
    double Y[3] = {spline(x,y,x1,size),spline(x,y,x2,size),spline(x,y,x3,size)};
    GnuP p;
    p.plotArrayPar(6,x,y,3,5,3,"points");
    p.plotArrayPar(3,Tochka,Ln,3,5,12,"Lagrange interpolation polynomial");
    p.plotArrayPar(3,Tochka,f,3,5,1,"Newton's interpolation polynomial");
    p.plotArrayPar(3,Tochka,P,3,5,7,"Canonical polynomial");
    p.plotArrayPar(3,Tochka, Y,3,5,10,"spline interpolation");
    p.plot();
 


    return 0;
}
