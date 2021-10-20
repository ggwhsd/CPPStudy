// TemplateMeta.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。


// 参考 https://www.cnblogs.com/qicosmos/p/4480460.html

#include <iostream>
using namespace std;


//模板泛型编程,主要目的是类型通用。这也是模板一开始的目的，元编程属于后续发展的应用。
template<typename T, int N>
class A
{
public:
	void Show(T value)
	{
		T t1;
		t1 = value;
		cout << t1 << endl;
		cout << N << endl;
	}
};

//模板元编程，元编程包含两个，元数据和元函数，如下为元函数。元编程用到的数据都是元数据，是编译期间能够确定的，而不是运行时，所以只能是静态常量、枚举等。
template<int N, int M>
struct meta_fun
{
	const static int value = N + M;
};



//type_traits是模板元的基础库,通过type_traits可以实现在编译期计算、查询、判断、转换和选择，提供了模板元编程需要的一些常用元函数
// 元函数是用来处理元数据的，一定要牢记。 
// 元编程主要目的是用代码在编译期间做一些事情
//第一个库函数:integral_constant
/*
* template< class T, T v >
struct integral_constant;
*/
void test_integral_constant()
{
	using one_type = std::integral_constant<int, 1>;
	cout << one_type::value << endl;
	//库提供的true和false元函数
	cout << (true_type::value == true)<< endl;
	cout << (false_type::value == false) << endl;
	cout << is_const<int>::value << endl;
	cout << is_const<const int>::value << endl;
	cout << is_same<int, int>::value << endl;
	cout << is_same<int, unsigned int >::value << endl;

	cout << "--------------------" << endl;
	//添加、移除const
	cout << std::is_same<const int, add_const<int>::type>::value << endl;
	cout << std::is_same<int, remove_const<const int>::type>::value << endl;
	//添加引用
	cout << std::is_same<int&, add_lvalue_reference<int>::type>::value << endl;
	cout << std::is_same<int&&, add_rvalue_reference<int>::type>::value << endl;
	//取公共类型
	typedef std::common_type<unsigned char, short, int>::type NumericType;
	cout << std::is_same<int, NumericType>::value << endl;
	
	cout << "---------------------------" << endl;
	//类似于三目运算符
	typedef std::conditional<true, int, float>::type A;
	typedef std::conditional<false, int, float>::type B;
	//输出类型名
	cout << typeid(A).name() << endl;
	cout << typeid(B).name() << endl;
	//编译期间 ，sizeof之间也可以进行比较
	typedef std::conditional< (sizeof(long long) > sizeof(long double)) , long long, long double>::type max_size_t;
	cout << typeid(max_size_t).name() << endl;

	
	
}

void test_decay()
{
	cout << "-------------------------------" <<__FUNCTION__ << endl;
	//移除cv符，以及函数类型转换为函数指针类型
	typedef std::decay<int>::type A1;           // int
	cout << typeid(A1).name() << endl;
	typedef std::decay<int&>::type B1;          // int
	cout << typeid(B1).name() << endl;
	typedef std::decay<int&&>::type C1;         // int
	cout << typeid(C1).name() << endl;
	typedef std::decay<const int&>::type D1;    // int
	cout << typeid(D1).name() << endl;
	typedef std::decay<int[2]>::type E1;        // int*
	cout << typeid(E1).name() << endl;
	typedef std::decay<int(int)>::type F1;       // int(*)(int)
	cout << typeid(F1).name() << endl;
}

template<typename F>
struct Decay_FunctionExample
{
	using FnType = typename std::decay<F>::type;//先移除引用再添加指针
	Decay_FunctionExample(F& f) : m_fn(f) {}   //将函数转换为函数指针保存下来。
	void Run()
	{
		cout<<m_fn(1);
	}
	FnType m_fn;  
};
int fn_decay(int a) { return a; }
void test_Decay_FunctionExample()
{
	cout << "-------------------------------" << __FUNCTION__ << endl;
	typedef std::decay<int(int)>::type F1;
    F1 f= fn_decay;
	// C++98/03的写法 typedef int(*p)(int);    p f = fn_decay;
	Decay_FunctionExample<int(*)(int)> d(f);
	d.Run();

}


int fn(int) { return int(); } // function
typedef int(&fn_ref)(int);  //function reference
typedef int(*fn_ptr)(int);  // function pointer
struct fn_class { int operator()(int i) { return i; } };  // function-like class


void test_result_of()
{
	cout << "-------------------------------" << __FUNCTION__ << endl;
	//调用对象返回类型
	fn_class f; f(1);
	//C++11新标准引入了decltype类型说明符，它的作用是选择并返回操作数的数据类型，在此过程中，编译器分析表达式并得到它的类型，却不实际计算表达式的值。
	typedef std::result_of<decltype(fn)& (int)>::type A;
	typedef std::result_of<fn_ref(int)>::type B;
	typedef std::result_of<fn_ptr(int)>::type C;
	typedef std::result_of<fn_class(int)>::type D;

	cout << typeid(A).name() << endl;
	cout << typeid(B).name() << endl;
	cout << typeid(C).name() << endl;
	cout << typeid(D).name() << endl;
}

//根据模板来定义返回值类型，并且限定了只能特定数字范围类型才能够使用重载。相比于传统的重载函数，以及不适用enable_if的模板函数而言，有个更多的控制和开发效率。
template <class T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type foo(T t)
{
	return t;
}

//根据模板来定义返回值类型，限定了入参类型的范围，同时限定了返回值类型都为int
template <class T>
typename std::enable_if<std::is_arithmetic<T>::value, int>::type foo1(T t)
{
	return t;
}
template <class T>
typename std::enable_if<!std::is_arithmetic<T>::value, int>::type foo1(T t)
{
	cout << typeid(T).name() << endl;
	return 1;
}

void test_enable_if()
{
	cout << "-------------------------------" << __FUNCTION__ << endl;
	cout << foo<int>(1) << endl;;
	cout << foo(2) <<endl;
	cout << foo(3.1) << endl;
	//foo("3.1");  // 这个在vs2019里面，直接在Intelligence中就报错了E0304。
	cout << foo1(100) << endl;
	cout << foo1("100") << endl;
}




int main()
{
	A<int, 5> a;
	a.Show(100);
	cout << "01 case: meta_fun【" << meta_fun<1, 3>::value << "】" << endl;;
	test_integral_constant();
	test_decay();
	test_Decay_FunctionExample();
	test_result_of();
	test_enable_if();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
