#include <iostream>
#include <cmath>
#include "Gnup.h"
#include <locale>
using namespace std;

const int n=6;

double lagranz(double X[n], double Y[n], double x)
{
        double z,p1,p2;
        z=0;
        for (int j=0; j<n; j++){
                p1=1; p2=1;
                for (int i=0; i<n; i++){
                        if (i==j){
                            p1=p1*1;p2=p2*1;
                        }
                        else {
                                p1=p1*(x-X[i]);
                                p2=p2*(X[j]-X[i]);
                    }
                }
                z=z+Y[j]*p1/p2;
        }
        return z;
}

double Newton(double X[n], double Y[n], double x){

    double sum = Y[0];
    for(int i = 1; i < n; i++)
    {
        double F = 0;
        for(int j = 0; j <= i; j++)
            {
            double den = 1;
            for(int k = 0; k <= i; k++)
                if (k != j)
                    den *= (X[j] - X[k]);
            F += Y[j]/den;
            }
        for(int k = 0; k < i; k++)
            F *= (x - X[k]);
        sum += F;
    }
    return sum;
}

double gauss(double** a, double* y, double* x)
{
    double max;
    int k, index;
    const double eps = 0.00001;  
    k = 0;
    while (k < n)
    {
        
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        
        if (max < eps)
        {
            
            cout << " ";
            cout << index << " " << endl;
            return 0;
        }
        for (int j = 0; j < n; j++)
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;
        
        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            if (abs(temp) < eps) continue; 
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k)  continue; 
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }
    
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
    return 1;

}

double kanon(double x[n], double y[n], double t)
{
    double sum =0;
    double** X = new double*[n];
    for(int i=0; i <n; i++)
    {
        X[i] = new double[n];
    }
    for(int i = 0; i<n; i++)
    {
        for(int j=0;j<n;j++)
        {
            X[i][j] = pow(x[i],j);

        }
    }
    double* Y = new double [n];
    for(int i=0;i<n;i++)
    {
        Y[i]=y[i];
    }
    double* c = new double[n];
    gauss(X,Y,c);
    for(int i=0; i <n; i++)
    {
        sum+=c[i]*pow(t,i);
    }
    delete X,c;
    return sum;
}

double linear(double X[n], double Y[n],double x)
{
	double y = 0;

	for ( int i = 1; i < n; i++)
		if (x < X[i]) {
			y = Y[i - 1] + (Y[i] - Y[i - 1]) * ((x - X[i - 1]) / (X[i] - X[i - 1]));
			break;
		}

	return y;
}


int main()
{
    setlocale(LC_ALL,"RUS");
    double x1=0.102, x2=0.203,x3=0.154;

    double x[n] = {0.02, 0.08, 0.12, 0.17, 0.23, 0.30};
    double Tochka[6] = {x1,x2,x3};
    double y[n] = {1.02316, 1.09509, 1.14725, 1.21423, 1.30120, 1.40907};

    cout<< "Lagrange interpolation polynomial" <<endl;
    cout << "Ln(x1)=" << lagranz(x,y,x1) << " " << endl;
    cout << "Ln(x2)=" << lagranz(x,y,x2) << " " << endl;
    cout << "Ln(x3)=" << lagranz(x,y,x3) << " " << endl;

    cout<< "Newton's interpolation polynomial" <<endl;
    cout << "f(x1)= "<< Newton(x,y,x1) <<endl;
    cout << "f(x2)= "<< Newton(x,y,x2) <<endl;
    cout << "f(x3)= "<< Newton(x,y,x3) <<endl;


    cout<< "Canonical polynomial" <<endl;
    cout << "P(x1)= "<< kanon(x,y,x1) <<endl;
    cout << "P(x2)= "<< kanon(x,y,x2) <<endl;
    cout << "P(x3)= "<< kanon(x,y,x3) <<endl;

    cout<< "Linear interpolation" <<endl;
    cout << "f(x1)= "<< linear(x,y,x1) <<endl;
    cout << "f(x2)= "<< linear(x,y,x2) <<endl;
    cout << "f(x3)= "<< linear(x,y,x3) <<endl;

    double Ln[3] = {lagranz(x,y,x1),lagranz(x,y,x2),lagranz(x,y,x3)};
    double f[3] = {Newton(x,y,x1),Newton(x,y,x2),Newton(x,y,x3)};
    double P[3] = {kanon(x,y,x1),kanon(x,y,x2),kanon(x,y,x3)};
    double Y[3] = {linear(x,y,x1),linear(x,y,x2),linear(x,y,x3)};
    GnuP p;
    p.plotArrayPar(6,x,y,3,5,3,"points");
    p.plotArrayPar(3,Tochka,Ln,3,5,12,"Lagrange interpolation polynomial");
    p.plotArrayPar(3,Tochka,f,3,5,1,"Newton's interpolation polynomial");
    p.plotArrayPar(3,Tochka,P,3,5,7,"Canonical polynomial");
    p.plotArrayPar(3,Tochka, Y,3,5,10,"Linear interpolation");
    p.plot();
 


    return 0;
}