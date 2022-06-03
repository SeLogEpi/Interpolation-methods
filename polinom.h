#ifndef POLINOM_H
#define POLINOM_H

#include <cmath>
#include <omp.h>
#include <exception>


int Check(double **m,int N) {
	for (int k = 0; k < N; k++) {
		
		int i_max = k;
		double v_max = m[i_max][k];

		for (int i = k + 1; i < N; i++) {
			if (fabs(m[i][k]) > v_max) {
				v_max = m[i][k];
				i_max = i;
			}
		}
			if (!m[i_max][k]) {
				return k;
			}
			if (i_max != k && m[k][k] == 0) {
				#pragma omp parallel for
				for(int i = 0;i < N;i++){
					double temp = m[i_max][i];
					m[i_max][i] = m[k][i];
					m[k][i] = temp;
				}
			}
		#pragma omp parallel for
			for (int i = k + 1; i < N; i++) {
				double d = m[i][k] / m[k][k];
				if (d != 0) {
					for (int j = k; j <= N; j++) {
						m[i][j] -= d * m[k][j];
					}
				}
			}
	}

	return -1;
}

double* Solutions(double **M,int N) {
	double *X = new double [N]; 
	for (int i = N - 1; i >= 0; i--) {
		X[i] = M[i][N];
		for (int j = i + 1; j < N; j++) {
			X[i] -= M[i][j] * X[j];
		}
		X[i] /=  M[i][i];
	}
	return X;
}

double* Gauss(double **M,int size) {
	int flag = Check(M,size);

	if (flag != -1) {
		throw std :: invalid_argument("Matrix can't be solved");
	}
	double *fx = Solutions(M,size); 
	return fx;
	

}


double lagrange(double *X, double *Y, double point,int size){
    double value = 0;
    for(int i = 0; i < size;i++){
        double p = 1;
        for(int j = 0;j < size;j++){
            if(i != j){
                p*=(point - X[j])/(X[i] - X[j]);
            }
        }
        value += Y[i]*p;
    }
    return value;
}

double canonical(double *X, double *Y,double point, int size){
    double value = 0;
	
	double **matrix = new double *[size];
	for(int i = 0;i < size;i++){
		matrix[i] = new double [size+1];
	}

	for(int i = 0;i < size;i++){
		for(int j = 0;j < size;j++){
			matrix[i][j] = pow(X[i],size - j - 1);
		}
		matrix[i][size] = Y[i];
	}

	double *fx;
	fx = Gauss(matrix,size);
	for(int i = 0; i < size; i++){
		value += fx[i]*pow(point,size - i - 1);
	}
	
	for(int i = 0;i < size;i++)
		delete [] matrix[i];
	delete [] matrix;
	delete [] fx;

	return value;
}


double Newton(double *X,double *Y,double point, int size){
	double value = Y[0];
	for(int i = 1;i < size; i++){
		double F = 0;
		for(int j = 0;j <= i;j++){
			double denominator = 1;
			for(int k = 0;k <= i;k++){
				if(k != j)
					denominator*= (X[j] - X[k]);
			} 
			F += Y[j]/denominator;
		}
		for(int m = 0;m < i;m++)
			F*= (point  - X[m]);
		value += F;
	}

	return value;
}
void CubicSpline(int n, double *h, double **a, double *y){
    int i;
    for(i=0;i<n-1;i++){
        a[i][i]=2*(h[i]+h[i+1]);
    }
    for(i=0;i<n-2;i++){
        a[i][i+1]=h[i+1];
        a[i+1][i]=h[i+1];
    }
    for(i=1;i<n;i++){
        a[i-1][n-1]=(y[i+1]-y[i])*6/(double)h[i]-(y[i]-y[i-1])*6/(double)h[i-1];
    }
} 
void coef(int n, double *h, double *sig, double *y, double *a, double *b, double *c, double *d){
    int i;
    for(i=0;i<n;i++){
        d[i]=y[i];
        b[i]=sig[i]/2.0;
        a[i]=(sig[i+1]-sig[i])/(h[i]*6.0);
        c[i]=(y[i+1]-y[i])/h[i]-h[i]*(2*sig[i]+sig[i+1])/6.0;
    }
}

double spline(double *X,double *Y,double point, int size){
	int n = size - 1;
	double *h = new double [n];
	for(int i = 0;i < n;i++){
		h[i] = X[i+1] - X[i];
	}	
	double *a = new double [n];
	double *b = new double [n];
	double *c = new double [n];
	double *d = new double [n];
	double  *sig = new double [n+1]; sig[0] = 0; sig[n] = 0;
	double **matrix = new double *[n-1];
	for(int i = 0;i < n - 1;i++){
		matrix[i] = new double [n];
	}
	CubicSpline(n,h,matrix,Y);
	double *temp = Gauss(matrix, n - 1);
	for(int i = 0;i < n; i++){
		sig[i] = temp[i - 1];
	}
	coef(n,h,sig,Y,a,b,c,d);
	double value = 0;
	for(int i = 0; i < size; i++){
		if(point > X[i] && point < X[i+1]){
			value += a[i]* pow((point - X[i]),3) + b[i]*pow((point - X[i]),2) + c[i]*(point - X[i]) + d[i];
		}
	}

	for(int i =0; i < n - 1;i++){
		delete [] matrix[i];
	}
	delete [] matrix;
	delete [] a;
	delete [] b;
	delete [] temp;
	delete [] sig;
	delete [] c;
	delete [] d;

	return value;

}




#endif