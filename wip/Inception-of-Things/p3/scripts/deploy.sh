set -e

if [ "$(id -u)" -ne 0 ]; then
    echo "Please run as root." >&2;
    exit 1;
fi

function wait_all()
{
    namespace=$1

    kubectl get -n $namespace deployment
    
    while true; do
        services=$(kubectl get -n $namespace deployment --no-headers -o custom-columns=":metadata.name" | xargs -I{} echo deployment.apps/{})
    
        if [ -z "$services" ]; then
            echo "no service in namespace '$namespace', retrying in 5 seconds"
            sleep 5
        else
            break
        fi
    done

    k wait --for=condition=available --timeout=300s -n $namespace $services
}

echo "[IoT] waiting for kubernetes' deployments to be available"
wait_all kube-system

echo "[IoT] creating namespaces"
k create namespace argocd
k create namespace dev

echo "[IoT] adding argocd"
k apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml
k apply -n argocd -f /vagrant/confs/argocd.yaml

echo "[IoT] waiting for argocd's deployments to be available"
wait_all argocd

echo "[IoT] adding application"
k apply -n argocd -f /vagrant/confs/application.yaml

password=$(kubectl -n argocd get secret argocd-initial-admin-secret -o jsonpath="{.data.password}" | base64 -d)
ip=$(ifconfig eth1 | grep 'inet ' | awk '{ print $2 }')

echo "[IoT] The admin username is: admin"
echo "[IoT] The admin password is: $password"
echo "[IoT] The dashboard is: http://$ip/"
