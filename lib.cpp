#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <array>
#include "lib.h"

IpAddr::IpAddr(const std::string addr) {
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
	out << me.to_str();
	return out;
}

std::string IpAddr::to_str() const {
	std::stringstream output;
	for(int i = 0; i < octet.size(); i++) {
		output << int(octet[i]);
		if (i != octet.size() - 1) {
			output << '.';
		}
	}
	return output.str();
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
	return (octet < right.octet);
}
