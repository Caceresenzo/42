FROM quay.io/frrouting/frr:master

RUN apk add bash iproute2
RUN echo "service integrated-vtysh-config" > /etc/frr/vtysh.conf
RUN sed -i "s/bgpd=no/bgpd=yes/" /etc/frr/daemons
RUN sed -i "s/ospfd=no/ospfd=yes/" /etc/frr/daemons
RUN sed -i "s/isisd=no/isisd=yes/" /etc/frr/daemons

COPY cmd.sh /
RUN chmod +x /cmd.sh

CMD [ "/cmd.sh" ]
