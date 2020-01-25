export GOINFRE=~/goinfre
export MINIKUBE_HOME=$GOINFRE/minikube

export SOURCES=srcs

export LOGS=$SOURCES/logs

export CERTIFICATES=$SOURCES/certificates

export KUSTOMIZATION=$SOURCES/kustomization
export KUSTOMIZATION_READY=$KUSTOMIZATION/ready
export KUSTOMIZATION_TEMPLATES=$KUSTOMIZATION/templates

export OPERATION=$1

function redirect_minikube()
{
	to=$1

	if [[ -d "$to" ]]
	then
		echo "Using redirected MINIKUBE home"
	else
		echo "Redirecting MINIKUBE home directory... ($to)"
		mkdir "$to"
	fi
}

function start_minikube()
{
	#redirect_minikube
	
	minikube status | grep -q Stopped
	if [[ $? -eq "0" ]]
	then
		minikube config set vm-driver virtualbox
		minikube start --memory 3000
	fi
	
	kill -9 $(ps aux | grep "[m]inikube dashboard" | cut -c10-15 | tr -d ' ') || true
	minikube dashboard &
}

function generate_tls_certificate()
{
	cert_file=$1
	key_file=$2
	to=$3

﻿	rm -rf "${cert_file}" "${key_file}"
	
	openssl req -newkey rsa:4096 -x509 -sha256 -days 3650 -nodes -out "${cert_file}" -keyout "${key_file}" -subj "/C=FR/ST=France/L=France/OU=42/OU=42/CN=42"
	
	sed -i 's/__b64_cert__/'$(cat $cert_file | base64 | tr -d '\n')'/g' $to
	sed -i 's/__b64_key__/'$(cat $key_file | base64 | tr -d '\n')'/g' $to
}

function generate_ready_kustomization()
{
	from=$1
	to=$2
	
	clear_ready $to
	cp $from/*.yaml $to/
	
	ip=$(minikube ip)
	
	find $to/ -name "*.yaml" -type f -print -exec sed -i 's/__ip__/'$ip'/g' {} \;
}

function clear_ready()
{
	directory=$1
	
	rm -rf $directory/*.yaml
}

if [[ "$OPERATION" != "update" ]]
then
	start_minikube

	cp $KUSTOMIZATION_TEMPLATES/tls.yaml $KUSTOMIZATION/tls.yaml
	generate_tls_certificate $CERTIFICATES/common.crt $CERTIFICATES/common.key $KUSTOMIZATION/tls.yaml
fi

generate_ready_kustomization $KUSTOMIZATION $KUSTOMIZATION_READY

if [[ "$OPERATION" == "delete" ]]
then
	kubectl delete -k $KUSTOMIZATION_READY
else
	kubectl apply -k $KUSTOMIZATION_READY
fi

clear_ready $KUSTOMIZATION_READY
