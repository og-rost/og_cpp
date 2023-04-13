#include <iostream>

double MySqrt(double val) {
	double res = val;
	res = (res + val / res) / 2;
	res = (res + val / res) / 2;
	res = (res + val / res) / 2;
	res = (res + val / res) / 2;
	res = (res + val / res) / 2;
	res = (res + val / res) / 2;
	res = (res + val / res) / 2;
	return res;
}

int main() {
	std::cout << MySqrt(16) << std::endl;
	std::cout << MySqrt(25) << std::endl;
	std::cout << MySqrt(36) << std::endl;
}
