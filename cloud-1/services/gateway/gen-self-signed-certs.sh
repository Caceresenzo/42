openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout etc/ssl/private/nginx.key \
    -out etc/ssl/certs/nginx.crt \
    -subj '/C=FR/ST=France/L=Paris/O=42/OU=cloud-1'
