FROM alpine

RUN apk add apache2 php-apache2 php-mysqli php-pdo_mysql mysql-client

RUN cd /tmp && \
    wget https://wordpress.org/latest.zip && \
    unzip latest.zip && \
    rm latest.zip && \
    mkdir -p /usr/share/webapps/ && \
    mv wordpress /usr/share/webapps/wordpress && \
    ln -s /etc/wordpress/wp-config.php /usr/share/webapps/wordpress/wp-config.php

COPY etc/apache2/conf.d/wordpress.conf /etc/apache2/conf.d/wordpress.conf
COPY etc/wordpress/wp-config.php /etc/wordpress/wp-config.php

COPY entry.sh /

EXPOSE 80

CMD ["/entry.sh"]
