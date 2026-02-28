#pragma once
#include <string>
#include <iostream>

// Types of Employee
enum class EmployeeType {
     Hourly, 
     Salaried 
};

class Employee {
protected:
    std::string name;
    int id; // unique id of employee

public:
    Employee(std::string name, int id);
    virtual ~Employee() = default; 

    virtual double calculatePay() const = 0; 
    virtual EmployeeType getType() const = 0; // return type of employee e.g. Hourly
    virtual void displayInfo() const; 
    int getId() const;
};