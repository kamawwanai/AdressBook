#include <iostream>
#include <string>
#include "adressbook.h"

using namespace std::string_literals;

bool is_number(const std::string& s);

void add_command(AdressBook& a);

void find_command(AdressBook& a);

void remove_command(AdressBook& a);

void help_command();

int main() {
	AdressBook a;

	while (true) {
		std::string command; std::cin >> command;
		if (command == "add"s)
			add_command(a);
		else if (command == "find"s)
			find_command(a);
		else if (command == "remove"s)
			remove_command(a);
		else if (command == "clear"s)
			a.clear();
		else if (command == "help"s)
			help_command();
		else if (command == "exit"s) {
			std::cout << "Bye bye!" << std::endl;
			break;
		}
		else
			std::cout << "try help command for usage information" << std::endl;
	}

	return 0;
}

bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(), s.end(),
		[](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void add_command(AdressBook& a) {
	uint32_t id; std::string name; uint16_t grade;
	std::cin >> id >> name >> grade;
	if (a.find_by_id(id).has_value()) {
		throw std::runtime_error("Employee with such id already exists");
	}
	else if (is_number(name)) {
		throw std::runtime_error("Invalid name with numbers");
	}
	Employee employee(id, name, grade);
	a.add(employee);
}

void find_command(AdressBook& a) {
	std::string param; std::cin >> param;
	if (is_number(param)) {
		auto found_employee = a.find_by_id(std::stoi(param));
		//std::cout << found_employee.value_or<std::string>("No such employee in adressbook") << std::endl;
		if (found_employee.has_value()) {
			std::cout << found_employee.value() << std::endl;
		}
		else {
			std::cout << "No such employee in adressbook" << std::endl;
		}
	}
	else {
		auto found_employee = a.find_by_name(param);
		//std::cout << found_employee.value_or<std::string>("No such employee in adressbook") << std::endl;
		if (found_employee.has_value()) {
			std::cout << found_employee.value() << std::endl;
		}
		else {
			std::cout << "No such employee in adressbook" << std::endl;
		}
	}
}

void remove_command(AdressBook& a) {
	std::string param; std::cin >> param;
	if (is_number(param)) {
		a.delete_by_id(std::stoi(param));
	}
	else {
		a.delete_by_name(param);
	}
}

void help_command() {
	std::cout << "Try: <command> [args]." << std::endl
		<< "Available commands:" << std::endl
		<< "\tadd" << std::endl
		<< "\tArguments:" << std::endl
		<< "\t\tid (unique number)" << std::endl
		<< "\t\tname (string not number)" << std::endl
		<< "\t\tgrade (number)" << std::endl
		<< "\tDescription: add employee with specified data." << std::endl
		<< "\tCan throw exception if employee with such id is exists." << std::endl
		<< std::endl
		<< "\tfind" << std::endl
		<< "\tArguments:" << std::endl
		<< "\t\tid or name" << std::endl
		<< "\tDescription: find employee by id or name and print info about him" << std::endl
		<< std::endl
		<< "\tremove" << std::endl
		<< "\tArguments:" << std::endl
		<< "\t\tid or name" << std::endl
		<< "\tDescription: remove employee by id or name" << std::endl
		<< std::endl
		<< "\tclear" << std::endl
		<< "\tDescription: clears all adressbook" << std::endl
		<< std::endl
		<< "\texit" << std::endl
		<< "\tDescription: stop programm" << std::endl
		<< std::endl;
}