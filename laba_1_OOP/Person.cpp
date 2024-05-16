/************************************************************************
* file: Person.cpp
* These functions are declared in the include file "Person.h".
* related files: none
* author: Vlad Seletkov
* written: 28/02/2021
* last modified: 28/03/2021
************************************************************************/

#include "Person.h"

void Employee::Display(bool flag) {
	if (flag == false) {
		cout << "\nEmployment type: employee" << endl;
		cout << "id: " << this->id << endl;
		cout << this->f_name << " " << this->l_name << endl;
		cout << "age: " << this->age << endl;
		cout << "salary: " << this->salary << endl;
		cout << "department: " << this->department << endl;
	}
	else if (flag == true) {
		cout << "\t\tEmployment type: employee" << endl;
		cout << "\t\tid: " << this->id << endl;
		cout << "\t\t" << this->f_name << " " << this->l_name << endl;
		cout << "\t\tage: " << this->age << endl;
		cout << "\t\tsalary: " << this->salary << endl;
		cout << "\t\tdepartment: " << this->department << endl << endl;
	}
}

Manager::Manager(const Manager &m) {
	this->f_name = m.f_name;
	this->l_name = m.l_name;
	this->age = m.age;
	this->department = m.department;
	this->salary = m.salary;
	this->id = m.id;
	this->subordinates = m.subordinates;
}

void Manager::Display(bool flag) {
	if (flag == false) {
		cout << "\nEmployment type: manager" << endl;
		cout << "id: " << this->id << endl;
		cout << this->f_name << " " << this->l_name << endl;
		cout << "age: " << this->age << endl;
		cout << "salary: " << this->salary << endl;
		cout << "department: " << this->department << endl;
	}
	else if (flag == true) {
		cout << "\t\tEmployment type: manager" << endl;
		cout << "\t\tid: " << this->id << endl;
		cout << "\t\t" << this->f_name << " " << this->l_name << endl;
		cout << "\t\tage: " << this->age << endl;
		cout << "\t\tsalary: " << this->salary << endl;
		cout << "\t\tdepartment: " << this->department << endl << endl;
	}
}

Person *Manager::AddSubordinate(Person *p) {
	if (p == nullptr || (typeid(*p) != typeid(Employee))) {
		cout << "AddSubordinate() p == nullptr || (typeid(*p) != typeid(Employee)) error" << endl;
		return nullptr;
	}
	Employee e_p = *(dynamic_cast<Employee*>(p));
	Employee e_sub;
	bool flag = false;
	for (list <Person*>::const_iterator iter = this->subordinates.cbegin(); iter != this->subordinates.end(); iter++) {
		e_sub = *(dynamic_cast<Employee*>(*iter));
		if (e_sub.GetId() == e_p.GetId()) {
			flag = true;
			break;
		}
	}
	if (flag == false) {
		this->subordinates.push_back(p);
		return this->subordinates.back();
	}
	else {
		//cout << "AddSubordinate(Person *p) subbordinates.GetId() == p.GetId() error" << endl;
		delete p;
		return nullptr;
	}
}

void Manager::DisplaySubordinates() {
	if (this->subordinates.empty()) {
		cout << "\n\tSubbordinates:\n" << "\t\tnone" << endl;
		return;
	}
	bool flag = false;
	cout << "\n\tSubbordinates:" << endl;
	for (list <Person*>::const_iterator iter = this->subordinates.cbegin(); iter != this->subordinates.end(); iter++)
		(*iter)->Display(true);
}

void Manager::DisplaySubordinatesByDepartment(string _department) {
	if (this->subordinates.empty() || _department.empty()) {
		cout << "\n\tSubbordinates:\n" << "\t\tnone" << endl;
		return;
	}
	Employee emp;
	cout << "\n\tSubbordinates:" << endl;
	for (list <Person*>::const_iterator iter = this->subordinates.cbegin(); iter != this->subordinates.end(); iter++)
		if (typeid(**iter) == typeid(Employee)) {
			emp = *(dynamic_cast<Employee*>(*iter));
			if (emp.GetDepartment() == _department) 
				(*iter)->Display(true);
		}
}

void Manager::DeleteSubordinates() {
	if (this->subordinates.empty()) {
		//cout << "DeleteSubordinates() this->subordinates.empty() error" << endl;
		return;
	}
	for (list <Person*>::iterator iter = this->subordinates.begin(); iter != this->subordinates.end(); iter++)
		delete *iter;
	this->subordinates.clear();
}

void Manager::EraseSubordinateById(int id) {
	if (id < 0 || this->subordinates.empty()) {
		//cout << "DeleteSubordinates() id < 0 || this->subordinates.empty() error" << endl;
		return;
	}
	Employee *e_p = nullptr;
	for (list <Person*>::iterator iter = this->subordinates.begin(); iter != this->subordinates.end(); iter++)
		if (typeid(**iter) == typeid(Employee)) {
			e_p = dynamic_cast<Employee*>(*iter);
			if (e_p != nullptr)
				if (e_p->GetId() == id) {
					if (iter == this->subordinates.begin()) {
						delete *iter;
						this->subordinates.pop_front();
						if (!this->subordinates.empty())
							iter = this->subordinates.begin();
						else
							break;
					}
					else {
						delete *iter;
						iter = this->subordinates.erase(iter);
						iter--;
					}
				}
		}
}

Employee::Employee(const Employee &e) {
	this->f_name = e.f_name;
	this->l_name = e.l_name;
	this->age = e.age;
	this->department = e.department;
	this->salary = e.salary;
	this->id = e.id;
}

Employee &Employee::operator=(const Employee &e)
{
	this->f_name = e.f_name;
	this->l_name = e.l_name;
	this->age = e.age;
	this->department = e.department;
	this->salary = e.salary;
	this->id = e.id;
	return *this;
}

void Employee::SetSalary(int s) {
	if (s < 0) {
		cout << "SetSalary() s < 0 error" << endl;
		return;
	}
	this->salary = s;
}

void Employee::SetDepartment(string dept) {
	if (dept.empty() == true) {
		cout << "SetDepartment() dept.empty() == true error" << endl;
		return;
	}
	this->department = dept;
}

void Employee::SetId(int n) {
	if (n < 0) {
		cout << "SetId() n < 0 error" << endl;
		return;
	}
	this->id = n;
}

int Employee::GetSalary() {
	return this->salary;
}

string Employee::GetDepartment() {
	return this->department;
}

int Employee::GetId() {
	return this->id;
}

int Person::GetAge() {
	return this->age;
}
