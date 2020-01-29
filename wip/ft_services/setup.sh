#export GOINFRE=~/goinfre
#export MINIKUBE_HOME=$GOINFRE/minikube

export SOURCES=srcs

export LOGS=$SOURCES/logs

export DATABASES=$SOURCES/databases

export CERTIFICATES=$SOURCES/certificates

export KUSTOMIZATION=$SOURCES/kustomization
export KUSTOMIZATION_READY=$KUSTOMIZATION/ready
export KUSTOMIZATION_TEMPLATES=$KUSTOMIZATION/templates

export OPERATION=$1

export FT_SERVICES_PREFIX="\e[97m[\e[92mft_services\e[97m]\e[0m"

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
	
	printf "$FT_SERVICES_PREFIX Check current minikube status... "
	minikube status | grep -q Running
	if [[ $? -ne "0" ]]
	then
		printf "\e[95mNOT RUNNING\e[0m\n"
		echo "$FT_SERVICES_PREFIX Starting now..."
	
		minikube config set vm-driver virtualbox
		#minikube start --memory 3000 --extra-config=kubelet.authentication-token-webhook=true --extra-config=kubelet.authorization-mode=AlwaysAllow
		#minikube start --memory 3000 --bootstrapper=kubeadm --kubernetes-version=v1.12.2 --extra-config=kubelet.authentication-token-webhook=true
		minikube start --memory 3000 --bootstrapper=kubeadm
		
		if [[ "$?" -ne "0" ]]
		then
			echo "$FT_SERVICES_PREFIX Failed to start minikube (return code != 0)"
		
			exit 1
		fi
	else
		printf "\e[95mALREADY RUNNING\e[0m\n"
	fi
	
	pids=$(ps aux | grep "[m]inikube dashboard" | cut -c10-15 | tr -d ' ')
	if [[ "$pids" != "" ]]
	then
		echo "$FT_SERVICES_PREFIX Killing old minikube dashboard instances..."
		
		kill -9 $(echo $pids) || true
	fi
	
	minikube dashboard > $LOGS/minikube_dashboard.log 2>&1 &
	
	printf "$FT_SERVICES_PREFIX Waiting for the dashboard"
	while true;
	do
		printf "."
		sleep 1s
		
		log=$(cat $LOGS/minikube_dashboard.log)
	
		if [[ "$log" = *"error"* ]]
		then
			printf " \e[101mFAILED\e[0m\n"
			echo "Failed to start the dashboard."
	
			exit 3
		elif [[ "$log" = *"Opening"* ]]
		then
			printf " \e[102mDONE\e[0m\n"
			echo "Dashboard started!"
			
			break
		fi
	done

	echo "$FT_SERVICES_PREFIX Enabling minikube addons..."
	
	minikube addons enable ingress
	minikube addons enable dashboard
	minikube addons enable metrics-server
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
	
	clear_dir $to
	cp $from/*.yaml $to/
	
	ip=$(minikube ip)

	echo "$FT_SERVICES_PREFIX Generating kustomization with IP = $ip..."
	
	find $to/ -name "*.yaml" -type f -print -exec sed -i 's/__ip__/'$ip'/g' {} \;
}

function clear_dir()
{
	directory=$1
	
	rm -rf $directory/*.yaml
}

echo "$FT_SERVICES_PREFIX Hello"

if [[ "$OPERATION" != "update" ]] && [[ "$OPERATION" != "delete" ]]
then
	start_minikube

	echo "$FT_SERVICES_PREFIX Generating TLS from templates..."
	cp $KUSTOMIZATION_TEMPLATES/tls.yaml $KUSTOMIZATION/tls.yaml
	generate_tls_certificate $CERTIFICATES/common.crt $CERTIFICATES/common.key $KUSTOMIZATION/tls.yaml
fi

generate_ready_kustomization $KUSTOMIZATION $KUSTOMIZATION_READY

if [[ "$OPERATION" == "delete" ]]
then
	echo "$FT_SERVICES_PREFIX Deleting..."
	
	kubectl delete configmap grafana-database
	kubectl delete -k $KUSTOMIZATION_READY
else
	echo "$FT_SERVICES_PREFIX Applying..."
	
	kubectl create configmap grafana-database --from-file=./srcs/databases/grafana.db
	kubectl apply -k $KUSTOMIZATION_READY
fi

echo "$FT_SERVICES_PREFIX Done!"