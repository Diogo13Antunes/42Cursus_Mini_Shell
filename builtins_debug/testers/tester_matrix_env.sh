clear
gcc -Wall -Wextra -Werror -g main_matrix_env.c matrix_env.c builtin_env.c builtin_env_utils.c builtin_manipulation_env.c LIBFT_NEW/libft.a -o env_matrix
norminette main_matrix_env.c matrix_env.c builtin_env.c builtin_env_utils.c builtin_manipulation_env.c

./env_matrix