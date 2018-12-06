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

1. 构造函数最好使用成员初始值列，而不要在构造函数中进行赋值。初始值列的次序应该和它们在`class`中的声明次序相同。
2. 内置对象进行手工初始化。
3. 对于不同文件中的全局的`non-local static`对象，请替换为`local static`对象，也就是将这些对象发到函数中。


## 条款【5】

C++默默编写并调用了 `default`构造函数、`copy`构造函数、析构函数、`copy assignment`操作符。但是有个前提，惟有代码中没有自定义这些函数，且这些函数被调用了，才会编译创建。

## 条款【6】

若不想编译器自动生成函数，则需要明确拒绝。拒绝方式就是把这些函数声明为`private`，同时没有函数实现，注意不是空函数体`{}`，而是不实现。

## 条款【7】

一个多态基类有多个子类，多态基类最好声明`virtual`的析构函数，避免在使用动态内存时，对基类指针进行`delete`，没有调用子类的析构函数。

若一个基类不是用作多态，则无需为析构函数声明`virtual`。

## 条款【8】

别让异常析构函数。 

因为析构函数抛出异常，则会引起不明确的行为。 

所以，为了避免这种情况，对于可能发生异常的情况，请使用`try-catch`，可以在`catch`中终止程序或者记录异常继续运行。

也可以将析构函数中的功能单独放在一个函数中，供使用方单独调用，以便知道运行结果，可以进行其他处理。

## 条款【9】

在构造函数和析构函数中，不要调用`virtual`函数。因为`virtual`函数实现是在子类，而构造函数和析构函数可能是在父类，此时无法调用子类的函数。

## 条款【10】

令`operator=`返回一个`reference to *this`

	class Widget { ... }
	Widget& operator=(const Widget& rhs)
	{
		...
		return * this;
	}

	
## 条款【11】

在`operator=`中处理“自我赋值”，比如一些成员为指针变量时，赋值就要特别注意，可以使用 检查是否相同即自我赋值，也可以使用`copy and swap`方式即先构造，然后将指针变量指向到这个构造对象上。

## 条款【12】

复制对象时勿忘其每一个成分。我理解就是深赋值时，要考虑每个成员。

## 条款【13】

以对象管理资源。使用RAII对象，比如`auto_ptr`或者`shared_ptr`来管理指针分配的动态资源，当然也可以自己实现对象管理资源。

* `auto_ptr`会在其作用域结束时调用其析构函数，`delete`掉申请的对象空间,且auto_ptr pt2 = pt1 ,进行copy assignment操作时，原先的pt1.get()会变为NULL,资源被转移给了pt2。
* `shared_ptr`跟`auto_ptr`有着相同的作用，并且增加了引用计数器，当引用计数器为0，即没有指向它时，自动删除其对象。
* 两者在释放资源都是delete，不是delete[]，因为vector和string几乎可以代替数组。

## 条款【14】

对资源管理类的coping需要小心，需要考虑是否需要复制副本、引用计数、转移资源拥有权、还是禁止复制。我觉得，只要你写过一些资源管理的程序，你肯定能够理解以上这句话的含义。

## 条款【15】

RAII类应该提供一个访问原始资源的方法，以便一些C API访问，因为C API中参数经常是调用原始资源。对原始资源的访问可以用显示例如get，也可以隐式转换。

## 条款【16】

new和delete要成对使用，如果表达式中使用了[]，则相应的delete也要用[]。

对于typedef，最好不要对数组形式使用typedef，如要要用，则需要使用delete [].
	
	typedef std::string address[4];
	std::string pa1 = new address;
	delete []pa1

## 条款【17】

以独立语句将newed对象存储于智能指针中，避免一旦异常被抛出，可能导致难查的资源泄漏。如果是小程序，这点可能泄漏不会对程序引起大的风险，但是如果是一个交易系统，且频率很高的交易系统，则必然引起一个大的问题。

	std::tr1::shared_ptr<Widget> pw(new Widget);
	processWidget(pw,priority());


## 条款【18】

让接口容易被使用，不易被误用。

这条我觉得是开发中，每个专业程序员都应该知晓的。


