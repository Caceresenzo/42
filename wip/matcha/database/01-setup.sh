sed -i "s/%MYSQL_DATABASE%/$MYSQL_DATABASE/g" /docker-entrypoint-initdb.d/02-create_db.sql
sed -i "s/%MYSQL_USER%/$MYSQL_USER/g" /docker-entrypoint-initdb.d/02-create_db.sql
