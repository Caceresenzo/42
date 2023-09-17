echo "[IoT] installing tools"
apt update
apt install net-tools curl -y

echo -e 'export PATH="/usr/sbin:$PATH"' >> /etc/profile
