/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:09:25 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/27 23:38:41 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
# define MODE_HPP

# include "ft_irc.hpp"

class	Channel;
class	Client;

class Mode
{
  private:
	bool _inviteOnly;
	bool _topicLocked;
	bool _hasKey;
	bool _hasLimit;
	size_t _limit;
	std::string _key;

  public:
	Mode();
	Mode(const Mode &copy);
	Mode &operator=(const Mode &copy);
	~Mode();
	bool isInviteOnly() const;
	bool isTopicLocked() const;
	bool checkKey(const std::string &key) const;
	bool hasKey() const;
	bool hasLimit() const;
	size_t getLimit() const;
	void setInvinteOnly(bool mode);
	void setTopicLocked(bool mode);
	void setKey(const std::string &Key);
	void setLimit(size_t limit);
	void clearLimit();
	void clearKey();
	std::string getModeString() const;
};

#endif
