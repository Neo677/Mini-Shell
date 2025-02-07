#include "built_in.h"

void    init_var(t_buit_in *exec)
{
	(void)exec->ac;
	(void)exec->av;
	exec->env_cpy = NULL;
	exec->export_cpy = NULL;
	exec->tab = NULL;
	exec->input = 0;
	exec->cd = 0;
}
