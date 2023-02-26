#include <iostream>
#include <cmath>

#define N 3 //размерность матрицы

void inversion(float ** A)
{
	double temp;
	double** E = new double* [N];

	for (int i = 0; i < N; i++)
		E[i] = new double[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			E[i][j] = 0.0;

			if (i == j)
				E[i][j] = 1.0;
		}

	for (int k = 0; k < N; k++)
	{
		temp = A[k][k];

		for (int j = 0; j < N; j++)
		{
			A[k][j] /= temp;
			E[k][j] /= temp;
		}

		for (int i = k + 1; i < N; i++)
		{
			temp = A[i][k];

			for (int j = 0; j < N; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}

	for (int k = N - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = A[i][k];

			for (int j = 0; j < N; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			A[i][j] = E[i][j];

	for (int i = 0; i < N; i++)
		delete[] E[i];

	delete[] E;
}
void Multy(float arr1[N][N], float arr2[N], float arr[N]) {

	float temp = 0;
	for (int i = 0; i < N; i++) {
		temp = 0;
		for (int j = 0; j < N; j++) {
			temp += arr1[i][j] * arr2[j];
		}
		arr[i] = temp;
	}

}
void Multy1(float **arr1, float arr2[N], float arr[N]) {

	float temp = 0;
	for (int i = 0; i < N; i++) {
		temp = 0;
		for (int j = 0; j < N; j++) {
			temp += arr1[i][j] * arr2[j];
		}
		arr[i] = temp;
	}

}
float lyambda(float arr1[N], float arr2[N]) {
	float lyambda = 0;
	float sum_mult = 0;
	float sum_pow = 0;
	for (int i = 0; i < N; i++) {
		sum_mult += arr1[i] * arr2[i];
	}
	for (int i = 0; i < N; i++) {
		sum_pow += pow(arr1[i], 2);
	}
	lyambda = sum_mult / sum_pow;
	return lyambda;
}
void assign(float arr1[N], float arr2[N]) {
	for (int i = 0; i < N; i++) {
		arr1[i] = arr2[i];
	}
}

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	float Vector1[N] = {0};
	float Vector2[N] = { 0 };
	float Matrix[N][N] = {0};
	float Vector_copy[N] = {0};
	float ** Matrix1 = new float* [N];
	for (int i = 0; i < N; i++)
		Matrix1[i] = new float[N];
	float Vector[N] = {0};
	float e = 0.01;
	float e_max = 0;
	float e_max2 = 0;
	float e_curr = 0;
	float e_curr2 = 0;
	float a = 0;


	for (int i = 0; i < N; i++) {
		cout << "¬ведите элементы " << i << " строки ";
		for (int j = 0; j < N; j++) {
			cin >> a;
			Matrix[i][j] = a;
			Matrix1[i][j] = a;

		}
	}

	cout << "¬ведите элементы вектора: ";
	for (int i = 0; i < N; i++) {
		cin >> Vector[i];
	}
	Multy(Matrix, Vector, Vector1);

	e_max = lyambda(Vector, Vector1);
	assign(Vector_copy, Vector);

	while ((abs(e_max - e_curr)) >= e){
		assign(Vector, Vector1);
		Multy(Matrix, Vector, Vector1);
		e_curr = e_max;
		e_max = lyambda(Vector, Vector1);
	}
	cout << "max = " << e_max << endl;

	inversion(Matrix1);
	Multy1(Matrix1, Vector_copy, Vector2);
	e_max2 = lyambda(Vector_copy, Vector2);

	while ((abs(e_max2 - e_curr2)) >= e) {
		assign(Vector_copy, Vector2);
		Multy1(Matrix1, Vector_copy, Vector2);
		e_curr2 = e_max2;
		e_max2 = lyambda(Vector_copy, Vector2);
	}
	cout << "min = " << e_max2;
}