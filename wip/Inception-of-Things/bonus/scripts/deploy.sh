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

master_ip=$2
login=$2
domain=$3

echo "[IoT] installing helm"
curl -sfL https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3 | bash -

helm repo add gitlab https://charts.gitlab.io/
helm repo update

echo "[IoT] waiting for kubernetes' deployments to be available"
wait_all kube-system

echo "[IoT] creating namespaces"
k create namespace gitlab
k create namespace argocd
k create namespace dev

echo "[IoT] adding gitlab"
helm upgrade --install gitlab gitlab/gitlab \
  --timeout 600s \
  --namespace gitlab \
  --values /vagrant/confs/gitlab-helm.yaml \
  --set global.hosts.domain="$domain" \
  --set global.hosts.externalIP="$master_ip" \
  --set certmanager-issuer.email="$login@student.42.fr"

sed 's/DOMAIN/'"$domain"'/g' /vagrant/confs/gitlab-ingress.yaml | k apply -n gitlab -f -

echo "[IoT] adding argocd"
k apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml
sed 's/DOMAIN/'"$domain"'/g' /vagrant/confs/argocd-ingress.yaml | k apply -n argocd -f -

echo "[IoT] waiting for gitlab's deployments to be available"
wait_all gitlab

echo "[IoT] waiting for argocd's deployments to be available"
wait_all argocd

echo "[IoT] adding application"
sed 's/LOGIN/'"$login"'/g' /vagrant/confs/argocd-application.yaml | k apply -n argocd -f -

argocd_password=$(kubectl -n argocd get secret argocd-initial-admin-secret -o jsonpath="{.data.password}" | base64 -d)
gitlab_password=$(kubectl -n gitlab get secret gitlab-gitlab-initial-root-password -ojsonpath='{.data.password}' | base64 -d)
ip=$(ifconfig eth1 | grep 'inet ' | awk '{ print $2 }')

echo "[IoT] ArgoCD's admin username is: admin"
echo "[IoT] ArgoCD's admin password is: $argocd_password"
echo "[IoT] ArgoCD's dashboard is: http://argocd.$domain/"

echo "[IoT] GitLab's admin username is: root"
echo "[IoT] GitLab's admin password is: $gitlab_password"
echo "[IoT] GitLab's dashboard is: http://gitlab.$domain/"
