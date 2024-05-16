/************************************************************************
 * file: Person.h
 * Person abstract class definition
 * Employee derived class definition from Person
 * Manager derived class definition from Employee
 * written: 28/02/2021
 * created by Vlad Seletkov
*************************************************************************/

#ifndef LABA_1_OOP_PERSON_H
#define LABA_1_OOP_PERSON_H

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <typeinfo>
#include <locale>
#include <fstream>

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable : 4996)

using std::string;
using std::cout;
using std::endl;
using std::list;
using std::vector;

//An abstract class
class Person {
public:
	Person() : f_name("empty"), l_name("empty"), age(-1) {}
	Person(string _f_name, string _l_name, int _age) : f_name(_f_name), l_name(_l_name), age(_age) {}
	int GetAge();
	virtual void Display(bool flag) = 0;
	virtual ~Person() = default; 
protected:
	string f_name;
	string l_name;
	int age;
};

//A derived class from Person class
class Employee : public Person {
public: 
	Employee() : department("empty"), salary(-1), id(-1) {}
	Employee(string _f_name, string _l_name, int _age, int _id) : Person(_f_name, _l_name, _age), id(_id), salary(-1), department("empty") {}
	Employee(const Employee &e);
	Employee &operator = (const Employee &e);
	void SetSalary(int s);
	void SetDepartment(string dept);
	void SetId(int n);
	int GetSalary();
	string GetDepartment();
	int GetId();
	virtual void Display(bool flag) override;
protected:
	string department;
	int salary;
	int id;
};

//A derived class from Employee class
class Manager : public Employee {
public:
	Manager() {};
	Manager(string _f_name, string _l_name, int _age, int _id) : Employee(_f_name, _l_name, _age, _id) {};
	Manager(const Manager &m);
	virtual void Display(bool flag) override;
	//add an employee to the subordinates list
	Person *AddSubordinate(Person *p);
	void DisplaySubordinates();
	void DisplaySubordinatesByDepartment(string _department);
	void DeleteSubordinates();
	void EraseSubordinateById(int id);
private:
	list <Person*> subordinates; //list of subordinates
};

#endif //LABA_1_OOP_PERSON_H
