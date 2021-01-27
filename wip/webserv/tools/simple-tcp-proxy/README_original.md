This program listens for TCP connections on a given local address
and port.  When a connection is accepted, it forks and then creates
a new connection to a given remote address and port.  As long as
both connections remain established, the program copies packets
between the two sides.  Not unlike SSH tunnels, but without the
SSH.

Usage

   simple-tcp-proxy localip localport remoteip remoteport &
