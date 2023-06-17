#!/bin/sh

DATADIR=/data

if [ ! -d "$DATADIR" ]; then
    mkdir -p "$DATADIR"
fi

cp /init.original.sql /init.sql
sed -i 's/WORDPRESS_DATABASE_PASSWORD/'$WORDPRESS_DATABASE_PASSWORD'/' /init.sql
sed -i 's/PHPMYADMIN_DATABASE_PASSWORD/'$PHPMYADMIN_DATABASE_PASSWORD'/' /init.sql
cat /init.sql

ARGS='--datadir=/data --user=root'

mysql_install_db $ARGS
exec mysqld $ARGS --init-file=/init.sql
