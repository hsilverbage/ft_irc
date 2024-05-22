#include "Channel.hpp"

Channel::Channel(std::string key, Client* client, std::string channelName) : _key(key)
{
	this->_topic					   = "";
	_ClientOperators[client->get_fd()] = client;
	this->_channelName				   = channelName;
	this->_topicProtected = false;
	this->_nbClient					   = 0;
	this->_inviteOnly 				   = false;
	if (key.empty())
		this->_pwdProtected = false;
	else
		this->_pwdProtected = true;
}

Channel::~Channel() {}

std::string& Channel::get_key()
{
	return (this->_key);
}

std::string& Channel::get_topic()
{
	return (this->_topic);
}

bool	Channel::get_invite_only()
{
	return (this->_inviteOnly);
}

void Channel::set_invite_only(bool status)
{
	this->_inviteOnly = status;
}

void Channel::set_topic(std::string topic, Client* client)
{
	this->_topic = topic;
	this->_whoSetTopic = client->get_nickname();
}

std::string&	Channel::who_set_topic()
{
	return (this->_whoSetTopic);
}

std::map<int, Client*>& Channel::get_ClientOperators()
{
	return (this->_ClientOperators);
}

std::map<int, Client*>& Channel::get_clients()
{
	return (this->_Clients);
}

std::map<int, Client*>& Channel::get_banned()
{
	return (this->_Banned);
}

std::vector<Client*>& Channel::get_invited()
{
	return (this->_Invited);
}

size_t Channel::get_maxClient()
{
	return (this->_maxClient);
}

size_t Channel::get_nbClient()
{
	return (this->_nbClient);
}

void Channel::set_invited_client(Client* client)
{
	this->_Invited.push_back(client);
}

void Channel::set_nbClient(size_t actualNb)
{
	this->_nbClient = actualNb;
}

void	Channel::set_maxClient(size_t max)
{
	this->_maxClient = max;
}

void Channel::add_client_to_channel(Client* client)
{
	this->_Clients[client->get_fd()] = client;
	client->set_nb_channel(client->get_nb_channel() + 1);
	set_nbClient(this->_nbClient + 1);
	// send_msg_to_everyone_in_channel(client->get_nickname() + " is joining the channel " + get_channel_name());
}


bool Channel::is_channel(std::map<std::string, Channel*> channels, std::string channelTarg)
{
	for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if (it->first == channelTarg)
			return true;
	}
	return false;
}

bool Channel::is_banned(std::string nickname)
{
	for (std::map<int, Client*>::iterator it = _Banned.begin(); it != _Banned.end(); it++)
	{
		if (it->second->get_nickname() == nickname)
			return true;
	}
	return false;
}

void Channel::ban_client(Client* client, std::string reason)
{
	std::map<int, Client*>::iterator it = _Clients.find(client->get_fd());

	if (it != _Clients.end())
	{
		if (reason.empty())
			send_msg_to_everyone_in_channel(client->get_nickname() + " is banned from the channel " + get_channel_name() + "\r\n");
		else
			send_msg_to_everyone_in_channel(client->get_nickname() + " is banned from the channel " + get_channel_name() + " because " + reason + "\r\n");
		this->_Clients.erase(it);
		set_nbClient(this->_nbClient - 1);
		_Banned.insert(std::make_pair(it->first, it->second));
		client->set_nb_channel(client->get_nb_channel() - 1);
	}
	else
		NumericReplies::ERR_NOTONCHANNEL(client, get_channel_name());
}

void Channel::unban_client(Client* client)
{
	this->_Clients.insert(std::make_pair(client->get_fd(), client));
	_Banned.erase(client->get_fd());
	send_msg_to_everyone_in_channel(client->get_nickname() + " is unbanned from the channel " + get_channel_name() + "\r\n");
}

void Channel::remove_client_from_channel(Client* client, std::string reason)
{
	std::map<int, Client*>::iterator it = _Clients.find(client->get_fd());
	if (it != _Clients.end())
	{
		if (reason.empty())
			send_msg_to_everyone_in_channel(client->get_nickname() + " is leaving the channel " + get_channel_name() +
											"\r\n");
		else
			send_msg_to_everyone_in_channel(client->get_nickname() + " is leaving the channel " + get_channel_name() +
											" because " + reason + "\r\n");
		this->_Clients.erase(it);
		set_nbClient(this->_nbClient - 1);
		client->set_nb_channel(client->get_nb_channel() - 1);
	}
	else
		NumericReplies::ERR_NOTONCHANNEL(client, get_channel_name());
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

void Channel::send_msg_to_someone(int fd, std::string str)
{
	str += "\r\n";
	if (send(fd, str.c_str(), str.size(), 0) == -1)
		std::cerr << "send() failed" << std::endl;
}

void Channel::send_msg_to_everyone_in_channel(std::string str)
{
	str = ":" + str + "\r\n";
	for (std::map<int, Client*>::iterator it = _Clients.begin(); it != _Clients.end(); it++)
	{
		if (is_banned(it->second->get_nickname()))
			it++;
		if (send(it->first, str.c_str(), str.size(), 0) == -1)
			std::cerr << "send() failed" << std::endl;
	}
}

std::string& Channel::get_channel_name()
{
	return (this->_channelName);
}

bool	Channel::get_topicProtected()
{
	return (this->_topicProtected);
}

void	Channel::set_topicProtected(bool status)
{
	this->_topicProtected = status;
}

bool	Channel::isOperator(int fd)
{
	std::map<int, Client*>::iterator it = _ClientOperators.find(fd);

	if (it != _ClientOperators.end())
		return (true);
	return (false);
}

bool	Channel::is_client_in_channel(int fd)
{
	std::map<int, Client*>::iterator it = _Clients.find(fd);

	if (it == _Clients.end())
		return (false);
	return (true);
}

bool	Channel::is_nick_in_channel(const std::string nickname)
{
	for (std::map<int, Client*>::iterator it = _Clients.begin(); it != _Clients.end(); it++)
	{
		if (it->second->get_nickname() == nickname)
			return (true);
	}
	return (false);
}

bool Channel::get_pwd_protected()
{
	return (this->_pwdProtected);
}

void Channel::set_pwd_protected(bool status)
{
	this->_pwdProtected = status;
}
