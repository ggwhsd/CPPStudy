#pragma once
#include <random>
#include <time.h>
#include <iostream>
using namespace std;

void testRandom()
{
	std::default_random_engine random(time(nullptr));

	// �������ȷֲ�
	std::uniform_int_distribution<int> int_r(0, 100);
	for (int i = 0; i < 20; ++i) {
		cout << int_r(random) << ',';
	}
	cout << endl;

	// ���������ȷֲ�
	std::uniform_real_distribution<float> real_r(0.0, 1.0);
	for (int i = 0; i < 20; ++i) {
		cout << real_r(random) << ',';
	}
	


		

}