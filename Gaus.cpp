// Gaus.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

class matrix
{
private:
	int n;
	double **A;
	double *b;
	inline void ifend();
	void filling();
public:
	matrix() :n(0), A(NULL), b(NULL) {}
	matrix(int x) :n(x)
	{
		b = new double[n];
		A = new double *[n];
		for (int i(0); i < n; i++)
		{
			A[i] = new double[n];
		}
	}
	~matrix() { delete[] * A; delete[]b; }
	void constructor();
	void answer();
	void gauss();
	void show();
	void divider(int&);
	void mult(int&);
	void isNull();
};
inline void matrix::ifend() //Проверка на заполнение размера матрицы
{
	if (n == 0)
	{
		cout << "The size of matrix not found";
		system("pause");
		exit(0);
	}
}
void matrix::constructor() //Создание системы уравнений
{
	matrix::ifend();
	matrix::filling();
}
void matrix::filling() //Заполнение расширенного массива
{
	for (int i(0); i < n; i++)
	{
		for (int j(0); j < n; j++)
		{
			cout << "a" << i + 1 << j + 1 << " = ";
			cin >> A[i][j];
		}
		cout << "b" << i << " = ";
		cin >> b[i];
	}
}
void matrix::show()
{
	matrix::ifend();
	for (int i(0); i < n; i++)
	{
		for (int j(0); j < n; j++)
		{
			cout << A[i][j] << " * x" << j + 1;
			if (j == n - 1)
				cout << " = " << b[i];
			else
				cout << " + ";
		}
		cout << endl;
	}
}

static int step_counter = 0; //номер строки матрицы
void matrix::gauss()
{
	matrix::ifend();
	while (step_counter != n)
	{
		matrix::divider(step_counter); //делит строку step_counter на первый член данной строки;
		matrix::mult(step_counter);
		step_counter++;
		matrix::isNull();
		cout << endl << "Step #" << step_counter << " : " << "We're divide " << step_counter << " row to first koef and find a difference between " << step_counter << " row and other rows" << endl;
		matrix::show();
	}
	matrix::answer();
}

int main()
{
	matrix obj1(3);
	obj1.constructor();
	obj1.show();
	obj1.gauss();
	system("pause");
    return 0;
}

//methods for gauss

void matrix::divider(int &counter)
{
	double divider = A[counter][counter];
	b[counter] /= divider;
	for (int i(0); i < n; i++)
	{
		A[counter][i] /= divider;
	}
}
void matrix::mult(int& counter)
{
	for (int i(counter + 1); i < n; i++) //делаем единичным 1ый элемент строки counter и вычетаем его из последующих строк, умноженную на 1 к/ф той строки
	{
		double mult = A[i][counter];
		for (int j(counter); j < n; j++)
		{
			A[i][j] -= A[counter][j] * mult;
		}
		b[i] -= b[counter] * mult;
	}

	for (int i(0); i < counter; i++)
	{
		double factor = A[i][counter];
		for (int j(counter); j < n; j++)
		{
			A[i][j] -= A[counter][j] * factor;
		}
		b[i] -= b[counter] * factor;
	}
}
void matrix::answer()
{
	cout << endl << "X = ( ";
	for (int i(0); i < n; i++)
	{
		cout << b[i];
		if (i != n - 1) cout << ", ";
	}
	cout << " );" << endl;
}
void matrix::isNull() //Не спраашивайте зачем эта функция, главное работает
{
	for (int i(0); i < n; i++)
	{
		for (int j(0); j < n; j++)
		{
			A[i][j] = (A[i][j] == 0 ? 0 : A[i][j]);
		}
	}
}