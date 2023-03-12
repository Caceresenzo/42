#!/bin/sh

openssl dhparam -out /etc/ssl/certs/dhparam.pem 2048
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/ssl/private/nginx-selfsigned.key \
    -out /etc/ssl/certs/nginx-selfsigned.crt \
    -subj '/C=FR/ST=France/L=Paris/O=42/OU=cloud-1'

exec nginx -g 'daemon off;'
