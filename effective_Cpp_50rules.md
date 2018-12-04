## 条款【1】

c++是一个联邦语言。一开始c++是c加上了一些面向对象的特性。

因此C++最初的名称是C with Class。但是c++目前拥有`多重范型编程语言`，可以理解为次语言，主要有四个：

1. `c语言`，没有模板，没有异常，没有重载...
2. `object-oriented c++`, 有了类，析构，构造，封装，继承，多态，virtual函数
3. `Template C++`, 这个是泛型编程。
4. `STL`， STL是一个template程序库，迭代器，容器，算法，以及函数对象。

每个次语言都有自己的编程规则。使用c++开发程序，不一定要使用里面所有的次语言规则，比如，有的人只喜欢过程开发，可以只使用c语言部分。
    
## 条款【2】

尽量以`const`，`enum`，`inline`来替换预处理`#define`。

因为前者可以被编译器看到，而`#define`是在预处理阶段，编译器是不知道里面的符号名称的。
两个特殊：

1. 如果使用`char*`，则需要`const char* const name = "effective"`，不过，书中建议使用`string`，如`const std::string name("effective")`;
2. 如果是在类中定义常量,假设类为GameBB，则需要声明为
	`static const int Num = 5`；
同时在实现文件中定义 
	`const int GameBB::Num`，无需赋值。

但是有一种情况，编译器可能不支持上述这种写法，则可以改为如下的写法:

头文件   ` const int Num;`
实现文件 `const int GameBB::Num = 5;`

假如在编译阶段就需要用常量,又不能给常量赋值？比如定义数组，此时可以用enum
	enum {Num=5}
	int scores[Num]
	

## 条款【3】

尽可能使用`const`。

`const`可以修饰指针，可以修饰指针所指物，或者两者都是。

	char hello[]="hello";
	char* ptr = hello;
	const char* ptr = hello;          //non-const pointer, but const data
	char* const ptr = hello;          //const pointer, non-const data
	const char* const ptr = hello;    //const pointer, const data

`const` 可以修饰方法，表示该方法不可以修改成员变量。如果存在，则编译报错。

`const` 可以修饰方法的返回值，表示返回值不可以被修改，这是一种对于返回的引用变量，阻止其操作成员内部变量的方法。

将`non-const`转换为`const`，可以通过`static_cast`。将`const`转换为`non-const`,可以使用`const_cast`。


## 条款【4】

确定对象使用前已经被初始化。

牢记3条：

1. 构造函数最好使用成员初始值列，而不要在构造函数中进行赋值。初始值列的次序应该和它们在class中的声明次序相同。
2. 内置对象进行手工初始化。
3. 对于不同文件中的全局的non-local static对象，请替换为local static对象，也就是将这些对象发到函数中。