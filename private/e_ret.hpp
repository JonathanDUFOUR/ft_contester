/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_ret.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 02:53:35 by jodufour          #+#    #+#             */
/*   Updated: 2022/09/02 02:58:45 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_RET_HPP
# define E_RET_HPP

enum e_ret
{
	IMP_OK, // if the behavior is the same as the standard one
	ISO_OK, // if the behavior differs from the standard one, but still conforms to the ISO C++98 standard
	KO
};

#endif
