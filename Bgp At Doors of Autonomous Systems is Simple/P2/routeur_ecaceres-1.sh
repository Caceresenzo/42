mode=$1

# Create a bridge interface that will bridge e1 with the newly created VXLAN interface
ip link add br0 type bridge

# Bring interface into UP state
ip link set dev br0 up

# Give IP address
ip addr add 10.1.1.1/24 dev eth0

# Create VXLAN interface
if [ "$mode" == "static" ]; then
    ip link add name vxlan10 type vxlan id 10 dev eth0 remote 10.1.1.2 local 10.1.1.1 dstport 4789
elif [ "$mode" == "dynamic multicast" ]; then
    ip link add name vxlan10 type vxlan id 10 dev eth0 group 239.1.1.1 dstport 4789
else
    echo "unknown mode: $mode"
    exit 1
fi

# Add address
ip addr add 20.1.1.1/24 dev vxlan10

# Associate VXLAN interface with an ethernet port to be part of the bridge domain
brctl addif br0 eth1
brctl addif br0 vxlan10

# Bring interface to UP state
ip link set dev vxlan10 up
