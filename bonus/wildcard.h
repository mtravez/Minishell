/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:45:12 by mtravez           #+#    #+#             */
/*   Updated: 2023/06/03 15:45:34 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <dirent.h>

typedef struct s_wildir
{
	char			*subdir;
	DIR				*src_dir;
	struct dirent	*dent;
	char			*address;
}	t_wildir;

#endif