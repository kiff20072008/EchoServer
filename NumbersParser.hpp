#ifndef _NUMBER_PARSER_HPP_
#define _NUMBER_PARSER_HPP_

#include <string>
#include <vector>

class NumbersParser
{
public:
	NumbersParser();
	~NumbersParser();
	void getNumber(int num);
	std::string getAllNum();
private:
	int sum_,max_,min_;
	std::vector<int> arr_;

	void reset();
};

#endif // !_NUMBER_PARSER_HPP_


