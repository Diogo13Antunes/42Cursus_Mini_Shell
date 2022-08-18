clear
gcc -Wall -Wextra -Werror builtin_echo.c -o builtin_echo
norminette builtin_echo.c

echo ""
echo "\033[1;36m""Without flag""\033[0m"
./builtin_echo "Hello World"

echo "\033[1;36m""With flag""\033[0m"
./builtin_echo -n "Hello World"
