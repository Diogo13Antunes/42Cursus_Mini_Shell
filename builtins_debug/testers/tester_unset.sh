clear
gcc -Wall -Wextra -Werror -g main_unset.c builtin_unset.c builtin_check_export_elements.c builtin_env.c builtin_env_utils.c builtin_export.c builtin_print_export.c builtin_manipulation_env.c LIBFT_NEW/libft.a -o builtin_unset
norminette main_unset.c builtin_unset.c builtin_env.c builtin_check_export_elements.c builtin_env_utils.c builtin_manipulation_env.c builtin_print_export.c builtin_export.c

echo ""
./builtin_unset
