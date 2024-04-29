#include "Channel.hpp"

Channel::Channel(std::string key, Client* client, std::string channelName) : _key(key), _nameChannel(channelName)
{
	this->_topic = "";
	_ClientOperators.push_back(client);
	this->_maxClient = 100; //TODO SEE VLAUE TO SET
}

Channel::~Channel()
{

}

Channel::Channel(const Channel& rhs)
{
	*this = rhs;
}

Channel&	Channel::operator=(const Channel& rhs)
{
	if (this != &rhs)
	{

	}
	return (*this);
}


std::string&	Channel::get_key()
{
	return (this->_key);
}

std::string&	Channel::get_topic()
{
	return (this->_topic)
}

void			Channel::set_topic(std::string topic)
{
	this->_topic = topic;
}

std::vector<Client*>& 	Channel::get_ClientOperators()
{
	return (this->_ClientOperators);
}

std::map<int, Client*> Channel::get_clients()
{
	return (this->_Clients);
}

void	Channel::get_maxClient()
{
	return (this->_maxClient);
}

size_t	Channel::set_maxClient(size_t max)
{
	this->_maxClient = max;
}


