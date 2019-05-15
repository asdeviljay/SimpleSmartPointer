// SimpleSmartPointer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRTDBG_MAP_ALLOC 
#include "pch.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <crtdbg.h>

using namespace std;

class Monster
{
private:
	string m_monsterName;
	double m_healthPoint;
	double m_attackPoint;

public:
	Monster()
		: m_monsterName("No Name"), m_healthPoint(10), m_attackPoint(1)
	{
	}

	Monster(string t_monsterName, double t_healthPoint, double t_attackPoint)
		: m_monsterName(t_monsterName), m_healthPoint(t_healthPoint), m_attackPoint(t_attackPoint)
	{
	}

	~Monster()
	{
	}

	void setHealthPoint(double t_healthPoint) {
		m_healthPoint = t_healthPoint;
	}

	double getHealthPoint() {
		return m_healthPoint;
	}

	void decreaseHealthPoint(double t_reduseHealthPoint) {
		m_healthPoint -= t_reduseHealthPoint;
	}

	void setAttackPoint(double t_attackPoint) {
		m_attackPoint = t_attackPoint;
	}

	double getAttackPoint() {
		return m_attackPoint;
	}

	void showInfo() {
		cout << "Name : " << m_monsterName << "\tHP : " << round(m_healthPoint) << "\tATK : " << round(m_attackPoint) << endl;
	}
};

template <typename T> class SimpleSmartPointer
{
private:
	T* m_simpleSmartPointer;
	int m_count;

public:
	SimpleSmartPointer()
		: m_simpleSmartPointer(), m_count(1)
	{
	}

	SimpleSmartPointer(T* t_simpleSmartPointer)
		: m_simpleSmartPointer(t_simpleSmartPointer)
		, m_count(1)
	{
	}

	SimpleSmartPointer(const SimpleSmartPointer<T>& t_simpleSmartPointer)
		: m_simpleSmartPointer(t_simpleSmartPointer.m_simpleSmartPointer)
		, m_count(t_simpleSmartPointer.m_count)
	{
		m_count++;
	}

	~SimpleSmartPointer()
	{
		m_count--;
		if (m_count == 0)
			delete m_simpleSmartPointer;
	}

	T& operator* () {
		return *m_simpleSmartPointer;
	}

	T* operator-> () {
		return m_simpleSmartPointer;
	}

	SimpleSmartPointer<T>& operator = (const SimpleSmartPointer<T>& t_simpleSmartPointer) {
		// Assignment operator
		if (this != &t_simpleSmartPointer) // Avoid self assignment
		{
			// Decrement the old reference count
			// if reference become zero delete the old data
			if (m_count == 0)
				delete m_simpleSmartPointer;

			// Copy the data and reference pointer
			// and increment the reference count
			m_simpleSmartPointer = t_simpleSmartPointer.m_simpleSmartPointer;
			m_count = t_simpleSmartPointer.m_count;
			m_count++;
		}
		return *this;
	}
};

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	SimpleSmartPointer<Monster> p_slime_1(new Monster("Slime No.1", 100, 5.1));
	p_slime_1->showInfo();
	{
		SimpleSmartPointer<Monster> p_slime_2 = p_slime_1;
		p_slime_2->showInfo();

		SimpleSmartPointer<Monster> p_slime_3;
		p_slime_3 = p_slime_1;
		p_slime_3->showInfo();

		SimpleSmartPointer<Monster> p_slime_4(p_slime_1);
		p_slime_4->showInfo();
		*p_slime_4 = Monster("Slime No.2", 500, 25);
		p_slime_4->showInfo();
	}
	p_slime_1->showInfo();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
