#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include <array>
#include "lib.h"

IpAddr::IpAddr(std::string addr) {
	int start = 0;
	for (int i = 0; i < octet.size(); i++) {
		int stop = addr.find_first_of('.', start);
		if(stop != std::string::npos){
			octet[i] = std::stoi(addr.substr(start, stop));
			start = stop + 1;
		} else {
			octet[i] = std::stoi(addr.substr(start, addr.size()));
		}
	}
}

std::ostream& operator << (std::ostream &out, const IpAddr& me) {
	std::string output = "";
	for(int i = 0; i < me.octet.size(); i++) {
		output.append(std::to_string(int(me.octet[i])));
		output.push_back('.');
	}
	out << output.substr(0, output.size() - 1);
	
	return out;
}

std::string IpAddr::to_str() {
	std::string output = "";
	for(int i = 0; i < octet.size(); i++) {
		output.append(std::to_string(int(octet[i])));
		output.push_back('.');
	}
	output.pop_back();
	return output;
}

bool IpAddr::any_octet_eq(uint8_t val) const {
    for(int i = 0; i < octet.size(); i++) {
		if (octet[i] == val) {
			return true;
		}
	}
	return false;
}

bool IpAddr::operator<(const IpAddr& right) const {
	for(int i = 0; i < octet.size(); i++) {
		if (octet[i] == right.octet[i]){
			continue;
		} 
		return (octet[i] < right.octet[i]);
	}
	return false;
}
