/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:25:09 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:16:32 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_HPP
# define TOPIC_HPP

# include "ft_irc.hpp"

class	Client;

class Topic
{
  private:
	std::string _topic;
	std::string _author;
	time_t _timestamp;

  public:
	Topic();
	Topic(const Topic &copy);
	Topic &operator=(const Topic &copy);
	~Topic();

	// Topic's Public methods //
	const std::string &getTopic() const;
	const std::string &getAuthor() const;
	time_t getTimestamp() const;
	void setTopic(const std::string &topic, const std::string &author);
	void clear();
};

#endif
