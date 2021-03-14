#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main()
{
	float a, b, c; // ������������ ����������� ���������
	char Sa[64], Sb[64], Sc[64]; // ������������ ����������� ���������
	bool zero = true; // ���������� ��� ������������ ���� (�.�. ������� atof() �� ����� ������������ 0 ��� �����)
	ifstream file("input.txt"); // �������� ����� ��� ������
	ofstream ofile("output.txt"); // �������� ����� ��� ������
	while (!file.eof()) // ���� �� ����� �����
	{
		try
		{
			file >> Sa >> Sb >> Sc;
			// ���� �������� �� ������� ����
			if (Sa[0] == '0')
			{
				a = 0;
				zero = false;
			}
			if (Sb[0] == '0')
			{
				b = 0;
				zero = false;
			}
			if (Sc[0] == '0')
			{
				c = 0;
				zero = false;
			}//-----------------------------------------	

			// ���� �������� ������������ ����� ������
			if ((!atof(Sa) || !atof(Sb) || !atof(Sc)) && zero)
			{
					throw 3; // �������� ��� ������ 3
			}
			else
			{
					a = atof(Sa);
					b = atof(Sb);
					c = atof(Sc);
			}//--------------------------------------------

			// �������� �� ����� �� ������� ������������� ��������
			if (a > (pow(2, sizeof(float) * 8.0 - 1) - 1) || b > (pow(2, sizeof(float) * 8.0 - 1) - 1) || c > (pow(2, sizeof(float) * 8.0 - 1) - 1))
			{
				throw 5;
			}

			// �������� �� ����� �� ������� ������������ ��������
			if (a < -1*(pow(2, sizeof(float) * 8.0 - 1)) || b < -1*(pow(2, sizeof(float) * 8.0 - 1)) || c < -1*(pow(2, sizeof(float) * 8.0 - 1)))
			{
				throw 7;
			}
		}
		catch(int i) // ��������� ���� ������
		{
			if (i == 3)
			{
				ofile << "Error: " << i << " - Entered letter" <<endl;
			}
			else if (i == 5)
			{
				ofile << "Error: " << i << " - Too many numbers entered" << endl;
			}
			else if (i == 7)
			{
				ofile << "Error: " << i << " - The number entered is too small" << endl; 
			}
			continue;
		}//-----------------------------------------------------------

		// ���� ������� ����������� ���������
		if (a == 0)
		{
			if (b == 0)
			{
				if (c == 0)
				{
					ofile << "x - any"<< endl;
					continue;
				}
				else
				{
					ofile << "No solution" << endl;
					continue;
				}
			}
			else
			{
				float x = (-c) / b;
				ofile << "x = " << x << endl;
				continue;
			}
		}
		else
		{
			float D = pow(b, 2) - 4 * a * c;
			if (D < 0)
			{
				ofile << "No real roots" << endl;
				continue;
			}
			else
			{
				if (D == 0)
				{
					float x = (-b) / (2 * a);
					ofile << "x1 = x2 = " << x << endl;
					continue;
				}
				else
				{
					double x1 = (-b + sqrt(D)) / (2 * a);
					double x2 = (-b - sqrt(D)) / (2 * a);
					ofile << "x1 = " << x1 << ' ' << "x2 = " << x2 << endl;
					continue;
				}
			}
		}
	}
	file.close(); // �������� ����� ��� ��� ������
	ofile.close(); // �������� ����� ��� ��� ������
	return 0;
}