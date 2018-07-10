#ifndef _NUMBER_PARSER_HPP_
#define _NUMBER_PARSER_HPP_
#include <string>
#include <vector>
#include <sstream>

class NumbersParser
{
public:
	NumbersParser();
	void getNumber(int num);
	std::stringstream getAllNum();
	~NumbersParser();
private:
	int sum_,max_,min_;
	std::vector<int> arr_;
	void reset();

};


#endif // !_NUMBER_PARSER_HPP_


