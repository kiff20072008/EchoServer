#include "NumbersParser.h"
#include <algorithm>
#include <limits.h>


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

std::stringstream NumbersParser::getAllNum()
{
	std::stringstream stream;
	std::sort(arr_.begin(), arr_.end());
	std::reverse(arr_.begin(), arr_.end());
	stream << "Sum: ";
	stream << sum_<<std::endl;
	stream  << "Numbers: " ;
	if (arr_.empty())
	{
		stream << "none" ;
	}
	else
	{
		for (size_t i = 0; i < arr_.size(); ++i)
		{
			stream << arr_.at(i) << " ";
		}
	}
	stream << std::endl << "Maximum: ";
	(max_ == INT_MIN) ? stream << "none" << std::endl : stream << max_ << std::endl;
	stream << "Minimum: ";
	(min_ == INT_MAX) ? stream << "none" << std::endl : stream << min_ << std::endl;
	reset();
	return stream;
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
