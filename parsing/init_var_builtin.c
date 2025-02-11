#include "minishell.h"

void init_var_builtin(t_buit_in *exec)
{
    exec->input = NULL;
    exec->tab = NULL;
    exec->env_cpy = NULL;
    // exec->cd = NULL;
} 