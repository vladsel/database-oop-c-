#include "Database.h"

int main() {
	Database db;

	vector <Person*> vec;

	Employee *emp = new Employee("Ladyslav", "Corax", 23, 10);
	emp->SetDepartment("PR");
	emp->SetSalary(400);

	if (!db.LoadFromFile("file.csv")) {
		cout << "LoadFromFile() error" << endl;
		exit(1);
	}	

	db.ArrangeSubordinates();
	db.DisplayAll();

	cout << "\nhire employee: " << endl;
	(db.HireEmployee(dynamic_cast<Person*>(emp)))->Display(false);

	if (db.FireEmployee(5))
		cout << "\nfire employee id: 5 " << endl;

	cout << "\n\n\n\n";
	db.ArrangeSubordinates();
	db.DisplayAll();

	cout << "\n\n\n\nby department: \n";
	db.DisplayDepartmentEmployees("PR");

	cout << "\n\n\n\nnew vector by condition: \n";
	vec = db.SQL("age", "lt", "30");
	db.ShowRecordSet(vec);

	db.DeleteDatabase();
	return 0;


	/*Database db;
	db.LoadFromFile("file.csv");
	Manager *tmgr = new Manager("John", "Smith", 50, 70);
	Employee *te = new Employee("Joe", "Doe", 20, 71);

	tmgr->SetSalary(2000);
	te->SetSalary(1800);

	tmgr->SetDepartment("Dept3");
	te->SetDepartment("Dept3");

	db.HireEmployee(tmgr);
	db.HireEmployee(te);
	db.ArrangeSubordinates();

	auto tr = db.SQL("id", "eq", "71");
	for (auto p : tr) {
		auto ep = dynamic_cast<Employee*>(p);
		if (ep) {
			ep->SetSalary(1000000);
			std::cout << "Modified:" << std::endl;
			ep->Display(true);
			std::cout << "==============" << std::endl;
		}
		else {
			std::cout << "Cast error" << std::endl;
		}
	}
	

	db.DisplayDepartmentEmployees("Dept3");

	cout << "\n\n\n";
	db.ShowRecordSet(tr);*/

	//Database db;
	//db.LoadFromFile("file.csv");
	//int id = 100;
	//for (size_t iter = 0; iter < 100000000; ++iter)
	//{
	//	int mid = id++;
	//	int eid1 = id++;
	//	int eid2 = id++;

	//	Manager* mgr = new Manager("John", "Smith", 50, mid);
	//	Employee* e1 = new Employee("Joe", "Doe", 20, eid1);
	//	Employee* e2 = new Employee("Jimm", "Roe", 30, eid2);

	//	mgr->SetDepartment("SomeDept");
	//	e1->SetDepartment("SomeDept");
	//	e2->SetDepartment("SomeDept");

	//	db.HireEmployee(dynamic_cast<Person*>(mgr));
	//	db.HireEmployee(e1);
	//	db.HireEmployee(e2);
	//	db.ArrangeSubordinates();

	//	db.FireEmployee(eid1);
	//	db.FireEmployee(eid2);
	//	db.FireEmployee(mid);
	//}
}
