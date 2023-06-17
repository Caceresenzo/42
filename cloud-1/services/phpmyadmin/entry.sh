#!/bin/sh

while ! cat /usr/share/webapps/phpmyadmin/sql/create_tables.sql | mysql -hdatabase -uphpmyadmin -ppassword; do
    sleep 1
done

exec httpd -DFOREGROUND
