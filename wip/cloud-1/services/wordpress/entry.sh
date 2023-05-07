#!/bin/sh

if [ "$(ls -A /data)" ]; then
    echo "/data seems OK"
else
    echo "/data is empty, copying"
    cp -r /usr/share/webapps/wordpress/wp-content-original/* /data
fi

chmod +wrx /usr/share/webapps/wordpress/wp-content
chmod -R +wrx /data

exec httpd -DFOREGROUND
