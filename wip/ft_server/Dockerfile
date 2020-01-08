ARG VERSION=buster

FROM debian:$VERSION
ENV AUTHOR=ecaceres

# Config
ARG HTTP_DIR=/var/www/html
ARG NGINX_DIR=/etc/nginx
ARG NGINX_SITES_DIR=$NGINX_DIR/sites-enabled

# Possible values: 'on' or 'off'
ARG NGINX_AUTO_INDEX="on"

ARG MYSQL_PASSWORD="password"

ARG WORDPRESS_DATABASE_NAME=wordpress_42
ARG WORDPRESS_TAR=wordpress.tar.gz
ARG WORDPRESS_TAR_URL=https://fr.wordpress.org/latest-fr_FR.tar.gz

ARG PHPMYADMIN=phpmyadmin
ARG PHPMYADMIN_TAR=phpmyadmin.tar.gz
ARG PHPMYADMIN_TAR_URL=https://files.phpmyadmin.net/phpMyAdmin/4.9.0.1/phpMyAdmin-4.9.0.1-all-languages.tar.gz

# Updating indexes
RUN apt-get update

# Installing programs
RUN apt-get install nginx -y ; \
	apt-get install php php-mysql php-fpm php-mbstring php-zip php-gd -y ; \
	apt-get install default-mysql-server -y ; \
	apt-get install wget -y ;

# Installing debug tools
RUN apt-get install curl zsh git nano -y ; \
	yes | sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# Using working directory
WORKDIR $HTTP_DIR

# Removing unwanted data
RUN rm -f $NGINX_SITES_DIR/default ; \
	rm -rf *
	
# Making a directory for testing auto-index
RUN mkdir $HTTP_DIR/empty

# Copying config files and preparing nginx to use PHP
COPY ./srcs/nginx-template $NGINX_SITES_DIR/default
RUN sed -i 's/%PHP_FPM%/'$(find /etc/init.d -name "php*" -printf "%f")'/g' $NGINX_SITES_DIR/default ; \
	sed -i 's/%AUTO_INDEX%/'$NGINX_AUTO_INDEX'/g' $NGINX_SITES_DIR/default ; \
	openssl req -newkey rsa:4096 -x509 -sha256 -days 3650 -nodes -out $NGINX_DIR/common.crt -keyout $NGINX_DIR/common.key -subj "/C=FR/ST=France/L=France/OU=42/OU=42/CN=42" ; \
	cat $NGINX_SITES_DIR/default ; \
	nginx -t

# Installing WordPress
COPY ./srcs/wp-config.php wp-config.php
RUN wget -P $HTTP_DIR -O $WORDPRESS_TAR $WORDPRESS_TAR_URL ; \
	tar xvf $WORDPRESS_TAR ; \
	rm -f $WORDPRESS_TAR ; \
	mv wordpress/* . ; \
	rm -rf wordpress $WORDPRESS_TAR ; \
	sed -i 's/%MYSQL_PASSWORD%/'$MYSQL_PASSWORD'/g' wp-config.php ; \
	sed -i 's/%MYSQL_DATABASE%/'$WORDPRESS_DATABASE_NAME'/g' wp-config.php

# Installing PhpMyAdmin
RUN mkdir $HTTP_DIR/$PHPMYADMIN ; \
	wget -P $HTTP_DIR -O $PHPMYADMIN_TAR $PHPMYADMIN_TAR_URL ; \
	tar xvf $PHPMYADMIN_TAR ; \
	mv phpMyAdmin*/* phpmyadmin ; \
	rm -rf phpMyAdmin* $PHPMYADMIN_TAR

# Running MySQL to create required table and setting root's mysql password
RUN service mysql start ; \
	mysql -u root -p -e "CREATE DATABASE IF NOT EXISTS "$WORDPRESS_DATABASE_NAME";" ; \
	mysqladmin -u root -p password $MYSQL_PASSWORD
	
EXPOSE 80/tcp
EXPOSE 80/udp
	
EXPOSE 443/tcp
EXPOSE 443/udp

# When starting container, starting mysql, php proxy and nginx
CMD service mysql start ; \
	service $(find /etc/init.d -name "php*" -printf "%f") start ; \
	nginx -g 'daemon off;'
#	/bin/zsh