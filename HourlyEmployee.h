#pragma once
#include "Employee.h"

// Special Class of Employee that gets paid per hour with overtime pay
class HourlyEmployee : public Employee {
private:
    double normal_hourly_rate;
    double normal_hours_worked;
    double overtime_hourly_rate;
    double overtime_hours_worked;
public:
    HourlyEmployee(std::string name, int id, double normal_hourly_rate, double normal_hours_worked);
    HourlyEmployee(std::string name, int id, double normal_hourly_rate, double normal_hours_worked,
        double overtime_hourly_rate, double overtime_hours_worked);
    
    double calculatePay() const override;
    void displayInfo() const override;
    
    void setNormalHourlyRate(double new_rate);
    void setOvertimeHourlyRate(double new_rate);

    EmployeeType getType() const override;
};