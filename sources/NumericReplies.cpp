#include "NumericReplies.hpp"

NumericReplies::NumericReplies(std::string port, std::string password) : _port(port), _password(password)
{

}

NumericReplies::~NumericReplies()
{

}

NumericReplies::NumericReplies(const NumericReplies& rhs)
{
	*this = rhs;
}

NumericReplies&	NumericReplies::operator=(const NumericReplies& rhs)
{
	if (this != &rhs)
	{

	}
	return (*this);
}

