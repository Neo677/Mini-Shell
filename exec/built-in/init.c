#include "../include/exec.h"

void    init_var_builtin(t_buit_in *exec)
{
	(void)exec->ac;
	(void)exec->av;
	exec->env_cpy = NULL;
	exec->export_cpy = NULL;
	exec->tab = NULL;
	exec->input = 0;
	exec->cd = 0;
	exec->exit = 0;
	exec->check_built_in = 0;
}
