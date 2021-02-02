FROM webserv-base

CMD echo Starting 'run' && \
	service mysql start && \
	cd /app/source && \
	valgrind --track-fds=yes /app/source/webserv