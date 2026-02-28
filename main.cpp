#include <iostream>
#include <cassert> 
#include "HourlyEmployee.h"
#include "SalariedEmployee.h"
#include "EmployeeFactory.h"
#include "Company.h"

// --- UNIT TESTS ---

void testPayCalculations() {
    // Basic Hourly Test
    HourlyEmployee alice("Alice", 1, 20.0, 40.0);
    assert(alice.calculatePay() == 800.0 && "Basic hourly pay math failed!");

    // Basic Overtime Math Test
    HourlyEmployee bob("Bob", 2, 20.0, 40.0, 30.0, 10.0);
    assert(bob.calculatePay() == 1100.0 && "Overtime pay math failed!");

    // Salaried Math Test
    SalariedEmployee charlie("Charlie", 3, 2500.0);
    assert(charlie.calculatePay() == 2500.0 && "Salaried pay math failed!");

    std::cout << "[TEST PASSED] Pay Calculations\n";
}

// Test checking if adding 2 employees with same id is caught
void testDuplicateIdValidation() {
    Company testCorp;
    
    testCorp.addEmployee(EmployeeFactory::createEmployee("Salaried", "Valid Employee", 100, 1000.0));

    bool caught_exception = false;
    try {
        testCorp.addEmployee(EmployeeFactory::createEmployee("Salaried", "Invalid Employee", 100, 1000.0));
    } catch (const std::invalid_argument& e) {
        caught_exception = true;
    }
    assert(caught_exception == true && "System failed to block a duplicate ID!");

    std::cout << "[TEST PASSED] Duplicate ID Validation\n";
}

// Test checking if adding employee of unkown type is caught
void testFactoryCreation() {
    bool caught_exception = false;
    try {
        auto ghost = EmployeeFactory::createEmployee("12492184214912", "Ghost", 404, 0);
    } catch (const std::invalid_argument& e) {
        caught_exception = true;
    }

    assert(caught_exception == true && "Factory failed to block invalid employee type!");
    
    std::cout << "[TEST PASSED] Factory Validation\n";
}

// MAIN LOOP

int main() {
    std::cout << "Tests Start\n";
    testPayCalculations();
    testDuplicateIdValidation();
    testFactoryCreation();
    std::cout << "Tests Passed\n";

    // Reads from line info about employees
    Company techCorp;
    techCorp.loadFromFile("employees.txt");

    techCorp.processPayroll();

    std::cout << "-------------------------------------------------\n";

    // Now reads 1 false and 1 correct change
    techCorp.loadFromFile("changes.txt");

    techCorp.processPayroll();

    return 0;
}