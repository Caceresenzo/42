FROM mysql

COPY ./02-create_db.sql /docker-entrypoint-initdb.d/02-create_db.sql
RUN chown -R mysql:mysql /docker-entrypoint-initdb.d
