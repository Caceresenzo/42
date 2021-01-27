FROM webserv-base

COPY docker/tests/42-testers/ /app/source

ARG DO_MAKE_RE=0
RUN test "$DO_MAKE_RE" = "true" && cd /app/ && make rej || true

WORKDIR /app/source

CMD echo Starting 'run' && \
	service mysql start && \
	dos2unix run-tests.sh && \
	/usr/bin/zsh run-tests.sh