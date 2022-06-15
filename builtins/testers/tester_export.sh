clear
gcc -Wall -Wextra -Werror -g main_export.c builtin_print_export.c builtin_export.c builtin_env.c builtin_env_utils.c builtin_manipulation_env.c builtin_check_export_elements.c LIBFT_NEW/libft.a -o builtin_export
norminette main_export.c builtin_print_export.c builtin_export.c builtin_env.c builtin_env_utils.c builtin_manipulation_env.c builtin_check_export_elements.c

export D1=123456789
export Hello=World

echo ""
./builtin_export "D1=" "=123" "Hello" "-1Two3=123" "_Real_Madrid=Champions&"

unset D1 Hello

diff file1.txt file2.txt
echo ""
cat file3.txt
