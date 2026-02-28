#include "Employee.h"
#include <stdexcept>

Employee::Employee(std::string name, int id) : name(std::move(name)), id(id) {
    if (id < 0) {
        throw std::invalid_argument("Employee ID cannot be negative.");
    }
}

void Employee::displayInfo() const {
    std::cout << "ID: " << id << '\n';
    std::cout << "Name: " << name << '\n';
}

int Employee::getId() const {
    return id;
}