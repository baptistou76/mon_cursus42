/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 21:51:12 by bcaumont          #+#    #+#             */
/*   Updated: 2026/01/03 13:31:36 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Topic.hpp"

Channel::Channel(const std::string &name) : _name(name), _key(""),
	_mode(new Mode()), _topic(new Topic())
{
}

Channel::Channel(const Channel &copy) : _name(copy._name), _key(copy._key),
	_members(copy._members), _operators(copy._operators),
	_invited(copy._invited), _mode(new Mode(*copy._mode)),
	_topic(new Topic(*copy._topic))
{
}

Channel &Channel::operator=(const Channel &copy)
{
	delete	_mode;
	delete	_topic;

	if (this == &copy)
		return (*this);
	_name = copy._name;
	_key = copy._key;
	_members = copy._members;
	_operators = copy._operators;
	_invited = copy._invited;
	_mode = new Mode(*copy._mode);
	_topic = new Topic(*copy._topic);
	return (*this);
}

Channel::~Channel()
{
	delete	_mode;
	delete	_topic;
}

const std::string &Channel::getName() const
{
	return (_name);
}

const std::set<Client *> &Channel::getMembers() const
{
	return (_members);
}

void Channel::addMember(Client *client)
{
	if (!client)
		return ;
	_members.insert(client);
}

void Channel::removeMember(Client *client)
{
	if (!client)
		return ;
	_members.erase(client);
	_operators.erase(client->getFd());
	_invited.erase(client);
}

void Channel::broadcast(const std::string &message)
{
	for (std::set<Client *>::iterator it = _members.begin(); it != _members.end(); ++it)
		(*it)->sendMessage(message);
}

void Channel::privBroadcast(const std::string &message, Client *exclude)
{
	for (std::set<Client *>::iterator it = _members.begin(); it != _members.end(); ++it)
	{
		if (*it == exclude)
			continue ;
		(*it)->sendMessage(message);
	}
}

bool Channel::isMember(const Client &client) const
{
	return (_members.count(const_cast<Client *>(&client)) > 0);
}

bool Channel::isOperator(const Client &client) const
{
	return (_operators.count(client.getFd()) > 0);
}

void Channel::addOperator(Client *client)
{
	if (!client)
		return ;
	_operators.insert(client->getFd());
}

void Channel::removeOperator(Client *client)
{
	if (!client)
		return ;
	_operators.erase(client->getFd());
}

Mode &Channel::getMode()
{
	return (*_mode);
}

Topic &Channel::getTopic()
{
	return (*_topic);
}

bool Channel::isInvited(const Client &client) const
{
	return (_invited.count(const_cast<Client *>(&client)) > 0);
}

void Channel::addInvitation(Client *client)
{
	if (!client)
		return ;
	_invited.insert(client);
}

void Channel::removeInvitation(Client *client)
{
	if (!client)
		return ;
	_invited.erase(client);
}

size_t Channel::getMemberCount() const
{
	return (_members.size());
}
