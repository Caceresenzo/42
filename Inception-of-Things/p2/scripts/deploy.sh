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

echo "[IoT] adding deployment"
k apply -f /vagrant/confs/app-1.yaml
k apply -f /vagrant/confs/app-2.yaml
k apply -f /vagrant/confs/app-3.yaml
k apply -f /vagrant/confs/ingress.yaml

echo "[IoT] waiting for deployments to be available"
wait_all default
