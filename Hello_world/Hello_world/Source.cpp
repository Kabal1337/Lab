#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int main()
{
	setlocale(LC_ALL, "RUS");
	string num1;
	string num2;
	string num3;
	cout << "������� ��� �����:\n";
	cin >> num1;
	cin >> num2;
	cin >> num3;
	if (num1 >= num2) {
		if (num2 >= num3) {
			cout << "����� � ������� ����������� = " << num3 << num2 << num1;
			return 0;
		}
			if (num2 <= num3)
			if (num1 < num3) {
				cout << "����� � ������� ����������� = " << num1 << num2 << num3;
				return 0;
			}
			if (num1>=num3)
				cout << "����� � ������� ����������� = " << num2 << num3 << num1;
	
			return 0;
	}
	if (num1 <= num2) {
		if (num1 >= num3)
			cout << "����� � ������� ����������� = " << num3 << num1 << num2;
		if (num1 <= num3)
			if (num2 > num3) {
				cout << "����� � ������� ����������� = " << num1 << num3 << num2;
				return 0;
			}
			if (num2<=num3)
				cout << "����� � ������� ����������� = " << num1<<num2<<num3;


	}



		
	
	
		
}
