

#include "../inc/shell.h"
#include "env.c"
#include "libft.c"


int has_equal(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

int len_til_equal(char *str)
{
    int i;

    i = 0;
    while (str[i] != '=')
        i++;
    return (i);
}

int compare_env(char *env_str, char *str)
{
    int len;
    len = 0;
    if (has_equal(str))
    {
        len = len_til_equal(str);
        if (ft_strncmp(env_str, str, len) == 0)
            return (1);
    }
    return (0);
}


int is_env(t_env *node, char *str)
{
    t_env *tmp;

    tmp = node;
    while (tmp)
    {
        if (compare_env(tmp->str, str))
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

void    modify_env(t_env **node, char *str)
{
    t_env *tmp;

    tmp = *node;
    while (tmp)
    {
        if (compare_env(tmp->str, str))
        {
			//free(tmp->str);
            tmp->str = ft_strdup(str);
            return ;
        }
        tmp = tmp->next;
    }
}

void    built_export(t_env **node, char *str)
{
    if (is_env(*node, str))
        modify_env(node, str);
/*     else
        env_add_back(node, str);   */
}

int main(int argc, char **argv, char **envp)
{
	t_env *env_struct;

	env_struct = NULL;
	
	create_env_list(&env_struct, envp);
	built_export(&env_struct, argv[1]);
	print_env(env_struct);
	return 0;
}