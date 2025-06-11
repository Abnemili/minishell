/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:14:24 by abnemili          #+#    #+#             */
/*   Updated: 2025/06/10 15:49:53 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handel_redirection_in(t_data *data, t_elem **current, t_cmd *cmd)
{
    int fd;
    
    *current = (*current)->next;
    skip_whitespace_ptr(current);
    if (!*current)
        return (0);
    fd = open((*current)->content, O_RDONLY);
    if (fd == -1)
    {
        data->file_error = 1;
        return (1);
    }
    if (cmd->in_file != STDIN_FILENO)
        close (cmd->in_file);
    cmd->in_file = fd;
    *current = (*current)->next;
    return (1);
}

int handle_redirection_out(t_data *data, t_elem **current, t_cmd *cmd)
{
    int     fd;

    *current = (*current)->next;
    skip_whitespace_ptr(current);
    if (!*current)
        return (1);
    fd = open((*current)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        data->file_error = 1;
        return (0);
    }
    if (cmd->out_file != STDOUT_FILENO)
        close(cmd->out_file);
    cmd->out_file = fd;
    *current = (*current)->next;
    return (1);
}

int handle_redirection_append(t_data *data, t_elem **current, t_cmd *cmd)
{
    int fd;

    *current = (*current)->next;
    skip_whitespace_ptr(current);
    if (!*current)
        return (0);
    fd = open((*current)->content, O_RDONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        data->file_error = 1;
        return (0);
    }
    if (cmd->out_file != STDOUT_FILENO)
        close(cmd->out_file);
    cmd->out_file = fd;
    *current = (*current)->next;
    return (1);
}