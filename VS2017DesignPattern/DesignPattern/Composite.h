#pragma once
#include <iostream>
#include <string>
#include <vector>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

using namespace std;
class Component
{
private:
	Component();  // 不允许

protected:
	string m_strName;

public:
	Component(string name) :m_strName(name) {}
	virtual ~Component() {}
	virtual void Add(Component *cmpt) = 0;  // 添加构件
	virtual void Remove(Component *cmpt) = 0;  // 删除构件
	virtual Component* GetChild(int index) = 0;  // 获取构件
	virtual void Operation(int indent) = 0;  // 显示构件（以缩进的方式）

};

class Leaf : public Component
{
public:
	Leaf(string name) : Component(name) {}
	virtual ~Leaf() {}
	void Add(Component *cmpt) {
		cout << "Can't add to a Leaf" << endl;
	}
	void Remove(Component *cmpt) {
		cout << "Can't remove from a Leaf" << endl;
	}
	Component* GetChild(int index) {
		cout << "Can't get child from a Leaf" << endl;
		return NULL;
	}
	void Operation(int indent) {
		string newStr(indent, '-');
		cout << newStr << " " << m_strName << endl;
	}

private:
	Leaf();  // 不允许
};

class Composite : public Component
{
public:
	Composite(string name) : Component(name) {}
	virtual ~Composite() {
		while (!m_elements.empty()) {
			vector<Component*>::iterator it = m_elements.begin();
			SAFE_DELETE(*it);
			m_elements.erase(it);
		}
	}
	void Add(Component *cmpt) {
		m_elements.push_back(cmpt);
	}
	void Remove(Component *cmpt) {
		vector<Component*>::iterator it = m_elements.begin();
		while (it != m_elements.end()) {
			if (*it == cmpt) {
				SAFE_DELETE(cmpt);
				m_elements.erase(it);
				break;
			}
			++it;
		}
	}
	Component* GetChild(int index) {
		if (index >= m_elements.size())
			return NULL;

		return m_elements[index];
	}
	// 递归显示
	void Operation(int indent) {
		string newStr(indent, '-');
		cout << newStr << "+ " << m_strName << endl;
		// 显示每个节点的孩子
		vector<Component*>::iterator it = m_elements.begin();
		while (it != m_elements.end()) {
			(*it)->Operation(indent + 2);
			++it;
		}
	}

private:
	Composite();  // 不允许

private:
	vector<Component *> m_elements;
};
