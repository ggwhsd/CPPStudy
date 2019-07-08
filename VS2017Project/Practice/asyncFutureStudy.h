#pragma once
#include <future>
#include <iostream>

class mathTools
{
public:
	bool is_prime(int x) {
		std::this_thread::sleep_for(std::chrono::seconds(5));
		for (int i = 2; i<x; i++)
		{
			if (x%i == 0)
				return false;
		}
		return false;
	}
};

int stdAsynct_test()
{
	mathTools m;
	std::future<bool> fut = std::async(&mathTools::is_prime, &m, 32212);
	std::cout << "please wait";
	std::chrono::milliseconds span(1000);
	while (fut.wait_for(span) != std::future_status::ready)
	{
		std::cout << ".";
		std::cout.flush();
	}
	std::cout << "wait end\n";

	bool ret = fut.get();
	std::cout << "result: " << (ret == true ? "Ture" : "False") << std::endl;
	return 0;
}



