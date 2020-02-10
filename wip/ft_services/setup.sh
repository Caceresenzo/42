#!/bin/sh

export FT_SERVICES_PREFIX="\e[97m[\e[92mft_services\e[97m]\e[0m"

if which zsh >/dev/null; then
	printf "$FT_SERVICES_PREFIX Starting using ZSH... (at $(which zsh))\n"
    zsh ./srcs/internal.sh $1 $2 $3 $4 $5 $6 $7 $8 $9
elif which bash >/dev/null; then
	printf "$FT_SERVICES_PREFIX Starting using BASH... (at $(which bash))\n"
    bash ./srcs/internal.sh $1 $2 $3 $4 $5 $6 $7 $8 $9
else
	printf "$FT_SERVICES_PREFIX Can't start because only SH is available.\n"
fi