#include "EmployeeFactory.h"
#include "SalariedEmployee.h"
#include "HourlyEmployee.h"
#include <memory>

std::unique_ptr<Employee> EmployeeFactory::createEmployee(
    const std::string& type, std::string name, int id, 
    double param1, double param2, double param3, double param4) {
    
    if (type == "Salaried") {
        return std::make_unique<SalariedEmployee>(std::move(name), id, param1);
    } 
    else if (type == "Hourly") {
        return std::make_unique<HourlyEmployee>(std::move(name), id, param1, param2, param3, param4);
    }
    
    throw std::invalid_argument("Unknown Employee Type: " + type);
}