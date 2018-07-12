#include "NumbersParser.hpp"
#include <algorithm>
#include <limits.h>
#include <sstream>

NumbersParser::NumbersParser() 
{
	reset();
}

void NumbersParser::getNumber(int num)
{
	sum_ += num;
	arr_.push_back(num);
	max_ = std::max(max_,num);
	min_ = std::min(min_, num);
}

std::string NumbersParser::getAllNum()
{
	std::stringstream result;
	std::sort(arr_.begin(), arr_.end());
	std::reverse(arr_.begin(), arr_.end());
	result << "Sum: ";
	result << sum_ << std::endl;
	result << "Numbers: ";
	if (arr_.empty())
	{
		result << "none";
	}
	else
	{
		for (size_t i = 0; i < arr_.size(); ++i)
		{
			result << arr_.at(i) << " ";
		}
	}
	result << std::endl << "Maximum: ";
	(max_ == INT_MIN)? result << "none" : result << max_;
	result << std::endl << "Minimum: ";
	(min_ == INT_MAX)? result << "none" : result << min_;
	result << std::endl;
	reset();
	return result.str();
}


NumbersParser::~NumbersParser()
{
}

void NumbersParser::reset()
{
	sum_=0;
	max_ = INT_MIN;
	min_ = INT_MAX;
	arr_.clear();
}
