#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx; // �������� �������� ��� ������������� �������

void left_rect(float* &mas_x, float* &mas_y, int &N, int &T, ofstream &ofile)
{
	auto start_t = chrono::high_resolution_clock::now(); // ����� ������ ������
	float sum = 0;
	float delta = (mas_x[N - 1] - mas_x[0]) / T;
	for (int i = 0; i < N - 1; i++)
	{
		float k = (mas_y[i + 1] - mas_y[i]) / (mas_x[i + 1] - mas_x[i]); // ����������� �������
		
		for (float x = mas_x[i]; x < mas_x[i + 1]; x += delta)
		{
			float b = mas_y[i] - k*mas_x[i]; // ����������� b
			float y = k * x + b; // ��������� ������
			sum += delta * fabs(y);
		}
	}
	
	mtx.lock();
	ofile << "Integral (Left rectangle) = " << sum;
	auto end_t = chrono::high_resolution_clock::now(); // ����� ����� ������
	chrono::duration<float> duration = end_t - start_t; // ������� ����� ������ � �������
	ofile << " Time: " << duration.count() << " Second" << endl;
	mtx.unlock();
}

void right_rect(float*& mas_x, float*& mas_y, int& N, int& T, ofstream& ofile)
{
	auto start_t = chrono::high_resolution_clock::now(); // ����� ������ ������
	float sum = 0;
	float delta = (mas_x[N - 1] - mas_x[0]) / T;
	for (int i = 0; i < N - 1; i++)
	{
		float k = (mas_y[i + 1] - mas_y[i]) / (mas_x[i + 1] - mas_x[i]); // ����������� �������
		for (float x = mas_x[i] + delta; x < mas_x[i + 1]; x += delta)
		{
			float b = mas_y[i] - k * mas_x[i]; // ����������� b
			float y = k * x + b; // ��������� ������
			sum += delta * fabs(y);
		}
	}

	mtx.lock();
	ofile << "Integral (Right rectangle) = " << sum;
	auto end_t = chrono::high_resolution_clock::now(); // ����� ����� ������
	chrono::duration<float> duration = end_t - start_t; // ������� ����� ������ � �������
	ofile << " Time: " << duration.count() << " Second" << endl;
	mtx.unlock();
}

void trapez(float*& mas_x, float*& mas_y, int& N, int& T, ofstream& ofile)
{
	auto start_t = chrono::high_resolution_clock::now(); // ����� ������ ������
	float sum = 0;
	float delta = (mas_x[N - 1] - mas_x[0]) / T;
	for (int i = 0; i < N - 1; i++)
	{
		float k = (mas_y[i + 1] - mas_y[i]) / (mas_x[i + 1] - mas_x[i]); // ����������� �������
		for (float x = mas_x[i], x1 = (mas_x[i] + delta); x < mas_x[i + 1]; x += delta, x1 += delta)
		{
			float b = mas_y[i] - k * mas_x[i]; // ����������� b
			float b1 = mas_y[i + 1] - k * mas_x[i + 1]; // ����������� b ��� ������ �����
			float y = k * x + b;// ��������� ������
			float y1 = k * x1 + b1;// ��������� ������ ��� ������ �����
			sum += delta * (fabs(y) * 0.5 + fabs(y1) * 0.5);
		}
	}

	mtx.lock();
	ofile << "Integral (Trapez) = " << sum;
	auto end_t = chrono::high_resolution_clock::now(); // ����� ����� ������
	chrono::duration<float> duration = end_t - start_t; // ������� ����� ������ � �������
	ofile << " Time: " << duration.count() << " Second" << endl;
	mtx.unlock();
}

int main()
{
	char Sx[64], Sy[64]; // ���������� ��� �������� �� �����
	int N = 0; // ���������� ���������������
	bool zero = true; // ���������� ��� ������������ ���� (�.�. ������� atof() �� ����� ������������ 0 ��� �����)
	ifstream file("input.txt"); // �������� ����� ��� ������
	ofstream ofile("output.txt"); // �������� ����� ��� ������

	while (!file.eof()) // ������� ���������� ���������������
	{
		file >> Sx >> Sy;
		N++;
	}//-------------------------------------------------------

	int T = 500; // ��������
	float* mas_x = new float [N]; // ������ ��������� �
	float* mas_y = new float [N]; // ������ ��������� �

	file.clear(); // ������� ������ �����
	file.seekg(0, ios_base::beg); // ����������� ������� � ����� �����

	int i = 0;
	while (!file.eof())
	{
		float x, y;
		try
		{
			file >> Sx >> Sy;
			// ���� �������� �� ������� ����
			if (Sx[0] == '0')
			{
				x = 0;
				zero = false;
			}
			if (Sy[0] == '0')
			{
				y = 0;
				zero = false;
			}//-----------------------------	

			// ���� �������� ������������ ����� ������
			if ((!atof(Sx) || !atof(Sy)) && zero)
			{
				throw 3; // �������� ��� ������ 3
			}
			else
			{
				x = atof(Sx);			
				y = atof(Sy);
			}//---------------------------------------

			// �������� �� ����� �� ������� ������������� ��������
			if (x > (pow(2, sizeof(float) * 8.0 - 1) - 1) || y > (pow(2, sizeof(float) * 8.0 - 1) - 1))
			{
				throw 5;
			}

			// �������� �� ����� �� ������� ������������ ��������
			if (x < -1 * (pow(2, sizeof(float) * 8.0 - 1)) || y < -1 * (pow(2, sizeof(float) * 8.0 - 1)))
			{
				throw 7;
			}
		}
		catch (int j) // ��������� ���� ������
		{
			if (j == 3)
			{
				ofile << "Error: " << j << " - Entered letter" << endl;
				return 0;
			}
			else if (j == 5)
			{
				ofile << "Error: " << j << " - Too many numbers entered" << endl;
				return 0;
			}
			else if (j == 7)
			{
				ofile << "Error: " << j << " - The number entered is too small" << endl;
				return 0;
			}
		}//------------------------------------
		mas_x[i] = x;
		mas_y[i] = y;
		i++;
	}

	int sort = 2;
	while (sort) // ����������
	{
		int k = 0;
		for (int i = 0; i < N - 1; i++) 
		{
			if (mas_x[i] > mas_x[i + 1]) // ���������� i-�� ������� �� ���������, � ���� i-�� ������, �� ��������� ������
			{
				float *a = new float[1];
				a[0] = mas_x[i + 1];
				mas_x[i + 1] = mas_x[i];
				mas_x[i] = a[0];

				a[0] = mas_y[i + 1];
				mas_y[i + 1] = mas_y[i];
				mas_y[i] = a[0];
				delete[] a;
			}
			else if (mas_x[i] == mas_x[i+1])
			{
				ofile << "Error: two identical points";
				return 0;
			}
			else
			{
				k++;
			}
		}
		if (k == N - 1) // ���� �������� �� �������� ��� ����, �� ����� �������, ��� ������ ������������
		{
			sort--;
		}
	}

	thread Left(left_rect, ref(mas_x), ref(mas_y), ref(N), ref(T), ref(ofile));		// �������� �������
	thread Right(right_rect, ref(mas_x), ref(mas_y), ref(N), ref(T), ref(ofile));
	thread Trapez(trapez, ref(mas_x), ref(mas_y), ref(N), ref(T), ref(ofile));

	Left.join();	// �������� ���������� �������� � �������
	Right.join();
	Trapez.join();
	delete[] mas_x; // ������������ ���������� ������
	delete[] mas_y;
	file.close();	// �������� ������
	ofile.close();
	system("pause");
	return 0;
}