/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:56:12 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 18:09:15 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TopicCmd.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "Utils.hpp"
#include "Topic.hpp"
#include "ft_irc.hpp"

void TopicCmd::execute(Server &server, Client &client,
    const std::vector<std::string> &args)
{
    if (!client.isRegistered())
        return sendError(server, client, ERR_NOTREGISTERED, "TOPIC",
                         "You have not registered");

    if (args.empty())
        return sendError(server, client, ERR_NEEDMOREPARAMS, "TOPIC",
                         "Not enough parameters");

    const std::string channelName = args[0];
    Channel *chan = server.getChannel(channelName);
    if (!chan)
        return sendError(server, client, ERR_NOSUCHCHANNEL, channelName,
                         "No such channel");

    if (!chan->isMember(client))
        return sendError(server, client, ERR_NOTONCHANNEL, channelName,
                         "You're not on that channel");

    if (args.size() == 1)
    {
        const std::string &topic = chan->getTopic().getTopic();
        if (topic.empty())
            return sendReply(server, client, RPL_NOTOPIC, channelName, "No topic is set");
        return sendReply(server, client, RPL_TOPIC, channelName, topic);
    }

    if (chan->getMode().isTopicLocked() && !chan->isOperator(client))
        return sendError(server, client, ERR_CHANOPRIVSNEEDED, channelName,
                         "You're not channel operator");

    std::string newTopic;
    for (size_t i = 1; i < args.size(); ++i)
    {
        if (i > 1)
            newTopic += " ";
        newTopic += args[i];
    }
    if (!newTopic.empty() && newTopic[0] == ':')
        newTopic = newTopic.substr(1);

    chan->getTopic().setTopic(newTopic, client.getNickname());
    chan->broadcast(":" + client.getNickname() + " TOPIC " + channelName
                    + " :" + newTopic);
}
