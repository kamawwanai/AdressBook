#pragma once

#include <cinttypes>
#include <string>
#include <forward_list>
#include <algorithm>
#include <stdexcept>
#include <optional>

struct Employee{
	uint32_t id;
	std::string name;
	uint16_t grade;

	Employee() : id(0), name("Undefined"), grade(0) {}
	Employee(uint32_t _id, const std::string& _name, uint16_t _grade) :
		id(_id), name(_name), grade(_grade) {}
};

std::ostream& operator<<(std::ostream& o, const Employee& e);

class AdressBook {
	std::forward_list<Employee> employees;

	auto get_have_required(uint32_t id) const;

	auto get_have_required(const std::string name) const;
public:
	
	void add(const Employee& employee);

	std::optional<Employee> find_by_id(uint32_t id);

	std::optional<Employee> find_by_name(const std::string name);

	void delete_by_id(uint32_t id);

	void delete_by_name(const std::string& name);

	void clear();
};