rarity=$1
title=$2
piped=$3

printf "\e[1m\e[36mTEST: \e[32m[$rarity] \e[20G\e[33m\"$title\"\e[49m\e[90G"

if [ $piped -ne 0 ]
then
	echo "$4" | cat $5 $6 $7 $8 $9 > cat_out 2> cat_err
	ecode_cat=$?
	
	echo "$4" | ./cato9tails $5 $6 $7 $8 $9 > cato9tails_out 2> cato9tails_err
	ecode_cato9tails=$?
else
	cat $4 $5 $6 $7 $8 $9 > cat_out 2> cat_err
	ecode_cat=$?
	
	./cato9tails $4 $5 $6 $7 $8 $9 > cato9tails_out 2> cato9tails_err
	ecode_cato9tails=$?
fi

diff cat_out cato9tails_out > diff_out 2>&1
ecode_diff_out=$?

diff cat_err cato9tails_err > diff_err 2>&1
ecode_diff_err=$?

if [ $ecode_cat -ne $ecode_cato9tails ]
then
	printf "❌"
	printf "\e[95GRETURN CODE "$ecode_cat" != "$ecode_cato9tails
elif [ $ecode_diff_out -ne 0 ]
then
	printf "❌"
	printf "\e[95GDIFF EXIT CODE (OUT) "$ecode_diff_out
elif [ $ecode_diff_err -ne 0 ]
then
	printf "❌"
	printf "\e[95GDIFF EXIT CODE (ERR) "$ecode_diff_err
else
	printf "✅"
	rm -f cat_out cat_err
	rm -f cato9tails_out cato9tails_err
	rm -f diff_out diff_err
fi

printf "\e[0m\n"