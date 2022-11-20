#include "adressbook.h"
#include <iostream>

std::ostream& operator<<(std::ostream& o, const Employee& e) {
	o << "Info about employee" << std::endl;
	o << "Id: " << e.id << std::endl
		<< "Name: " << e.name << std::endl
		<< "Grade: " << e.grade << std::endl;
	return o;
}

auto AdressBook::get_have_required(uint32_t id) const {
	return [id](const Employee& employee) {return employee.id == id; };
}

auto AdressBook::get_have_required(const std::string name) const {
	return [name](const Employee& employee) {return employee.name == name; };
}

void AdressBook::add(const Employee& employee) {
	employees.push_front(employee);
}

std::optional<Employee> AdressBook::find_by_id(uint32_t id) {
	auto have_required_id = get_have_required(id);
	auto found_employee = std::find_if(employees.begin(), employees.end(), have_required_id);
	if (found_employee == employees.end()) {
		return std::nullopt;
	}
	return std::optional<Employee>(*found_employee);
}

std::optional<Employee> AdressBook::find_by_name(const std::string name) {
	auto have_required_name = get_have_required(name);
	auto found_employee = std::find_if(employees.begin(), employees.end(), have_required_name);
	if (found_employee == employees.end()) {
		return std::nullopt;
	}
	return std::optional<Employee>(*found_employee);
}

void AdressBook::delete_by_id(uint32_t id) {
	auto have_required_id = get_have_required(id);
	bool removed = employees.remove_if(have_required_id);
	if (!removed) {
		throw std::runtime_error("Can not find employee with required id");
	}
}

void AdressBook::delete_by_name(const std::string& name) {
	auto have_required_name = get_have_required(name);
	bool removed = employees.remove_if(have_required_name);
	if (!removed) {
		throw std::runtime_error("Can not find employee with required name");
	}
}

void AdressBook::clear() {
	employees.clear();
}