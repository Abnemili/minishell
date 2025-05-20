#include "minishell.h"


char *get_env_value(const char *var_name, char **env)
{
	int i = 0;
	while (env[i])
	{
		if (strncmp(env[i], var_name, strlen(var_name)) == 0 && env[i][strlen(var_name)] == '=')
			return (env[i] + strlen(var_name) + 1);
		i++;
	}
	return "";
}
 // this function get the content of the $variable 
char *expnade_variable(const char *input, char **env, int state)
{
	char *result  = malloc(1);
	result[0] = '\0';
	int i = 0;

	while (input[i])
	{
		if (input[i] == '$' && state != IN_QUOTE)
		{
			i++;
			int start = i;
			while(input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
				i++;
			char *var = ft_strndup(&input[start], i - start);
			char *val = get_env_value(var, env);
			result = realloc(result, ft_strlen(result) + ft_strlen(val) + 1);
			strcat(result, val);
			free(var);
		}
		else
        {
            int len = strlen(result);
            result = realloc(result, len + 2);
            result[len] = input[i];
            result[len + 1] = '\0';
            i++;
        }
	}
	return result;
}