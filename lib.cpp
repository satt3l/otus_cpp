#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <array>
#include <regex>
#include "lib.h"


IpAddr::IpAddr(const std::string addr) {
	int start = 0;
	int stop = -1;
	int value = 0;
	std::smatch match;
	std::regex ipv4_format("^(([0-9]{1,3}\\.){3}[0-9]{1,3})");
	if (!std::regex_search(addr, match, ipv4_format)) {
		throw IpAddrValidationError();
	}
	std::string ip = match.str(0);
	for (int i = 0; i < octet.size(); i++) {
		stop = ip.find_first_of('.', start);
		value = std::stoi(ip.substr(start, stop == std::string::npos ? addr.size() : stop));
		if (value > 255 || value < 0) {
			throw IpAddrValidationError();
		}
		octet[i] = value;
		start = stop + 1;
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
