#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include <thread>
#include <sstream>
#include <atomic>
#include <iostream>
using namespace std;

namespace TestObjectPool {
    class Data {
    public:
        int i;
        Data()
        {
            i = 0;
            cout << " created " << endl;
        }
        ~Data()
        {
            cout << " destroyed " << endl;
        }
    };


    template<class T>
    class SimpleObjectPool2
    {
    private:
        typedef std::pair<shared_ptr<T>, bool> elemUnit;
        vector<elemUnit> objects;
        int size;
    public:
        SimpleObjectPool2(int length = 10)
        {
            size = length;
        }
        shared_ptr<T> GetElem()
        {
            for (elemUnit& ele : objects)
            {
                if (ele.second == true)
                {
                    ele.second = false;
                    return ele.first;
                }
            }
            if (size > objects.size())
            {
                shared_ptr<T> elePtr = make_shared<T>();
                objects.emplace_back(make_pair(std::move(elePtr), false));
                return objects.back().first;
            }
            else
            {
                cout << "对象池已满" << endl;
                return nullptr;
            }
        }
        void GC()
        {
            for (int i = 0; i < objects.size(); i++)
            {
                if (objects[i].second == false)
                {
                    //如果被使用了，则检查是否实际已经没有其他人使用，没有人使用的话，就得及时回收或者根据某种策略销毁
                    if (objects[i].first.unique())
                    {
                        //没其他人使用了
                        objects[i].second = true;
                        cout << "回收了【" << i << "】对象" << endl;
                        //主动调用析构函数并不会真的销毁对象内存，可以作为一种回收方式
                        //objectpool[i].first->~Data();
                        //假设触发了某种销毁策略
                        //objects[i].first = nullptr;
                    }
                }
            }
        }
    };
    void testObject2()
    {
        SimpleObjectPool2<Data> pool;
        int testCount = 100;
        while (testCount > 0)
        {
            auto ele = pool.GetElem();
            if (ele != nullptr)
                cout << ele->i << endl;
            else
            {
                cout << "xxx" << endl;
            }
            testCount--;
            if (testCount % 10 == 9)
                pool.GC();
        }
    }
}