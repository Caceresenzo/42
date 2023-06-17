#!/bin/sh

DATADIR=/data

if [ ! -d "$DATADIR" ]; then
    mkdir -p "$DATADIR"
fi

ARGS='--datadir=/data --user=root'

mysql_install_db $ARGS
exec mysqld $ARGS --init-file=/init.sql
