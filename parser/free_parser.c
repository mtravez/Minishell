
#include "parser.h"
#include "cmd_builder.h"
#include <stdlib.h>

//		didn't finish :D
void	free_parser(t_cb *cb)
{	
	free(cb->current_cmd);
}
