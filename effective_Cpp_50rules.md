## 条款【1】
	c++是一个联邦语言。一开始c++是c加上了一些面向对象的特性。因此C++最初的名称是C with Class。但是c++目前拥有`多重范型编程语言`，可以理解为次语言，主要有四个：
	1. `c语言`，没有模板，没有异常，没有重载...
	2. `object-oriented c++`, 有了类，析构，构造，封装，继承，多态，virtual函数
	3. `Template C++`, 这个是泛型编程。
	4. `STL`， STL是一个template程序库，迭代器，容器，算法，以及函数对象。
	每个次语言都有自己的编程规则。使用c++开发程序，不一定要使用里面所有的次语言规则，比如，有的人只喜欢过程开发，可以只使用c语言部分。
	
## 条款【2】
	尽量以`const`，`enum`，`inline`来替换预处理`#define`。因为前者可以被编译器看到，而`#define`是在预处理阶段，编译器是不知道里面的符号名称的。
	两个特殊：
	1. 如果使用`char*`，则需要`const char* const name = "effective"`，不过，书中建议使用`string`，如`const std::string name("effective")`;
	2. 如果是在类中定义常量,假设类为GameBB，则需要声明为 
		`static const int Num = 5`；
		同时在实现文件中定义 
		`const int GameBB::Num`，无需赋值。