FT_TESTER_DIR=YoupiBanane

cp -r $FT_TESTER_DIR /tmp/$FT_TESTER_DIR

if [[ "$RUN_WITH_VALGRIND" = "true" ]]
then
	valgrind --track-fds=yes --leak-check=full ./webserv -f conf_42_tester.json &
	jobpid=$!
else
	./webserv -f conf_42_tester.json &
	jobpid=$!
fi

chmod +x ./ubuntu_tester
chmod +x ./ubuntu_cgi_tester

./ubuntu_tester http://localhost:80
out=$?

printf "\n\n\n-- sending an interrupt --\n"
kill -s INT $jobpid

echo "waiting for program exit"
wait $jobpid

printf "\n\n\n-- files --\n"
find $FT_TESTER_DIR

printf "\n\n\n-- files diff --\n"
find $FT_TESTER_DIR > /tmp/a
BACK=$(pwd) ; cd /tmp/ ; find $FT_TESTER_DIR > /tmp/b ; cd $BACK
diff /tmp/a /tmp/b

printf "\n\n\nexit code $out\n"

exit $out