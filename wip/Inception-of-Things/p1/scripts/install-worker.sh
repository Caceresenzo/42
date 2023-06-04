echo "[IoT] installing worker"

export K3S_TOKEN_FILE="/vagrant/confs/token"
export K3S_URL="https://$1:6443"

export INSTALL_K3S_EXEC="agent --node-ip $2 --node-external-ip $2 -v 3"

echo "[IoT] installing k3s"
curl -sfL https://get.k3s.io | sh -

echo "[IoT] doing additional checks"
ifconfig eth1 | grep inet
