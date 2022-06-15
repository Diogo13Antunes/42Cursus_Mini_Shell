clear
gcc -Wall -Wextra -Werror main_pwd.c builtin_pwd.c LIBFT_NEW/libft.a -o builtin_pwd
norminette builtin_pwd.c

echo ""
echo "\033[1;36m""Tester [ pwd ]""\033[0m"
./builtin_pwd

echo ""
echo "\033[1;36m""Cat [ out.txt ]""\033[0m"
cat out.txt


echo ""
echo "\033[1;31m""CLEANER""\033[0m"
echo "\033[0;33m""Removed [ out.txt ]""\033[0m"
rm -rf out.txt
