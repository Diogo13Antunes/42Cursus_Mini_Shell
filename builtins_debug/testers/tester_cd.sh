clear
gcc -Wall -Wextra -Werror -g builtin_cd.c builtin_pwd.c builtin_env.c builtin_env_utils.c builtin_manipulation_env.c LIBFT_NEW/libft.a -o builtin_cd
norminette builtin_cd.c builtin_pwd.c builtin_env.c builtin_env_utils.c builtin_manipulation_env.c

echo ""
echo "\033[1;36m""With more than 1 Arg""\033[0m"
./builtin_cd "/Users/dcandeia/Desktop" ".."

echo ""
echo "\033[1;36m""Without Args""\033[0m"
./builtin_cd

echo ""
echo "\033[1;36m""The directory doesn't exist""\033[0m"
./builtin_cd "/Users/dcandeia/Desktop/Amazing"

echo ""
echo "\033[1;36m""Absolute Path [ /Users/dcandeia/Desktop ]""\033[0m"
./builtin_cd "/Users/dcandeia/Desktop"

echo ""
echo "\033[1;36m""Relative Path using [ .. ]""\033[0m"
echo "\033[1;36m""Inicial Path [ /Users/dcandeia/Desktop/secret/MiniShell ]""\033[0m"
./builtin_cd ".."

echo ""
echo "\033[1;36m""Relative Path using [ ../.. ]""\033[0m"
echo "\033[1;36m""Inicial Path [ /Users/dcandeia/Desktop/secret/MiniShell ]""\033[0m"
./builtin_cd "../.."

echo ""
echo "\033[1;36m""Relative Path using [ ../../../Downloads ]""\033[0m"
echo "\033[1;36m""Inicial Path [ /Users/dcandeia/Desktop/secret/MiniShell ]""\033[0m"
./builtin_cd "../../../Downloads"
