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
                cout << "���������" << endl;
                return nullptr;
            }
        }
        void GC()
        {
            for (int i = 0; i < objects.size(); i++)
            {
                if (objects[i].second == false)
                {
                    //�����ʹ���ˣ������Ƿ�ʵ���Ѿ�û��������ʹ�ã�û����ʹ�õĻ����͵ü�ʱ���ջ��߸���ĳ�ֲ�������
                    if (objects[i].first.unique())
                    {
                        //û������ʹ����
                        objects[i].second = true;
                        cout << "�����ˡ�" << i << "������" << endl;
                        //����������������������������ٶ����ڴ棬������Ϊһ�ֻ��շ�ʽ
                        //objectpool[i].first->~Data();
                        //���败����ĳ�����ٲ���
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