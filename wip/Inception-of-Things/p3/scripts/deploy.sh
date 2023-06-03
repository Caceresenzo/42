k wait --for=condition=available --timeout=300s -n kube-system deployment/metrics-server

k create namespace argocd
k create namespace dev

k apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml
k apply -n argocd -f /vagrant/confs/argocd.yaml

k apply -n argocd -f /vagrant/confs/application.yaml
