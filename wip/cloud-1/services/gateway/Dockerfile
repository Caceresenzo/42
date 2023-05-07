FROM alpine

RUN apk add nginx openssl

COPY etc/nginx/http.d/default.conf /etc/nginx/http.d/default.conf
COPY etc/nginx/snippets /etc/nginx/snippets
COPY etc/ssl/private /etc/ssl/private
COPY etc/ssl/certs /etc/ssl/certs

COPY entry.sh /
RUN chmod +x /entry.sh

EXPOSE 80
EXPOSE 443

CMD ["/entry.sh"]
