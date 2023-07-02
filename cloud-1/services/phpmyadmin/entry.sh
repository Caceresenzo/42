#!/bin/sh

while ! cat /usr/share/webapps/phpmyadmin/sql/create_tables.sql | mysql -hdatabase -uphpmyadmin -p"$PHPMYADMIN_DATABASE_PASSWORD"; do
    sleep 1
done

exec httpd -DFOREGROUND
