echo "[IoT] installing k3d"
curl -s https://raw.githubusercontent.com/k3d-io/k3d/main/install.sh | bash

echo "[IoT] installing kubectl"
curl -L "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl" -o /tmp/kubectl
curl -L "https://dl.k8s.io/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl.sha256" -o /tmp/kubectl.sha256
echo "$(cat /tmp/kubectl.sha256)  /tmp/kubectl" | sha256sum --check
sudo install -o root -g root -m 0755 /tmp/kubectl /usr/local/bin/kubectl
rm /tmp/kubectl /tmp/kubectl.sha256

echo "[IoT] aliasing k"
sudo ln -s $(which kubectl) $(dirname $(which kubectl))/k

echo "[IoT] creating cluster"
k3d cluster create iot -p "80:80@loadbalancer" -p "443:443@loadbalancer" -p "2222:22@loadbalancer" -p "8888:8888@loadbalancer"

echo "[IoT] preparing env"
echo 'export KUBECONFIG="$(k3d kubeconfig write iot)"' >> /home/vagrant/.bashrc
source /home/vagrant/.bashrc

echo "[IoT] doing additional checks"
ifconfig eth1 | grep inet
docker run --rm hello-world
kubectl cluster-info
