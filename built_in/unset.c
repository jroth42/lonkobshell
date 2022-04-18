
#include "../inc/shell.h"


//deletes flagged node
void    unset_env(t_env **head)
{
    t_env *tmp;
    t_env *prev;


    tmp = *head;
    prev = *head;
    if (tmp && tmp->flag == 1)
    {
        *head = tmp->next;
        tmp->next = NULL;
        //free (tmp);
        return ;
    }
    while (tmp && tmp->flag != 1)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    prev->next = tmp->next;
    tmp->next = NULL;
    //free(temp);
}

void    ft_unset(t_cmd *table, char **envp, char *str)
{
	t_env	*env_struct;

	env_struct = NULL;
	create_env_list(&env_struct, envp);
    if (is_env(env_struct, str))
        modify_env(&env_struct, str, 0);
    else
        return ;
}

