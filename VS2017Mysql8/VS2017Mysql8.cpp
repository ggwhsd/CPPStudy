// VS2017Mysql8.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <mysql.h>
#include <vector>
#include <chrono>
 //https://www.cnblogs.com/cansun/p/8605525.html
 //https://blog.csdn.net/qq_21095573/article/details/82824693

#include <mutex>
using namespace std;
using namespace chrono;

class DBService
{
	class DBInfo
	{
	public:
		string Server;
		unsigned int Port;
		string Username;
		string Password;
		string Database;
	};
private:
	typedef std::shared_ptr<DBService> Ptr;
	static Ptr instance;
	
	static mutex lockInstance;
	DBInfo info;
	MYSQL *mysql = nullptr;    //一个数据库结构体
	bool isConnected = false;

private:
	void Connect()
	{
		if (mysql == nullptr)
		{
			MYSQL_RES* res; //一个结果集结构体
			MYSQL_ROW row;  //char** 二维数组，存放一条条记录
			
			//初始化数据库
			mysql = mysql_init(NULL);
			//设置编码方式
			//mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
			
			if (mysql_real_connect(mysql, info.Server.c_str(), info.Username.c_str(), info.Password.c_str(), info.Database.c_str(), 3306, NULL, 0) == NULL)
				isConnected = false;
			else
			{
				isConnected = true;
			}
			//查询数据
			mysql_query(mysql, "SELECT * FROM studydb.articles");
			//获取结果集
			res = mysql_store_result(mysql);
			while (row = mysql_fetch_row(res))
			{
				printf("%s %s %s", row[0], row[1], row[2]);//
				

			}
			//释放结果集
			mysql_free_result(res);
		}

	}
	void Close()
	{
		if (mysql != nullptr) {
			mysql_close(mysql);
			
		}
	}
public:

	
	DBService()
	{
		InitDBInfo();
		Connect();
	}
	~DBService()
	{
		Close();
	}
	DBService(DBService&) = delete;
	DBService& operator=(const DBService&) = delete;

	static Ptr  GetInstance()
	{
		if (instance == nullptr)
		{
			lock_guard<mutex> lk(lockInstance);
			if (instance == nullptr)
			{
				instance =  shared_ptr<DBService>(new DBService());
			}
		}
		return instance;
	}

	void InitDBInfo()
	{
		info.Server = "127.0.0.1";
		info.Password = "12345678";
		info.Username = "testDB";
		info.Port = 3306;
		info.Database = "studydb";
	}
	
	bool IsConnected()
	{
		if (mysql)
		{
			return isConnected;
		}
		else
		{
			return false;
		}
	}
	
	bool TestSelect()
	{
		bool success = false;
		if (isConnected == true)
		{
			MYSQL_RES* res; //一个结果集结构体
			MYSQL_ROW row;  //char** 二维数组，存放一条条记录
			char tmp[400];
			
			//查询数据
			mysql_query(mysql, "SELECT * FROM studydb.articles");
			//获取结果集
			res = mysql_store_result(mysql);
			while (row = mysql_fetch_row(res))
			{
				sprintf_s(tmp,"%s %s %s", row[0], row[1], row[2]);
				success = true;
			}
			//释放结果集
			mysql_free_result(res);
		}
		else
		{
			success = false;
		}
		return success;
	}

	void  TestGetResult(string sql)
	{
		
		if (isConnected == true)
		{
			MYSQL_RES* res; //一个结果集结构体
			MYSQL_ROW row;  //char** 二维数组，存放一条条记录
			char tmp[400];

			//查询数据
			mysql_query(mysql, "SELECT * FROM studydb.articles");
			//获取结果集
			res = mysql_store_result(mysql);
			MYSQL_FIELD* field ;
			
			auto cols = GetCols(res);
			auto iterCol = cols.begin();
			while (iterCol != cols.end())
			{
				cout << (*iterCol).c_str() << " ";
				iterCol++;
			}

			auto rows = GetRows(res);
			vector<vector<string>>::iterator iterRow = rows.begin();
			while (iterRow != rows.end())
			{
				vector<string>::iterator iterValue = (*iterRow).begin();
				while (iterValue != (*iterRow).end())
				{
					cout << (*iterValue).c_str() << " ";
					iterValue++;
				}
				
				iterRow++;
			}
			
			//释放结果集
			mysql_free_result(res);
		}
		
		
	}
	vector<string>  GetCols(MYSQL_RES *res)
	{
		vector<string> cols;
		if (res != nullptr)
		{
			MYSQL_FIELD* field;
			while (field = mysql_fetch_field(res))
			{
				cols.push_back(field->name);
			}
		}
		else
		{
			
		}
		return cols;
	}

	vector<vector<string>> GetRows(MYSQL_RES *res)
	{
		vector<vector<string>> value_rows;
		vector<string> value_row;
		if (res != nullptr)
		{
			MYSQL_ROW row;
			int cols_count = res->field_count;

			while (row = mysql_fetch_row(res))
			{
				for (int i = 0; i < cols_count; i++) {
					value_row.push_back(row[i]);
				}
				
				value_rows.push_back(value_row);
				value_row.clear();
			}
			
		}
		else
		{

		}
		return value_rows;
	}

	void WriteData()
	{
		string sql = "delete from articles"; //关闭自动提交
		int rt = mysql_query(mysql, sql.c_str());
		if (rt != 0)
		{
			cout << "执行sql 错误" << mysql_error(mysql) << endl;
		}

		// sql = "set autocommit = 0"; //关闭自动提交
		// rt = mysql_query(mysql, sql.c_str());
		//if (rt != 0)
		//{
		//	cout << "执行sql 错误" << mysql_error(mysql) << endl;
		//}

#pragma region 事务必须要有提交或者回滚，对于事务，autocommit不生效，对于非事务默认生效



		auto start = system_clock::now();
		sql = "START TRANSACTION";
		 rt = mysql_query(mysql, sql.c_str());
		if (rt != 0)
		{
			cout << "执行START TRANSACTION 错误" << mysql_error(mysql) << endl;
		}


		for (int i = 0; i < 1000; i++)
		{
			sql = "INSERT INTO articles (pageid, authorid) VALUES ('9', '2');";
			rt = mysql_query(mysql, sql.c_str());
			if (rt != 0)
				cout << "执行insert sql出错" << mysql_error(mysql)<<endl;
		}

		sql = "COMMIT";
		 rt = mysql_query(mysql, sql.c_str());
		if (rt != 0)
		{
			cout << "执行COMMIT错误" << mysql_error(mysql) << endl;
		}

#pragma endregion


		auto end = system_clock::now();

		// sql = "set autocommit = 1"; //打开自动提交
		// rt = mysql_query(mysql, sql.c_str());
		//if (rt != 0)
		//{
		//	cout << "执行sql 错误" << mysql_error(mysql) << endl;
		//}
		auto dur = duration_cast<milliseconds>(end - start);
		cout << "耗时:【" << dur.count() << "】毫秒";
	}

};

DBService::Ptr DBService::instance = nullptr;
mutex DBService::lockInstance;

int main()
{
	std::cout << "Hello World!\n";

	std::cout << DBService::GetInstance()->IsConnected() << endl;

	std::cout << DBService::GetInstance()->TestSelect() << endl;

	DBService::GetInstance()->TestGetResult("");

	DBService::GetInstance()->WriteData();


	//注意你连接的账户名密码
			//注意你连接的账户名密码
					//注意你连接的账户名密码
							//注意你连接的账户名密码

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
