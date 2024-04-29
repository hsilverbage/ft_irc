#include "Channel.hpp"

Channel::Channel(std::string key, Client* client, std::string channelName) : _key(key)
{
	this->_topic = "";
	_ClientOperators[client->get_fd()] = client;
	this->_maxClient = 100; // TODO SEE VLAUE TO SET
	this->_channelName = channelName;
}

Channel::~Channel() {}

Channel::Channel(const Channel& rhs)
{
	*this = rhs;
}

Channel& Channel::operator=(const Channel& rhs)
{
	if (this != &rhs)
	{

	}
	return (*this);
}

std::string& Channel::get_key()
{
	return (this->_key);
}

std::string& Channel::get_topic()
{
	return (this->_topic);
}

void Channel::set_topic(std::string topic)
{
	this->_topic = topic;
}

std::map<int, Client*>& Channel::get_ClientOperators()
{
	return (this->_ClientOperators);
}

std::map<int, Client*>& Channel::get_clients()
{
	return (this->_Clients);
}

size_t Channel::get_maxClient()
{
	return (this->_maxClient);
}

void Channel::set_maxClient(size_t max)
{
	this->_maxClient = max;
}

void Channel::add_client_to_channel(Client* client)
{
	this->_Clients[client->get_fd()] = client;
	client->set_nb_channel(client->get_nb_channel() + 1);
	send_msg_to_everyone_in_channel(client->get_nickname() + " is joining the channel " + get_channel_name() + "\r\n");
}

void Channel::remove_client_from_channel(Client* client)
{
	std::map<int, Client*>::iterator it = _Clients.find(client->get_fd());

	if (it != _Clients.end())
	{
		this->_Clients.erase(it);
		client->set_nb_channel(client->get_nb_channel() - 1);
	}
}

void Channel::add_client_to_operators(Client* client)
{
	this->_ClientOperators[client->get_fd()] = client;
}

void Channel::remove_client_from_operators(Client* client)
{
	std::map<int, Client*>::iterator it = _ClientOperators.find(client->get_fd());

	if (it != _ClientOperators.end())
		this->_ClientOperators.erase(it);
}

void Channel::send_msg_to_everyone_in_channel(const std::string str)
{
	for (std::map<int, Client*>::iterator it = _Clients.begin(); it != _Clients.end(); it++)
	{
		if (send(it->first, str.c_str(), str.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
	}
}

std::string& Channel::get_channel_name()
{
	return (this->_channelName);
}
