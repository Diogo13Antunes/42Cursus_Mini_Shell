clear
gcc -Wall -Wextra -Werror -g main_env.c builtin_env.c builtin_env_utils.c builtin_manipulation_env.c LIBFT_NEW/libft.a -o builtin_env
norminette main_env.c builtin_env.c builtin_env_utils.c builtin_manipulation_env.c

echo ""
echo "\033[1;36m""Original Env""\033[0m"
env >original_env.txt
cat original_env.txt

echo ""
echo "\033[1;36m""Fake Env""\033[0m"
./builtin_env >fake_env.txt
cat fake_env.txt

echo ""
echo "\033[1;36m""Diff""\033[0m"
diff fake_env.txt original_env.txt
