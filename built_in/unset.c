
#include "../inc/shell.h"
#include "env.c"

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

/* int has_equal(char *str)
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


int compare_env(char *env_str, char *str, int mode)
{
    int len;
    len = 0;
    if (has_equal(str) && mode == 1)
    {
        len = len_til_equal(str);
        if (ft_strncmp(env_str, str, len) == 0)
            return (1);
    }
    else if (!has_equal(str) && mode == 0)
    {
        len = len_til_equal(env_str);
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
        if (compare_env(tmp->str, str, 0))
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

// modifies the env_node depending on mode; 1 = export -> modify string   0 = unset -> delete node
void    modify_env(t_env **node, char *str, int mode)
{
    t_env *tmp;

    tmp = *node;
    tmp->flag = 0;
    while (tmp)
    {
        if (compare_env(tmp->str, str, 1) && mode == 1)
        {
			//free(tmp->str);
            tmp->str = ft_strdup(str);
            return ;
        }
        else if (compare_env(tmp->str, str, 0) && mode == 0)
        {
            tmp->flag = 1;
            unset_env(node);
        }
        tmp = tmp->next;
    }
} */

void    built_unset(t_env **node, char *str)
{
    if (is_env(*node, str))
        modify_env(node, str, 0);
    else
        return ;
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_env *env_struct;

// 	env_struct = NULL;
	
// 	create_env_list(&env_struct, envp);
//     built_unset(&env_struct, argv[1]);
// 	print_env(env_struct);
// 	return 0;
// }
