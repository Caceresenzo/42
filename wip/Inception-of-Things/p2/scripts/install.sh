export K3S_KUBECONFIG_MODE="644"
export K3S_CLUSTER_INIT="true"

export INSTALL_K3S_EXEC="--tls-san $(hostname) --node-ip $1 --advertise-address=$1 --bind-address=0.0.0.0"

echo "[IoT] installing k3s"
curl -sfL https://get.k3s.io | sh -

echo "[IoT] aliasing k"
path=/usr/local/bin/k
echo -e '#!/bin/sh\nk3s kubectl $@' > $path
chmod +x $path

echo "[IoT] doing additional checks"
k get nodes -o wide
ifconfig eth1 | grep inet
