/************************************************************************
* file: Database.cpp
* These functions are declared in the include file "Database.h".
* related files: none
* author: Vlad Seletkov
* written: 28/02/2021
* last modified: 28/03/2021
************************************************************************/

#include "Database.h"
#pragma warning(disable : 6387)

bool Database::LoadFromFile(const char *file) {
	if (file == nullptr) {
		cout << "LoadFromFile() file nullptr error" << endl;
		return false;
	}
	std::ifstream in_file;
	in_file.open(file, std::ifstream::in);
	if (!in_file.is_open()) {
		cout << "LoadFromFile() !in_file.is_open() error" << endl;
		return false;
	}
	bool first_el_flag = false;
	char temp[256] = { 0 };
	while (1) {
		in_file.getline(temp, 256);
		if (in_file.eof())
			break;
		char *str = nullptr;
		int type = -1;
		str = strtok(temp, ";\n\0");
		if (str == nullptr || ((stoi(static_cast<string>(str)) != 1) && (stoi(static_cast<string>(str)) != 0))) {
			cout << "LoadFromFile() str == nullptr || atoi(str) != 1 || atoi(str) != 0 error" << endl;
			in_file.close();
			return false;
		}
		type = stoi(static_cast<string>(str));
		string f_name, l_name, department;
		int id = -1, age = -1, salary = -1;
		str = strtok(nullptr, ";\n\0");
		if (str == nullptr || stoi(static_cast<string>(str)) < 0) {
			cout << "LoadFromFile() str == nullptr || atoi(str) <= 0 error" << endl;
			in_file.close();
			return false;
		}
		id = stoi(static_cast<string>(str));
		str = strtok(nullptr, ";\n\0");
		if (str == nullptr || strlen(str) == 0) {
			cout << "LoadFromFile() str == nullptr || strlen(str) == 0 error" << endl;
			in_file.close();
			return false;
		}
		f_name = str;
		str = strtok(nullptr, ";\n\0");
		if (str == nullptr || strlen(str) == 0) {
			cout << "LoadFromFile() str == nullptr || strlen(str) == 0 error" << endl;
			in_file.close();
			return false;
		}
		l_name = str;
		str = strtok(nullptr, ";\n\0");
		if (str == nullptr || stoi(static_cast<string>(str)) <= 0) {
			cout << "LoadFromFile() str == nullptr || atoi(str) <= 0 error" << endl;
			in_file.close();
			return false;
		}
		age = stoi(static_cast<string>(str));
		str = strtok(nullptr, ";\n\0");
		if (str == nullptr || strlen(str) == 0) {
			cout << "LoadFromFile() str == nullptr || strlen(str) == 0 error" << endl;
			in_file.close();
			return false;
		}
		department = str;
		str = strtok(nullptr, ";\n\0");
		if (str == nullptr || stoi(static_cast<string>(str)) <= 0) {
			cout << "LoadFromFile() str == nullptr || atoi(str) <= 0 error" << endl;
			in_file.close();
			return false;
		}
		salary = stoi(static_cast<string>(str));

		Employee *cast_emp = nullptr;
		Manager *cast_man = nullptr;
		Employee emp_tmp;
		Manager man_tmp;
		bool flag = false;
		if (type == 0) {
			cast_emp = new Employee(f_name, l_name, age, id);
			cast_emp->SetDepartment(department);
			cast_emp->SetSalary(salary);
			if (this->employees.empty() && cast_emp != nullptr)
				this->employees.push_back(dynamic_cast<Person*>(cast_emp));
		}
		else if (type == 1) {
			cast_man = new Manager(f_name, l_name, age, id);
			cast_man->SetDepartment(department);
			cast_man->SetSalary(salary);
			if (this->employees.empty() && cast_man != nullptr)
				this->employees.push_back(dynamic_cast<Person*>(cast_man));
		}
		else {
			cout << "LoadFromFile() type != 0 && type != 1 error" << endl;
			delete cast_emp;
			delete cast_man;
			in_file.close();
			return false;
		}
		for (vector <Person*>::const_iterator iter = this->employees.cbegin(); iter != this->employees.end(); iter++) {
			if (first_el_flag == false) {
				first_el_flag = true;
				flag = true;
				break;
			}
			if (typeid(**iter) == typeid(Manager)) {
				man_tmp = *(dynamic_cast<Manager*>(*iter));
				if (type == 1 && cast_man != nullptr)
					if (man_tmp.GetId() == cast_man->GetId()) {
						flag = true;
						delete cast_man;
						break;
						cout << "LoadFromFile() (emp_tmp.GetId() == cast_man->GetId()) || (man_tmp.GetId() == cast_man->GetId()) error" << endl;
						return false;
					}
			} 
			else if (typeid(**iter) == typeid(Employee)) {
				emp_tmp = *(dynamic_cast<Employee*>(*iter));
				if (type == 0 && cast_emp != nullptr)
					if (emp_tmp.GetId() == cast_emp->GetId()) {
						flag = true;
						delete cast_emp;
						break;
						cout << "LoadFromFile() (emp_tmp.GetId() == cast_emp->GetId()) || (man_tmp.GetId() == cast_emp->GetId()) error" << endl;
						return false;
					}
			}
		}
		if (flag == false) {
			if (cast_emp != nullptr)
				this->employees.push_back(dynamic_cast<Person*>(cast_emp));
			else if (cast_man != nullptr)
				this->employees.push_back(dynamic_cast<Person*>(cast_man));
		}
	}
	in_file.close();
	return true;
}

void Database::ArrangeSubordinates() {
	if (this->employees.empty()) {
		cout << "ArrangeSubordinates() employees.empty() error" << endl;
		return;
	}
	Manager* m_tmp = nullptr;
	Employee* e_tmp = nullptr;
	for (vector <Person*>::iterator i = this->employees.begin(); i != this->employees.end(); i++) 
		if (typeid(**i) == typeid(Manager)) {
			m_tmp = new Manager(*(dynamic_cast<Manager*>(*i)));
			for (vector <Person*>::iterator j = this->employees.begin(); j != this->employees.end(); j++)
				if (typeid(**j) == typeid(Employee)) {
					e_tmp = new Employee(*(dynamic_cast<Employee*>(*j)));
					if (e_tmp != nullptr) {
						if (e_tmp->GetDepartment() == m_tmp->GetDepartment())
							m_tmp->AddSubordinate(dynamic_cast<Person*>(e_tmp));
						else
							delete e_tmp;
					}
				}
			if (m_tmp != nullptr) {
				delete *i;
				*i = dynamic_cast<Person*>(m_tmp);
			}
		}
}

Person *Database::HireEmployee(Person *p) {
	if (p == nullptr || this->employees.empty()) {
		cout << "HireEmployee(Person *p) p == nullptr || this->employees.empty() error" << endl;
		return nullptr;
	}

	bool f_id = false;
	Employee e_p;
	Manager m_p;
	Employee e_tmp;
	Manager m_tmp;
	if (typeid(*p) == typeid(Employee)) {
		e_p = *(dynamic_cast<Employee*>(p));
	}
	else if (typeid(*p) == typeid(Manager)) {
		m_p = *(dynamic_cast<Manager*>(p));
	}
	for (unsigned int i = 0; i < this->employees.size(); i++) {
		if (typeid(*this->employees.at(i)) == typeid(Manager)) {
			m_tmp = *(dynamic_cast<Manager*>(this->employees.at(i)));
			if (m_p.GetId() == m_tmp.GetId()) {
				f_id = true;
				break;
			}
		}
		else if (typeid(*this->employees.at(i)) == typeid(Employee)) {
			e_tmp = *(dynamic_cast<Employee*>(this->employees.at(i)));
			if (e_p.GetId() == e_tmp.GetId()) {
				f_id = true;
				break;
			}
		}
	}
	if (f_id == false) {
		this->employees.push_back(p);
		return this->employees.back();
	}
	else {
		cout << "HireEmployee(Person *p) .GetId() == .GetId() error" << endl;
		delete p;
		return nullptr;
	}
}

void Database::DisplayDepartmentEmployees(string _department) {
	if (this->employees.empty() || _department.empty()) {
		cout << "ArrangeSubordinates() employees.empty() || _department.empty() error" << endl;
		return;
	}
	Manager *m_tmp = nullptr;
	Employee *e_tmp = nullptr;
	for (unsigned int i = 0; i < this->employees.size(); i++) {
		if (typeid(*this->employees.at(i)) == typeid(Manager)) {
			m_tmp = new Manager(*(dynamic_cast<Manager*>(this->employees.at(i))));
			if (m_tmp != nullptr) 
				if (m_tmp->GetDepartment() == _department) {
					m_tmp->Display(false);
					m_tmp->DisplaySubordinatesByDepartment(_department);
					delete m_tmp;
				}
		}
		else if (typeid(*this->employees.at(i)) == typeid(Employee)) {
			e_tmp = new Employee(*(dynamic_cast<Employee*>(this->employees.at(i))));
			if (e_tmp != nullptr) 
				if (e_tmp->GetDepartment() == _department) {
					e_tmp->Display(false);
					delete e_tmp;
				}
		}
	}
	cout << endl;
}

bool Database::FireEmployee(int id) {
	if (id < 0 || this->employees.empty()) {
		cout << "FireEmployee(int id) id || this->employees.empty() < 0 error" << endl;
		return false;
	}
	Manager *m_p = nullptr;
	Employee *e_p = nullptr;
	for (vector <Person*>::iterator iter = this->employees.begin(); iter != this->employees.end(); iter++) {
		if (typeid(**iter) == typeid(Employee)) {
			e_p = dynamic_cast<Employee*>(*iter);
			if (e_p != nullptr)
				if (e_p->GetId() == id) {
					for (vector <Person*>::iterator iter2 = this->employees.begin(); iter2 != this->employees.end(); iter2++)
						if (typeid(**iter2) == typeid(Manager)) {
							m_p = dynamic_cast<Manager*>(*iter2);
							if (m_p != nullptr) 
								m_p->EraseSubordinateById(id);
						}
					if (iter == this->employees.begin()) {
						delete *iter;
						this->employees.erase(iter);
						if (!this->employees.empty())
							iter = this->employees.begin();
						else
							break;
					}
					else {
						delete *iter;
						iter = this->employees.erase(iter);
						iter--;
					}
				}
		}
		else if (typeid(**iter) == typeid(Manager)) {
			m_p = dynamic_cast<Manager*>(*iter);
			if (m_p != nullptr)
				if (m_p->GetId() == id) {
					m_p->DeleteSubordinates();
					if (iter == this->employees.begin()) {
						delete *iter;
						this->employees.erase(iter);
						if (!this->employees.empty())
							iter = this->employees.begin();
						else
							break;
					}
					else {
						delete *iter;
						iter = this->employees.erase(iter);
						iter--;
					}
				}
		}
	}
	return true;
}

void Database::DisplayAll() {
	if (this->employees.empty()) {
		cout << "DisplayAll() employees.empty() error" << endl;
		return;
	}
	for (unsigned int i = 0; i < this->employees.size(); i++) {
		this->employees.at(i)->Display(false);
		if (typeid(*(this->employees.at(i))) == typeid(Manager)) {
			Manager m_tmp(*(dynamic_cast<Manager*>(this->employees.at(i))));
			m_tmp.DisplaySubordinates();
		}
	}
	cout << endl;
}

void Database::DeleteDatabase() {
	if (this->employees.empty()) {
		cout << "DeleteDatabase() this->employees.empty() error" << endl;
		return;
	}
	for (unsigned int i = 0; i < this->employees.size(); i++) {
		if (typeid(*this->employees.at(i)) == typeid(Manager)) {
			Manager *m = dynamic_cast<Manager*>(this->employees.at(i));
			m->DeleteSubordinates();
		}
		delete this->employees.at(i);
	}
	this->employees.clear();
}

vector<Person*> Database::SQL(const string field, const string cond, const string value) {
	if (this->employees.empty() || field.empty() || cond.empty() || value.empty()) {
		cout << "SQL() this->employees.empty() || field.empty() || cond.empty() || value.empty() error" << endl;
		return vector<Person*>();
	}
	vector<Person*> sql;
	Employee *cast_emp = nullptr;
	Manager *cast_man = nullptr;
	for (vector <Person*>::iterator iter = this->employees.begin(); iter != this->employees.end(); iter++) {
		if (typeid(**iter) == typeid(Manager)) 
			cast_man = new Manager(*(dynamic_cast<Manager*>(*iter)));
		else if (typeid(**iter) == typeid(Employee)) 
			cast_emp = new Employee(*(dynamic_cast<Employee*>(*iter)));
		if ("department" == field) {
			bool flag = true;
			std::locale loc;
			for (unsigned int i = 0; i < value.size(); i++)
				if (isdigit(value.at(i), loc)) {
					flag = false;
					break;
				}
			if (flag == true) {
				if ("gt" == cond) {
					if (typeid(**iter) == typeid(Manager)) {
						if (cast_man->GetDepartment() > value)
							sql.push_back(dynamic_cast<Person*>(cast_man));
					}
					else if (typeid(**iter) == typeid(Employee))
						if (cast_emp->GetDepartment() > value)
							sql.push_back(dynamic_cast<Person*>(cast_emp));
				}
				else if ("lt" == cond) {
					if (typeid(**iter) == typeid(Manager)) {
						if (cast_man->GetDepartment() < value)
							sql.push_back(dynamic_cast<Person*>(cast_man));
					}
					else if (typeid(**iter) == typeid(Employee))
						if (cast_emp->GetDepartment() < value)
							sql.push_back(dynamic_cast<Person*>(cast_emp));
				}
				else if ("eq" == cond) {
					if (typeid(**iter) == typeid(Manager)) {
						if (cast_man->GetDepartment() == value)
							sql.push_back(dynamic_cast<Person*>(cast_man));
					}
					else if (typeid(**iter) == typeid(Employee))
						if (cast_emp->GetDepartment() == value)
							sql.push_back(dynamic_cast<Person*>(cast_emp));
				}
				else {
					if (typeid(**iter) == typeid(Manager))
						delete cast_man;
					else if (typeid(**iter) == typeid(Employee))
						delete cast_emp;
					cout << "SQL() const string cond != gt, lt, eq error" << endl;
					return vector<Person*>();
				}
			}
			else {
				if (typeid(**iter) == typeid(Manager))
					delete cast_man;
				else if (typeid(**iter) == typeid(Employee))
					delete cast_emp;
				cout << "SQL() const string value has digit error" << endl;
				return vector<Person*>();
			}
		}
		else if ("salary" == field) {
			if (IsDigit(value) == true) {
				if ("gt" == cond) {
					if (typeid(**iter) == typeid(Manager)) {
						if (cast_man->GetSalary() > stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_man));
					}
					else if (typeid(**iter) == typeid(Employee))
						if (cast_emp->GetSalary() > stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_emp));
				}
				else if ("lt" == cond) {
					if (typeid(**iter) == typeid(Manager)) {
						if (cast_man->GetSalary() < stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_man));
					}
					else if (typeid(**iter) == typeid(Employee))
						if (cast_emp->GetSalary() < stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_emp));
				}
				else if ("eq" == cond) {
					if (typeid(**iter) == typeid(Manager)) {
						if (cast_man->GetSalary() == stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_man));
					}
					else if (typeid(**iter) == typeid(Employee))
						if (cast_emp->GetSalary() == stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_emp));
				}
				else {
					if (typeid(**iter) == typeid(Manager))
						delete cast_man;
					else if (typeid(**iter) == typeid(Employee))
						delete cast_emp;
					cout << "SQL() const string cond != gt, lt, eq error" << endl;
					return vector<Person*>();
				}
			}
			else {
				if (typeid(**iter) == typeid(Manager))
					delete cast_man;
				else if (typeid(**iter) == typeid(Employee))
					delete cast_emp;
				cout << "SQL() const string value not digit error" << endl;
				return vector<Person*>();
			}
		}
		else if ("id" == field) {
			if (IsDigit(value) == true) {
				if ("gt" == cond) {
					if (typeid(**iter) == typeid(Manager)) {
						if (cast_man->GetId() > stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_man));
					}
					else if (typeid(**iter) == typeid(Employee))
						if (cast_emp->GetId() > stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_emp));
				}
				else if ("lt" == cond) {
					if (typeid(**iter) == typeid(Manager)) {
						if (cast_man->GetId() < stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_man));
					}
					else if (typeid(**iter) == typeid(Employee))
						if (cast_emp->GetId() < stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_emp));
				}
				else if ("eq" == cond) {
					if (typeid(**iter) == typeid(Manager)) {
						if (cast_man->GetId() == stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_man));
					}
					else if (typeid(**iter) == typeid(Employee))
						if (cast_emp->GetId() == stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_emp));
				}
				else {
					if (typeid(**iter) == typeid(Manager))
						delete cast_man;
					else if (typeid(**iter) == typeid(Employee))
						delete cast_emp;
					cout << "SQL() const string cond != gt, lt, eq error" << endl;
					return vector<Person*>();
				}
			}
			else {
				if (typeid(**iter) == typeid(Manager))
					delete cast_man;
				else if (typeid(**iter) == typeid(Employee))
					delete cast_emp;
				cout << "SQL() const string value not digit error" << endl;
				return vector<Person*>();
			}
		}
		else if ("age" == field) {
			if (IsDigit(value) == true) {
				if ("gt" == cond) {
					if (typeid(**iter) == typeid(Manager)) {
						if (cast_man->GetAge() > stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_man));
					}
					else if (typeid(**iter) == typeid(Employee))
						if (cast_emp->GetAge() > stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_emp));
				}
				else if ("lt" == cond) {
					if (typeid(**iter) == typeid(Manager)) {
						if (cast_man->GetAge() < stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_man));
					}
					else if (typeid(**iter) == typeid(Employee))
						if (cast_emp->GetAge() < stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_emp));
				}
				else if ("eq" == cond) {
					if (typeid(**iter) == typeid(Manager)) {
						if (cast_man->GetAge() == stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_man));
					}
					else if (typeid(**iter) == typeid(Employee))
						if (cast_emp->GetAge() == stoi(value))
							sql.push_back(dynamic_cast<Person*>(cast_emp));
				}
				else {
					if (typeid(**iter) == typeid(Manager))
						delete cast_man;
					else if (typeid(**iter) == typeid(Employee))
						delete cast_emp;
					cout << "SQL() const string cond != gt, lt, eq error" << endl;
					return vector<Person*>();
				}
			}
			else {
				if (typeid(**iter) == typeid(Manager))
					delete cast_man;
				else if (typeid(**iter) == typeid(Employee))
					delete cast_emp;
				cout << "SQL() const string value not digit error" << endl;
				return vector<Person*>();
			}
		}
		else {
			if (typeid(**iter) == typeid(Manager))
				delete cast_man;
			else if (typeid(**iter) == typeid(Employee))
				delete cast_emp;
			cout << "SQL() const string field != dep, salary, id, age error" << endl;
			return vector<Person*>();
		}
	}
	return vector<Person*>(sql);
}

bool Database::IsDigit(const string value)
{
	bool flag = true;
	std::locale loc;
	for (unsigned int i = 0; i < value.size(); i++)
		if (!isdigit(value.at(i), loc)) {
			flag = false;
			break;
		}
	return flag;
}

void Database::ShowRecordSet(vector<Person*> rs) {
	if (rs.empty()) {
		cout << "ShowRecordSet() rs.empty() error" << endl;
		return;
	}
	for (unsigned int i = 0; i < rs.size(); i++) {
		rs.at(i)->Display(false);
		if (typeid(*(rs.at(i))) == typeid(Manager)) {
			Manager m_tmp(*(dynamic_cast<Manager*>(rs.at(i))));
			m_tmp.DisplaySubordinates();
		}
	}
	cout << endl;
}
