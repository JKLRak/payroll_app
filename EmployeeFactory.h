#pragma once
#include <string>
#include <memory>
#include "Employee.h"

constexpr double DEFAULT_NORMAL_HOURS_WORKED = 0.0;
constexpr double DEFAULT_OVERTIME_RATE = 0.0;
constexpr double DEFAULT_OVERTIME_HOURS = 0.0;

class EmployeeFactory {
public:
    static std::unique_ptr<Employee> createEmployee(
        const std::string& type, 
        std::string name, 
        int id, 
        double param1, // Could be salary or normal_hourly_rate
        double param2 = DEFAULT_NORMAL_HOURS_WORKED,
        double param3 = DEFAULT_OVERTIME_RATE,
        double param4 = DEFAULT_OVERTIME_HOURS
    );
};