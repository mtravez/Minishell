
#include "pars_fsm.h"

char	*str_char_join(char const *s1, char const *s2, char c)
{
	char	*joint;
	size_t	sizes1;
	size_t	sizes2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	sizes1 = ft_strlen(s1);
	sizes2 = ft_strlen(s2);
	joint = malloc(sizes1 + sizes2 + 2);
	if (!joint)
		return (NULL);
	ft_memcpy(joint, s1, sizes1);
	joint[sizes1] = c;
	ft_memcpy(joint + sizes1 + 1, s2, sizes2);
	joint[sizes1 + sizes2 + 1] = '\0';
	return (joint);
}
