FROM quay.io/frrouting/frr:master

RUN sed -i "s/bgpd=no/bgpd=yes/" /etc/frr/daemons
RUN sed -i "s/ospfd=no/ospfd=yes/" /etc/frr/daemons
RUN sed -i "s/isisd=no/isisd=yes/" /etc/frr/daemons
