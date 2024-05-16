/************************************************************************
 * file: Database.h
 * Database class definition
 * written: 28/02/2021
 * created by Vlad Seletkov
*************************************************************************/

#ifndef LABA_1_OOP_DATABASE_H
#define LABA_1_OOP_DATABASE_H

#include "Person.h"

class Database {
public:
	Database() {}
	~Database() {}
	bool LoadFromFile(const char *file); //creates “flat” database
	//struct of file:
	//0 – employee, 1 – manager;
	//Id;
	//First name;
	//Last name;
	//Age;
	//Department;
	//Salary
	void ArrangeSubordinates(); //arranges "flat" database after loading from the file
	Person* HireEmployee(Person *p); //hire a new employee
	void DisplayDepartmentEmployees(string _department);
	bool FireEmployee(int id); //fire the employee
	void DisplayAll();
	void DeleteDatabase();
	void ShowRecordSet(vector <Person*> rs);
	vector <Person*> SQL(const string field, const string cond, const string value); 
	// possible field: department; salary; id; age
	// possible cond: 
	// “gt” – greater than;
	// “lt” – less than;
	// “eq” – equal.
private:
	vector <Person*> employees;
	bool IsDigit(const string value);
};

#endif //LABA_1_OOP_DATABASE_H
