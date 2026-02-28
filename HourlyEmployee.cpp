#include "HourlyEmployee.h" 
#include <stdexcept>

constexpr double MIN_HOURLY_RATE = 0.0;
constexpr double MIN_OVERTIME_HOURLY_RATE = 0.0;

// Constructors
HourlyEmployee::HourlyEmployee(std::string name, int id, double normal_hourly_rate, double normal_hours_worked)
    : HourlyEmployee(std::move(name), id, normal_hourly_rate, normal_hours_worked, 0.0, 0.0) {}

HourlyEmployee::HourlyEmployee(std::string name, int id, double normal_hourly_rate, 
    double normal_hours_worked, double overtime_hourly_rate, double overtime_hours_worked) 
    : Employee(std::move(name), id),
      normal_hourly_rate(normal_hourly_rate),
      normal_hours_worked(normal_hours_worked), 
      overtime_hourly_rate(overtime_hourly_rate), 
      overtime_hours_worked(overtime_hours_worked) {
        if (normal_hourly_rate < MIN_HOURLY_RATE || normal_hours_worked < MIN_OVERTIME_HOURLY_RATE) {
            throw std::invalid_argument("Hourly rates and hours worked must be bigger than minimal wage.");
        }
        if (overtime_hourly_rate < normal_hourly_rate && overtime_hours_worked > 0) {
            throw std::invalid_argument("Overtime hourly rate must be higher than normal hourly");
        }
      }


// Methods allowing to set hourly or overtime rate
void HourlyEmployee::setNormalHourlyRate(double new_rate) {
    if (new_rate < MIN_HOURLY_RATE) {
        throw std::invalid_argument("Hourly rate cannot be smaller than minimum wage");
    }
    normal_hourly_rate = new_rate;
}

void HourlyEmployee::setOvertimeHourlyRate(double new_rate) {
    if (new_rate < MIN_OVERTIME_HOURLY_RATE) {
        throw std::invalid_argument("Overtime rate cannot be smaller than minimum wage");
    }
    overtime_hourly_rate = new_rate;
}

double HourlyEmployee::calculatePay() const {
    double normal_pay = normal_hourly_rate * normal_hours_worked;
    double overtime_pay = overtime_hourly_rate * overtime_hours_worked;
    return normal_pay + overtime_pay;
}

void HourlyEmployee::displayInfo() const {
    Employee::displayInfo();
    std::cout << "Normal hourly rate / hours worked " << normal_hourly_rate << " " << normal_hours_worked << '\n';
    std::cout << "Overtime hourly rate / hours worked: " << overtime_hourly_rate << " " << overtime_hours_worked << '\n';
    std::cout << "Total pay: " << calculatePay() << '\n';
}

EmployeeType HourlyEmployee::getType() const {
    return EmployeeType::Hourly; 
}
