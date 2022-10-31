/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:22:20 by jodufour          #+#    #+#             */
/*   Updated: 2022/10/06 18:59:15 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_HPP
# define COLORS_HPP

# define BLACK_FG		"\033[38;2;0;0;0m"
# define RED_FG			"\033[38;2;255;0;0m"
# define GREEN_FG		"\033[38;2;0;255;0m"
# define BLUE_FG		"\033[38;2;0;0;255m"
# define YELLOW_FG		"\033[38;2;255;255;0m"
# define MAGENTA_FG		"\033[38;2;255;0;255m"
# define CYAN_FG		"\033[38;2;0;255;255m"
# define WHITE_FG		"\033[38;2;255;255;255m"

# define BLACK_BG		"\033[48;2;0;0;0m"
# define RED_BG			"\033[48;2;255;0;0m"
# define GREEN_BG		"\033[48;2;0;255;0m"
# define BLUE_BG		"\033[48;2;0;0;255m"
# define YELLOW_BG		"\033[48;2;255;255;0m"
# define MAGENTA_BG		"\033[48;2;255;0;255m"
# define CYAN_BG		"\033[48;2;0;255;255m"
# define WHITE_BG		"\033[48;2;255;255;255m"

# define BOLD			"\033[1m"
# define BLINK			"\033[5m"

# define LIGHT_BLUE_FG	"\033[38;2;0;177;255m"

# define PURPLE_BG		"\033[48;2;177;0;177m"

# define RESET			"\033[0m"

#endif
