goinfre=~/goinfre
minikube_home=$goinfre"/minikube"

if [[ -d "$minikube_home" ]]
then
	echo "using redirected minikube home"
else
	echo "redirecting minikube home directory..."
	mkdir "$minikube_home"
fi

eval 'export MINIKUBE_HOME=$minikube_home'

minikube config set vm-driver virtualbox
minikube start

minikube dashboard &

kubectl apply -f srcs/spec.yaml

sh srcs/nginx/setup-index.sh
