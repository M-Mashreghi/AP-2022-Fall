
#include <iostream>
#include <string>
#include <cstdlib>


using namespace std;

double CPU_power(int year ,double corei3_power, double corei5_power, double corei7_power)
{
	double corei3_power_new = 1.5 * corei3_power;
	double corei5_power_new = 0.2 * corei3_power_new + 1.2 * corei5_power;
	double corei7_power_new = 1.3 * corei7_power + 0.3 * corei5_power_new + 0.2 * corei3_power_new;

	if (year == 1) { cout << "core i3" << endl; return corei3_power; }
	else if (year == 2) { cout << "core i5" << endl; return corei5_power; }
	else if (year == 3) { cout << "core i7" << endl; return corei7_power; }
	else return CPU_power(year - 3, corei3_power_new, corei5_power_new, corei7_power_new);

		



}


int main()
{
  
	double corei3_power = 1;
	double corei5_power = 1.4;
	double corei7_power = 1.7;
	int year;
	cin >> year ;

	cout << CPU_power(year, corei3_power, corei5_power, corei7_power) << endl;

	/*
	cout << CPU_power(1, corei3_power, corei5_power, corei7_power) << endl;
	cout << CPU_power(2, corei3_power, corei5_power, corei7_power) << endl;
	cout << CPU_power(3, corei3_power, corei5_power, corei7_power) << endl;
	cout << CPU_power(4, corei3_power, corei5_power, corei7_power) << endl;
	cout << CPU_power(5, corei3_power, corei5_power, corei7_power) << endl;
	cout << CPU_power(6, corei3_power, corei5_power, corei7_power) << endl;
	cout << CPU_power(7, corei3_power, corei5_power, corei7_power) << endl;
	cout << CPU_power(8, corei3_power, corei5_power, corei7_power) << endl;
	cout << CPU_power(9, corei3_power, corei5_power, corei7_power) << endl;

	*/



}
