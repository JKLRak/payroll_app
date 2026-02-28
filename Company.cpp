#include "Company.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include "Employee.h" 
#include "HourlyEmployee.h"
#include "SalariedEmployee.h"
#include "EmployeeFactory.h"

void Company::addEmployee(std::unique_ptr<Employee> emp) {
    if (!emp) return; // Safety check for null pointer
    int new_id = emp->getId();

    if (employees.find(new_id) != employees.end()) {
        throw std::invalid_argument("Duplicate Employee ID detected: " + std::to_string(new_id));
    }

    employees[new_id] = std::move(emp);
}

// Function that prints info about payroll in total and for each employee
void Company::processPayroll() const {
    double total_payroll = 0.0;
    
    std::cout << "       PROCESSING WEEKLY PAYROLL        \n";

    for (const auto& emp_pair : employees) {
        
        emp_pair.second->displayInfo(); 
        
        double pay = emp_pair.second->calculatePay(); 
        
        std::cout << "Weekly Payout: $" << pay << "\n";
        std::cout << "----------------------------------------\n";
        
        total_payroll += pay;
    }

    std::cout << "TOTAL COMPANY PAYROLL: $" << total_payroll << "\n";
}

// Loads employee info from file
void Company::loadFromFile(const std::string& filename) {
    std::ifstream file(filename); 
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    std::string line;
    int line_number = 0;

    while (std::getline(file, line)) {
        line_number++;
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> data;

        while (std::getline(ss, token, ',')) {
            data.push_back(token);
        }

        if(data.empty()) continue;

        if (data[0] == "Edit") {
            if (data.size() < 3) {
                std::cerr << "Skipping edit line " << line_number << ": Not enough data.\n";
                continue;
            }
            int id = std::stoi(data[1]);
            double new_normal_rate = -1;
            double new_overtime_rate = -1;
            double new_salary = -1;

            // For hourly: Edit,102,30.0,45.0
            // For salaried: Edit,101,1300.0
            if (data.size() == 3) {
                new_salary = std::stod(data[2]);
            } else if (data.size() >= 4) {
                new_normal_rate = std::stod(data[2]);
                new_overtime_rate = std::stod(data[3]);
            }
            editEmployee(id, new_normal_rate, new_overtime_rate, new_salary);
            continue;
        }
        else if (data.size() < 4) {
            std::cerr << "Skipping line " << line_number << ": Not enough data.\n";
            continue;
        }

        try {
            std::string type = data[0];
            std::string name = data[1];
            
            int id = std::stoi(data[2]);
            double param1 = std::stod(data[3]);
            
            double param2 = (data.size() > 4) ? std::stod(data[4]) : 0.0;
            double param3 = (data.size() > 5) ? std::stod(data[5]) : 0.0;
            double param4 = (data.size() > 6) ? std::stod(data[6]) : 0.0;

            addEmployee(EmployeeFactory::createEmployee(type, name, id, param1, param2, param3, param4));

        } catch (const std::exception& e) {
            std::cerr << "Error on line " << line_number << " (" << data[1] << "): " << e.what() << "\n";
        }
    }
    
    file.close();
    std::cout << "Successfully loaded employee data from " << filename << ".\n";
}


bool Company::editEmployee(int id, double new_normal_rate, double new_overtime_rate, double new_salary) {
    auto it = employees.find(id);
    if (it == employees.end()) {
        std::cerr << "Error: Employee ID " << id << " not found.\n";
        return false;
    }

    Employee* target_emp = it->second.get();

    // Logic for checking whether edit is trying to change correct type of employee
    if (target_emp->getType() == EmployeeType::Hourly) {
        if (new_salary >= 0) {
            std::cerr << "Error: Cannot set salary for hourly employee (ID " << id << ").\n";
            return false;
        }
        
        auto* hourly_emp = static_cast<HourlyEmployee*>(target_emp);
        if (new_normal_rate >= 0) hourly_emp->setNormalHourlyRate(new_normal_rate);
        if (new_overtime_rate >= 0) hourly_emp->setOvertimeHourlyRate(new_overtime_rate);

        std::cout << "Hourly rates updated!\n";

    } else if (target_emp->getType() == EmployeeType::Salaried) {
        if (new_normal_rate >= 0 || new_overtime_rate >= 0) {
            std::cerr << "Error: Cannot set hourly rates for salaried employee (ID " << id << ").\n";
            return false;
        }

        auto* salaried_emp = static_cast<SalariedEmployee*>(target_emp);
        if (new_salary >= 0) salaried_emp->setWeeklySalary(new_salary);
        std::cout << "Salary updated!\n";
    }

    return true;
}