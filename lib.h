#pragma once
#include <array>
#include <cstdint>

struct IpAddr {
	std::array<uint8_t, 4> octet;

	IpAddr(std::string addr);
	std::string to_str();
	friend std::ostream& operator << (std::ostream &out, const IpAddr& me); 
	bool operator <(const IpAddr& right) const;
	bool operator >(const IpAddr& right) const;
	bool any_octet_eq(uint8_t val) const;
};
