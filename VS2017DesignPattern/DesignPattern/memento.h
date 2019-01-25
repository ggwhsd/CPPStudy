#pragma once
#include <iostream>
using namespace std;

class RoleStateMemento
{
private:
	//friend class GameRole;
	unsigned m_iBlood;
	unsigned m_iAttack;
	unsigned m_iDefense;
public:
	unsigned GetBloodValue() {
		return m_iBlood;
	}
	unsigned GetAttackValue() {
		return m_iAttack;
	}
	unsigned GetDefenseValue() {
		return m_iDefense;
	}


public:
	RoleStateMemento(unsigned iBlood, unsigned iAttack, unsigned iDefense) : m_iBlood(iBlood), m_iAttack(iAttack), m_iDefense(iDefense) {}
}
;

class GameRole {
private:
	unsigned m_iBlood;   // ÉúÃüÁ¦
	unsigned m_iAttack;  // ¹¥»÷Á¦
	unsigned m_iDefense; // ·ÀÓùÁ¦

public:
	GameRole() : m_iBlood(100), m_iAttack(100), m_iDefense(100) {}
	// ´æµµ
	RoleStateMemento *SaveState() { return new RoleStateMemento(m_iBlood, m_iAttack, m_iDefense); }

	// »Ö¸´´æµµ
	void RecoveryState(RoleStateMemento *pRoleState)
	{
		m_iBlood = pRoleState->GetBloodValue();
		m_iAttack = pRoleState->GetAttackValue();
		m_iDefense = pRoleState->GetDefenseValue();
		cout << "Recovery..." << endl;
	}

	void ShowState()
	{
		cout << "Blood:" << m_iBlood << endl;
		cout << "Attack:" << m_iAttack << endl;
		cout << "Defense:" << m_iDefense << endl;
	}

	void Fight()
	{
		m_iBlood -= 100;
		m_iAttack -= 10;
		m_iDefense -= 20;

		if (m_iBlood == 0)
		{
			cout << "Game Over" << endl;
		}
	}



};


class RoleStateCaretaker
{
public:
	void SetRoleStateMemento(RoleStateMemento *pRoleStateMemento) { m_pRoleStateMemento = pRoleStateMemento; }
	RoleStateMemento *GetRoleStateMemento() { return m_pRoleStateMemento; }

private:
	RoleStateMemento * m_pRoleStateMemento;
};

