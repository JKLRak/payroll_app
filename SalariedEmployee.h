#pragma once
#include "Employee.h"

class SalariedEmployee : public Employee {
private:
    double weekly_salary;

public:
    SalariedEmployee(std::string name, int id, double weekly_salary);
    
    double calculatePay() const override;
    void displayInfo() const override;
    
    void setWeeklySalary(double new_salary); 

    EmployeeType getType() const override;
};
