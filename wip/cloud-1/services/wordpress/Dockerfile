FROM alpine

RUN apk add apache2 php-apache2 php-mysqli php-pdo_mysql mysql-client

RUN cd /tmp && \
    wget https://wordpress.org/latest.zip && \
    unzip latest.zip && \
    rm latest.zip && \
    mkdir -p /usr/share/webapps/ && \
    mv wordpress /usr/share/webapps/wordpress && \
    mv /usr/share/webapps/wordpress/wp-content /usr/share/webapps/wordpress/wp-content-original && \
    ln -s /data /usr/share/webapps/wordpress/wp-content && \
    ln -s /etc/wordpress/wp-config.php /usr/share/webapps/wordpress/wp-config.php

RUN echo '<?php phpinfo(); ?>' > /usr/share/webapps/wordpress/phpinfo.php

COPY etc/apache2/conf.d/wordpress.conf /etc/apache2/conf.d/wordpress.conf
COPY etc/wordpress/wp-config.php /etc/wordpress/wp-config.php

COPY entry.sh /
RUN chmod +x /entry.sh

EXPOSE 80

CMD ["sh", "/entry.sh"]
