echo "Installing master"

export K3S_TOKEN_FILE="/vagrant/confs/token"
export K3S_KUBECONFIG_MODE="644"
export K3S_CLUSTER_INIT="true"

export INSTALL_K3S_EXEC="server --tls-san $(hostname) --node-ip $1 --advertise-address=$1 --bind-address=0.0.0.0"

# k3s
curl -sfL https://get.k3s.io | sh -

# kubectl
curl -L "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl" -o /tmp/kubectl
curl -L "https://dl.k8s.io/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl.sha256" -o /tmp/kubectl.sha256
echo "$(cat /tmp/kubectl.sha256)  /tmp/kubectl" | sha256sum --check
sudo install -o root -g root -m 0755 /tmp/kubectl /usr/local/bin/kubectl
rm /tmp/kubectl /tmp/kubectl.sha256

# "k" alias
sudo ln -s $(which kubectl) $(dirname $(which kubectl))/k

# setting environment
export KUBECONFIG=/etc/rancher/k3s/k3s.yaml
sudo chmod +r $KUBECONFIG
echo "KUBECONFIG=$KUBECONFIG" >> /etc/environment

# checks
k get nodes -o wide
ifconfig eth1 | grep inet
