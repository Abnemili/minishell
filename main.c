/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:23:16 by abnemili          #+#    #+#             */
/*   Updated: 2025/06/13 11:51:58 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
// Add these functions to your minishell project for debugging

#include "minishell.h"

// Function to print a single command's details
void print_cmd_debug(t_cmd *cmd, int cmd_num)
{
    int i;
    
    printf("=== Command %d ===\n", cmd_num);
    printf("Input FD: %d\n", cmd->in_file);
    printf("Output FD: %d\n", cmd->out_file);
    
    if (cmd->full_cmd)
    {
        printf("Arguments: ");
        i = 0;
        while (cmd->full_cmd[i])
        {
            printf("'%s'", cmd->full_cmd[i]);
            if (cmd->full_cmd[i + 1])
                printf(", ");
            i++;
        }
        printf("\n");
    }
    else
    {
        printf("Arguments: (none)\n");
    }
    printf("\n");
}

// Function to print the entire command pipeline
void print_pipeline_debug(t_data *data)
{
    t_cmd *current;
    int cmd_count = 0;
    
    if (!data || !data->head)
    {
        printf("No commands to display (empty pipeline)\n");
        return;
    }
    
    printf("\n==================== PIPELINE DEBUG ====================\n");
    
    current = data->head;
    while (current)
    {
        print_cmd_debug(current, cmd_count + 1);
        current = current->next;
        cmd_count++;
    }
    
    printf("Total commands in pipeline: %d\n", cmd_count);
    printf("========================================================\n\n");
}

// Alternative compact version for quick debugging
void print_pipeline_compact(t_data *data)
{
    t_cmd *current;
    int cmd_num = 1;
    int i;
    
    if (!data || !data->head)
    {
        printf("Empty pipeline\n");
        return;
    }
    
    printf("Pipeline: ");
    current = data->head;
    while (current)
    {
        printf("[");
        if (current->full_cmd && current->full_cmd[0])
        {
            i = 0;
            while (current->full_cmd[i])
            {
                printf("%s", current->full_cmd[i]);
                if (current->full_cmd[i + 1])
                    printf(" ");
                i++;
            }
        }
        else
        {
            printf("empty");
        }
        
        // Show redirections
        if (current->in_file != STDIN_FILENO)
            printf(" <fd:%d", current->in_file);
        if (current->out_file != STDOUT_FILENO)
            printf(" >fd:%d", current->out_file);
            
        printf("]");
        
        if (current->next)
            printf(" | ");
            
        current = current->next;
        cmd_num++;
    }
    printf("\n");
}

int main(int ac, char **av, char **env)
{
	t_data data;
	t_lexer *lexer;
	char *input;

	(void)av;
	(void)env;
	(void)ac;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		init_data(&data, input);
		if (check_empty_line(&data))
			continue;
		lexer = init_lexer(input);
		if (!lexer)
		{
			printf("Error: lexer initialization failed\n");
			free(input);
			continue;
		}
		data.elem = init_tokens(lexer);
		if (!parse_input(data.elem))
		{
			free(input);
			continue;
		}
		if (!parse_pipeline(&data))
        {
			printf("======\n");
			printf("Error: pipeline parsing failed\n");
            free(input);
            // Clean up allocated memory
            continue;
        }
        //DEBUG: Print the parsed commands
        printf("\n--- DEBUG: Parsed Commands ---\n");
        print_pipeline_debug(&data);
		add_history(input);
		free(input);
	}
	return 0;
}

