FROM alpine

RUN apk add mysql mysql-client

RUN mkdir /run/mysqld && \
    sed -i 's/skip-networking/#skip-networking/g' /etc/my.cnf.d/mariadb-server.cnf && \
    sed -i 's/#bind-address=0.0.0.0/bind-address=0.0.0.0/g' /etc/my.cnf.d/mariadb-server.cnf

COPY entry.sh init.sql /
RUN chmod +x /entry.sh

EXPOSE 3306

CMD ["/entry.sh"]
