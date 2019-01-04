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

## 条款【19】

设计class犹如设计type，在c++中，每设计一个新的class，就是设计一个新type。好的type有自然的语法、直观的语义，以及一或者多个高效实现品。

在设计一个新的type时，要回答如下问题：

* 新对象如何被创建和销毁？
* 初始化和赋值该有什么样的差别？
* 新的type对象如果被passed by value，意味着什么？也就是copy构造函数是否要考虑。
* 新type的合法值是什么？也就是约束条件
* 新type是否要配合继承关系？
* 新type需要什么样的转换？
* 什么样的操作符和函数对此新type而言是合理的？
* 什么样的标准函数应该驳回？这些函数要声明为private。
* 新的type是否需要一般化？如果需要一般化，就得考虑顶一个新的class template。
* 最后一个，真的需要一个新type？是否可以在原有type上新增函数或者template？

## 条款【20】

尽量以`pass-by-reference-to-const`替代`pass-by-value`。前者通常比较高效，并可避免切割问题。（子类被切割成父类）

以上规则不适用于内置类型、STL的迭代器和函数对象。

## 条款【21】

绝不要让reference和pointer指向一个local stack对象。或者返回reference指向一个heap-allocated对象，因为reference无法释放对象。


## 条款【22】

成员变量声明为private。这个我一直都是这么开发的，对于状态的维护、约束以及多线程操作，会减少很多不必要的问题。

## 条款【23】

用non-member non-friend函数替换member函数。 因为封装性前者比后者更高。

什么时候需要这样考虑呢？比如一个类中有多个member函数，如果每次都要依次调用这些member函数，会很烦，此时写一个member来调用这些函数。

对于写习惯了java代码的程序员你来说，可能会考虑使用类中的static member来替换member。  不过c++的做法，可以在某个命名空间中，使用c的函数来替换member。

## 条款【24】

如果需要为某个函数的所有参数进行类型转换，请使用non-member的设计。  我开发到现在，没有使用过这种情况，要么转换好了给函数调用，要么提供重载方式，亦或者使用模板，也就不会出现参数进行类型转换了。牺牲一点便利性，就可以跳过这条条款。

## 条款【25】

考虑写出一个不抛出异常的`swap`函数。这是一个调换两个对象的函数。`std::swap`有一个默认的模板实现。

## 条款【26】

尽可能延后定义变量，这样可以增加程序的清晰度并改善程序性能，比如：

	void test(const string& value)
	{
		string str1;
		if(value=="" || value.lenght()<10)
			return;
		else
			str1=value;
	}

改为

	void test(const string& value)
	{
		
		if(value=="" || value.lenght()<10)
			return;
		else
		{
			string str1(value);
		}
	}
	
## 条款【27】

尽量少做转型。

c++中提供了四种类型转换：`const_cast<T>(expression)`,`dynamic_cast<T>(express)`,`reinterpret_cast<T>(express)`,`static_cast<T>(express)`。常用的`const_cast`和`static_cast`。


## 《more effective c++》条款23

考虑使用程序库。理想的程序库：小、快速、威力强大、扩张性好、直观使用、广泛运用、良好支持、使用没有束缚、没有bug。

如果针对大小和速度，往往不具备很好的移植。如果拥有丰富的机能，就不容易直观。没有bug的程序库只能在乌托邦中寻找。真实世界中，不可能拥有每一样东西。

比如iostream和stdio库，前者使用方便，类型安全，后者库文件通常较小，通常执行较快。

## 《more effective c++》条款24

使用虚函数、多重继承、虚拟基类和RTTI的成本。

如果我们要使用这些特性，那么必须承受这些成本。其实成本不是很大。但是也要知晓成本的存在及其意义。

主要是使用这些都会创建`vbtls`和`vptrs`。前者为`virtual tables`，后者为`virtual tables pointer`，用于指向哪个`vbtls`。

每个类中都会有一个`vbtls`,类似数组或者链表结构，每一个元素用来记录自己的一个虚函数对应的实现方法。`vptrs`则是每个对象会有的，用于指向具体哪个`vbtls`。

而RTTI则是基于vbtls来实现，相关信息存放在type_info对象中，而该type_info对象放于vbtls中。用于在运行时期得知对象和类的信息。

## 《more effective c++》条款25 

将construct和non-member functions虚化。为什么需要这个呢？我一开始也很疑惑。

`virtual constructor` 原来就是基类虚函数，只是这个虚函数是用于根据不同的输入产生不同的类型对象。然后派生类实现虚函数创建自身对象，基类则可以在使用时根据不同类型创建不同的类对象以便指针或者引用使用，

跟设计模式中的抽象工厂类很像。

如下示例之一,有没有发现什么？虚函数的返回值可以不一样，如果返回值是指针或者引用，指向一个基类，那么派生类的函数可以返回一个指针或者引用，指向基类的一个派生类。

	class Block{
	public:
		virtual Block * clone() const = 0;
	};
	class TextBlock : public Block 
	{
	public:
		virtual TextBlock * clone() const
		{
			return new TextBlock(*this);
		}
		...
	}
	class ImageBlock : public Block 
	{
	public:
		virtual ImageBlock * clone() const
		{
			return new ImageBlock(*this);
		}
		...
	}


non-member functions,这个，我是觉得应该很少会用到的吧，因为书中举了个操作符虚化的例子，我对重构操作符一直没什么好感。

## 《more effective c++》条款26

解决允许一个类生产特定数量的同类对象：对象计数`Object-counting`

	class Printer{
	public:
		class TooManyObjects();
		Printer();
		~Printer();
		...
	private:
		static size_t numObjects;
		Printer(const Printer& rhs);
	}
	
	size_t Printer::numObjects = 0;
	Printer::Printer()
	{
		if(numObjects>=1)
		{
			throw TooManyObjects();
		}
		++numObjects;
	}
	Printer::~Printer()
	{
		--numObjects;
	}
	
若是不同类构造状态，以上方法是无法解决的。例如

	class ColorPrinter: public Printer
	{
	...
	}
	Printer p;
	ColorPrinter cp;
	
以上会产生两个`Printer`对象。若想只产生一个对象，则`Printer`中需要声明私有构造函数。但是这样子，`Printer`也无法创建对象。怎么办呢？
	
新增一个方法(伪构造函数`pseudo-constructor`），调用私有构造函数。同时为了管理对象资源，使用`auto_ptr`来使用这些资源。
	
	class FSA{
	public:
		static FSA* makeFSA();  // pseudo-constructor
		static FSA* makeFSA(const FSA& rhs);
		...
	private:
		FSA();
		FSA(const FSA& rhs);
	};
	
	FSA* FSA::makeFSA()
	{ return new FSA(); }
	
	FSA* FSA::makeFSA(cosnt FSA& rhs)
	{ return new FSA(rhs); }

	auto_ptr<FSA> pfsa1(FSA::makeFSA());
	auto_ptr<FSA> pfsa2(FSA::makeFSA(*pfsa1));
	
以上代码中，及时有类继承，只要派生类中没有调用基类的`makeFSA`方法，则不会产生多余对象。
	

## 《more effective c++》条款27

** 1.要求对象产生于heap中。 **

我们应该知道，程序中如果用new，则会产生于`heap`中，否则产生于`stack`中。而`new`里面的操作有两步，申请`heap`内存空间，以及调用构造函数，如果无法调用构造函数，则`new`会失败。

因此，思路就是限制构造函数和析构函数，因为非heap的对象，会自动调用构造和析构函数。 但是构造函数是可以重载的，限制的话，就需要限制所有的构造函数，这样感觉不方便，所以，采用限制唯一的析构函数，是比较好的。将析构函数申明为`private`，同时新增一个用于释放资源的伪析构函数。从而达到限制的目的。

如上虽然解决了只允许对象产生于`heap`中，但是也带来了如下两个问题：继承和内含。

继承，派生类继承基类，由于析构函数为`private`，所以，将`private`改为`protect`，则派生类能访问，因此能使用`heap`。

内含，就是把某类对象作为其他类的成员，此时可以使用指针的方式，此方法也可以只允许其生成在`heap`中。


```flow
st=>start: 开始
op=>operation: My Operation
cond=>condition: Yes or No?
e=>end
st->op->cond
cond(yes)->e
cond(no)->op
&```


