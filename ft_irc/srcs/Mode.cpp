/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:33:19 by bcaumont          #+#    #+#             */
/*   Updated: 2026/01/02 16:45:06 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Mode.hpp"

Mode::Mode() : _inviteOnly(false), _topicLocked(false), _hasKey(false),
	_hasLimit(false), _limit(0), _key("")
{
}

Mode::Mode(const Mode &copy)
{
	*this = copy;
}

Mode &Mode::operator=(const Mode &copy)
{
	if (this != &copy)
	{
		_inviteOnly = copy._inviteOnly;
		_topicLocked = copy._topicLocked;
		_hasKey = copy._hasKey;
		_hasLimit = copy._hasLimit;
		_limit = copy._limit;
		_key = copy._key;
	}
	return (*this);
}

Mode::~Mode()
{
}

bool Mode::isInviteOnly() const
{
	return (_inviteOnly);
}

bool Mode::isTopicLocked() const
{
	return (_topicLocked);
}

bool Mode::checkKey(const std::string &key) const
{
	return (_hasKey && _key == key);
}

bool Mode::hasKey() const
{
	return (_hasKey);
}

bool Mode::hasLimit() const
{
	return (_hasLimit);
}

size_t Mode::getLimit() const
{
	return (_limit);
}

void Mode::setInvinteOnly(bool mode)
{
	_inviteOnly = mode;
}

void Mode::setTopicLocked(bool mode)
{
	_topicLocked = mode;
}

void Mode::setKey(const std::string &key)
{
	_hasKey = true;
	_key = key;
}

void Mode::setLimit(size_t limit)
{
	_hasLimit = true;
	_limit = limit;
}

void Mode::clearKey()
{
	_hasKey = false;
	_key.clear();
}

void Mode::clearLimit()
{
	_hasLimit = false;
	_limit = 0;
}

std::string Mode::getModeString() const
{
	std::string result;
	if (_inviteOnly)
		result += "i";
	if (_topicLocked)
		result += "t";
	if (_hasKey)
		result += "k";
	if (_hasLimit)
		result += "l";
	return (result);
}
