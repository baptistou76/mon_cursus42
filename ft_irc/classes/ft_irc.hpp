/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_irc.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:38:15 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/27 23:42:48 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IRC_HPP
# define FT_IRC_HPP

// ========== CODE ERROR DEFINES ===========

# define ERR_NOSUCHNICK "401"        // No such nick/channel
# define ERR_NOSUCHSERVER "402"      // NO such server
# define ERR_NOSUCHCHANNEL "403"     // No such channel
# define ERR_CANNOTSENDTOCHAN "404"  // Cannot send to channel
# define ERR_NORECIPIENT "411"       // No recipient given
# define ERR_NOTEXTTOSEND "412"      // Not text to send
# define ERR_UNKNOWNCOMMAND "421"    // Unknown command
# define ERR_NONICKNAMEGIVEN "431"   // No nickname given
# define ERR_ERRONEUSNICKNAME "432"  // Erroneous nickname
# define ERR_NICKNAMEINUSE "433"     // Nickname in use
# define ERR_USERNOTINCHANNEL "441"  // User not in channel
# define ERR_NOTONCHANNEL "442"      // You're not on that channel
# define ERR_USERONCHANNEL "443"     // User already on channel
# define ERR_NOTREGISTERED "451"     // You have not registered
# define ERR_NEEDMOREPARAMS "461"    // Not enough parameters
# define ERR_ALREADYREGISTERED "462" // Already registered
# define ERR_PASSWDMISMATCH "464"    // Password incorrect
# define ERR_KEYSET "467"            // Channel key already set
# define ERR_CHANNELISFULL "471"     // Channel is full
# define ERR_UNKNOWNMODE "472"       // Unknown mode
# define ERR_INVITEONLYCHAN "473"    // Cannot join invite-only channel
# define ERR_BADCHANNELKEY "475"     // Bad channel key
# define ERR_BADCHANMASK "476"       // Bad channel mask
# define ERR_CHANOPRIVSNEEDED "482"  // Channel operator privileges needed

// ========== REPLIES CODE DEFINES =========

# define RPL_WELCOME "001"
# define RPL_YOURHOST "002"
# define RPL_CREATED "003"
# define RPL_MYINFO "004"
# define RPL_NOTOPIC "331"
# define RPL_TOPIC "332"
# define RPL_NAMREPLY "353"
# define RPL_ENDOFNAMES "366"
# define RPL_INVITING "341"
# define RPL_ENDOFWHO "315"
# define RPL_CHANNELMODEIS "324"

// ========== LIBRAIRIES STANDARD ==========
# include <algorithm>
# include <cstdlib>
# include <cstring>
# include <ctime>
# include <iomanip>
# include <iostream>
# include <map>
# include <set>
# include <sstream>
# include <stdexcept>
# include <string>
# include <vector>

// ========== LIBRAIRIES RÉSEAU ==========
# include <arpa/inet.h>
# include <cstdlib>
# include <cstring>
# include <fcntl.h>
# include <netinet/in.h>
# include <poll.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>

// ========== Interface ===================

class	ICommand;

#endif