#include <string>
#include <map>

std::string encode(const std::string& text);
std::string decode(const std::string& encoded, std::map<char, std::string>& codes);
