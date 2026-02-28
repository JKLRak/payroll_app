#include "SalariedEmployee.h"
#include <stdexcept>

SalariedEmployee::SalariedEmployee(std::string name, int id, double weekly_salary) 
    : Employee(std::move(name), id), weekly_salary(weekly_salary) {
        if (weekly_salary < 0) {
            throw std::invalid_argument("Salary cannot be negative.");
        }
    }

void SalariedEmployee::setWeeklySalary(double new_salary) {
    if (new_salary < 0) throw std::invalid_argument("Salary cannot be negative");
    weekly_salary = new_salary;
}

double SalariedEmployee::calculatePay() const {
    return weekly_salary;
}

void SalariedEmployee::displayInfo() const {
    Employee::displayInfo();
    std::cout << "Weekly salary: " << weekly_salary << '\n';
    std::cout << "Total pay: " << calculatePay() << '\n';
}

EmployeeType SalariedEmployee::getType() const { return EmployeeType::Salaried; }
