FROM alpine

COPY php-apk.list /
RUN apk add apache2 php-apache2 mysql-client $(cat php-apk.list)

RUN cd /tmp && \
    wget https://files.phpmyadmin.net/phpMyAdmin/5.2.1/phpMyAdmin-5.2.1-english.zip && \
    unzip phpMyAdmin-5.2.1-english.zip && \
    rm phpMyAdmin-5.2.1-english.zip && \
    mkdir -p /usr/share/webapps/ && \
    mv phpMyAdmin-5.2.1-english /usr/share/webapps/phpmyadmin && \
    ln -s /etc/phpmyadmin/config.inc.php /usr/share/webapps/phpmyadmin/config.inc.php

RUN echo '<?php phpinfo(); ?>' > /usr/share/webapps/phpmyadmin/phpinfo.php

COPY etc/apache2/conf.d/phpmyadmin.conf /etc/apache2/conf.d/phpmyadmin.conf
COPY etc/phpmyadmin/config.inc.php /etc/phpmyadmin/config.inc.php

COPY entry.sh /
RUN chmod +x /entry.sh

EXPOSE 80

CMD ["/entry.sh"]
