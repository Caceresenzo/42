FROM alpine

RUN apk add apache2 php-apache2 phpmyadmin mysql-client

COPY etc/apache2/conf.d/phpmyadmin.conf /etc/apache2/conf.d/phpmyadmin.conf
COPY etc/phpmyadmin/config.inc.php /etc/phpmyadmin/config.inc.php

COPY entry.sh /
RUN chmod +x /entry.sh

EXPOSE 80

CMD ["/entry.sh"]
