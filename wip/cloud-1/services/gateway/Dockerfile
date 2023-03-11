FROM alpine

RUN apk add nginx

COPY etc/nginx/http.d/default.conf /etc/nginx/http.d/default.conf

COPY entry.sh /
RUN chmod +x /entry.sh

EXPOSE 80

CMD ["/entry.sh"]
