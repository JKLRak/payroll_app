#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "Employee.h" 
class Company {
private:
    // Maps from id to employee
    std::unordered_map<int, std::unique_ptr<Employee>> employees;
public:
    void loadFromFile(const std::string& filename);
    void addEmployee(std::unique_ptr<Employee> emp);
    void processPayroll() const;
    bool editEmployee(int id, double new_normal_rate = -1, double new_overtime_rate = -1, double new_salary = -1);
};
