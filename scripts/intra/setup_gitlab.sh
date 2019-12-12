C_BOLD="\e[1m"
C_WHITE="\e[97m"
C_LIGHT_GREEN="\e[32m"
C_RESET="\e[0m"

C_TEXT="$C_BOLD$C_LIGHT_GREEN"

file=~/.ssh/id_rsa
pub_file=$file".pub"

rm -f "$file" "$pub_file"

printf $C_TEXT"SSH Key generator for the new vogsphere-v2 identification system\n\n"$C_RESET

printf "Email Address: "
read email

printf $C_TEXT"\nCreating new SSH file...\n"$C_RESET
ssh-keygen -t rsa -b 4096 -C "$email" -f "$file" -P ""

printf $C_TEXT"\nRegistering it...\n"$C_RESET
eval "$(ssh-agent -s)"
ssh-add -K "$file"

printf $C_TEXT"\nNow copy paste that key in the following sites:\n"$C_RESET
printf $C_TEXT"\t- https://gitlab.com/profile/keys\n"$C_RESET
printf $C_TEXT"\t- https://profile.intra.42.fr/gitlab_users/new\n"$C_RESET

printf $C_TEXT"\nHere is the key:\n"$C_RESET

printf $C_WHITE
cat "$pub_file"
printf $C_RESET
