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
	Component();  // ������

protected:
	string m_strName;

public:
	Component(string name) :m_strName(name) {}
	virtual ~Component() {}
	virtual void Add(Component *cmpt) = 0;  // ��ӹ���
	virtual void Remove(Component *cmpt) = 0;  // ɾ������
	virtual Component* GetChild(int index) = 0;  // ��ȡ����
	virtual void Operation(int indent) = 0;  // ��ʾ�������������ķ�ʽ��

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
	Leaf();  // ������
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
	// �ݹ���ʾ
	void Operation(int indent) {
		string newStr(indent, '-');
		cout << newStr << "+ " << m_strName << endl;
		// ��ʾÿ���ڵ�ĺ���
		vector<Component*>::iterator it = m_elements.begin();
		while (it != m_elements.end()) {
			(*it)->Operation(indent + 2);
			++it;
		}
	}

private:
	Composite();  // ������

private:
	vector<Component *> m_elements;
};
