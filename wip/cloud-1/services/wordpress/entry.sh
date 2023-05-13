#!/bin/sh

if [ "$(ls -A /data)" ]; then
    echo "/data seems OK"
else
    echo "/data is empty, copying"
    cp -r /usr/share/webapps/wordpress/wp-content-original/* /data
fi

sh /fix-perms.sh

exec httpd -DFOREGROUND
