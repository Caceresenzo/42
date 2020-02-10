#!/bin/bash

export MAC_42=1

if [ $MAC_42 -eq 1 ]
then
	export GOINFRE=~/goinfre
	export MINIKUBE_HOME=$GOINFRE/minikube
	
	export SED_EXTRA="_"
	export GREP_EXTRA="E"
else
	export SED_EXTRA=""
	export GREP_EXTRA="P"
fi

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
		printf "$FT_SERVICES_PREFIX Using redirected minikube home\n"
	else
		printf "$FT_SERVICES_PREFIX Redirecting minikube home directory... ($to)\n"
		mkdir "$to"
	fi
}

function start_minikube()
{
	if [[ $MAC_42 -eq 1 ]]
	then
		redirect_minikube $MINIKUBE_HOME
	fi
	
	printf "$FT_SERVICES_PREFIX Check current minikube status... "
	minikube status | grep -q Running
	if [[ $? -ne "0" ]]
	then
		printf "\e[95mNOT RUNNING\e[0m\n"
		printf "$FT_SERVICES_PREFIX Starting now...\n"
	
		minikube config set vm-driver virtualbox
		#minikube start --memory 3000 --extra-config=kubelet.authentication-token-webhook=true --extra-config=kubelet.authorization-mode=AlwaysAllow
		#minikube start --memory 3000 --bootstrapper=kubeadm --kubernetes-version=v1.12.2 --extra-config=kubelet.authentication-token-webhook=true
		minikube start --memory 3000 --bootstrapper=kubeadm
		
		if [[ "$?" -ne "0" ]]
		then
			printf "$FT_SERVICES_PREFIX Failed to start minikube (return code != 0)\n"
		
			exit 1
		fi
	else
		printf "\e[95mALREADY RUNNING\e[0m\n"
	fi
	
	pids=$(ps aux | grep "[m]inikube dashboard" | cut -c10-15 | tr -d ' ')
	if [[ "$pids" != "" ]]
	then
		printf "$FT_SERVICES_PREFIX Killing old minikube dashboard instances...\n"
		
		while read pid; do
			printf "$FT_SERVICES_PREFIX Killing PID: $pid\n"
			kill -9 "$pid" || true
		done <<< "$pids"
	else
		printf "$FT_SERVICES_PREFIX There are no old minikube dashboard instances currently running...\n"
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
			printf " \e[95mFAILED\e[0m\n"
			printf "$FT_SERVICES_PREFIX Failed to start the dashboard.\n"
	
			exit 3
		elif [[ "$log" = *"Opening"* ]]
		then
			printf " \e[95mDONE\e[0m\n"
			printf "$FT_SERVICES_PREFIX Dashboard started!\n"
			
			break
		fi
	done

	printf "$FT_SERVICES_PREFIX Enabling minikube addons...\n"
	
	minikube addons enable ingress
	minikube addons enable dashboard
	minikube addons enable metrics-server
}

function generate_tls_certificate()
{
	cert_file=$1
	key_file=$2
	to=$3
	
	printf "$FT_SERVICES_PREFIX Generating TLS certificates...\n"

	rm -rf "${cert_file}" "${key_file}"

	openssl req -newkey rsa:4096 -x509 -sha256 -days 3650 -nodes -out "${cert_file}" -keyout "${key_file}" -subj "/C=FR/ST=France/L=France/OU=42/OU=42/CN=42"

	sed -i $SED_EXTRA 's/__b64_cert__/'$(cat $cert_file | base64 | tr -d '\n')'/g' $to
	sed -i $SED_EXTRA 's/__b64_key__/'$(cat $key_file | base64 | tr -d '\n')'/g' $to
}

function generate_ftp_certificate()
{
	cert_file=$1
	key_file=$2
	to=$3
	
	printf "$FT_SERVICES_PREFIX Generating FTP certificates...\n"

	rm -rf "${cert_file}" "${key_file}"

	openssl req -new -x509 -days 3650 -nodes -out "${cert_file}" -keyout "${key_file}" -subj "/C=FR/ST=France/L=France/OU=42/OU=42/CN=42";

	sed -i $SED_EXTRA 's/__b64_cert__/'$(cat $cert_file | base64 | tr -d '\n')'/g' $to
	sed -i $SED_EXTRA 's/__b64_key__/'$(cat $key_file | base64 | tr -d '\n')'/g' $to
}

function generate_ssh_certificate()
{
	base_file=$1
	pub_file=$1".pub"
	to=$2
	
	printf "$FT_SERVICES_PREFIX Generating SSH keys...\n"

	rm -rf "${base_file}" "${pub_file}"

	ssh-keygen -b 521 -t ecdsa -f "${base_file}" -q -N ""

	sed -i $SED_EXTRA 's/__b64_private__/'$(cat $base_file | base64 | tr -d '\n')'/g' $to
	sed -i $SED_EXTRA 's/__b64_public__/'$(cat $pub_file | base64 | tr -d '\n')'/g' $to
}

function generate_ready_kustomization()
{
	from=$1
	to=$2
	
	clear_dir $to
	cp $from/*.yaml $to/
	
	ip=$(minikube ip)
	dashboard_url=$(cat srcs/logs/minikube_dashboard.log | grep Opening | awk '{ print $3 }')

	printf "$FT_SERVICES_PREFIX Generating kustomization with IP = $ip...\n"
	
	find $to -name "*.yaml" -type f -exec printf "Preparing file {}...\n" \;  -exec sed -i $SED_EXTRA 's/__ip__/'$ip'/g' {} \; -exec sed -i $SED_EXTRA 's+__dashboard_url__+'$dashboard_url'+g' {} \;
	
	if [[ $MAC_42 -eq 1 ]]
	then
		rm -rf $to/*.yaml$SED_EXTRA
	fi
}

function clear_dir()
{
	directory=$1
	
	rm -rf $directory/*.yaml
}

function print_info()
{
	ip=$(minikube ip)
	services=$(kubectl get services)
	
	ssh_ext_port=$(kubectl get services | grep nginx | grep "22:(\d+)" -o${GREP_EXTRA} | cut -c4-30)
	influxdb_ext_port=$(kubectl get services | grep influxdb | grep "8086:(\d+)" -o${GREP_EXTRA} | sed 's/:/ <--> /g')
	mysql_ext_port=$(kubectl get services | grep mysql | grep "3306:(\d+)" -o${GREP_EXTRA} | sed 's/:/ <--> /g')
	
	url_start="\e[50G\e[96m"
	
	printf "$FT_SERVICES_PREFIX\n"
	printf "$FT_SERVICES_PREFIX \e[97m	NGINX				\e[0m ${url_start}https://$ip/\e[0m\n"
	printf "$FT_SERVICES_PREFIX \e[97m	WORDPRESS			\e[0m ${url_start}https://$ip/\e[0m\n"
	printf "$FT_SERVICES_PREFIX \e[97m	PHPMYADMIN			\e[0m ${url_start}https://$ip/phpmyadmin/\e[0m\n"
	printf "$FT_SERVICES_PREFIX \e[97m	GRAFANA				\e[0m ${url_start}https://$ip/grafana/\e[0m\n"
	printf "$FT_SERVICES_PREFIX \e[97m	DASHBOARD			\e[0m ${url_start}https://$ip/dashboard\e[0m\n"
	printf "$FT_SERVICES_PREFIX\n"
	printf "$FT_SERVICES_PREFIX \e[97m	SSH					\e[0m ${url_start}ssh://root@$ip:$ssh_ext_port\e[0m\n"
	printf "$FT_SERVICES_PREFIX \e[97m	FTPS				\e[0m ${url_start}ftps://root@$ip:21\e[0m\n"
	printf "$FT_SERVICES_PREFIX\n"
	printf "$FT_SERVICES_PREFIX \e[97m	INFLUXDB			\e[0m ${url_start}internal: ${influxdb_ext_port}\e[0m\n"
	printf "$FT_SERVICES_PREFIX \e[97m	MYSQL				\e[0m ${url_start}internal: ${mysql_ext_port}\e[0m\n"
	printf "$FT_SERVICES_PREFIX\n"
	printf "$FT_SERVICES_PREFIX \e[97m	TELEGRAF			\e[0m ${url_start}no access\e[0m\n"
	printf "$FT_SERVICES_PREFIX\n"
}

printf "$FT_SERVICES_PREFIX Hello\n"

if [[ "$OPERATION" != "update" ]] && [[ "$OPERATION" != "delete" ]]
then
	start_minikube

	printf "$FT_SERVICES_PREFIX Generating TLS from templates...\n"
	cp $KUSTOMIZATION_TEMPLATES/*.yaml $KUSTOMIZATION/
	
	generate_tls_certificate $CERTIFICATES/common.crt $CERTIFICATES/common.key $KUSTOMIZATION/tls-https.yaml
	generate_ftp_certificate $CERTIFICATES/vsftpd.cert.pem $CERTIFICATES/vsftpd.key.pem $KUSTOMIZATION/tls-vsftpd.yaml
	generate_ssh_certificate $CERTIFICATES/ssh_host_ecdsa_key $KUSTOMIZATION/key-ssh.yaml
fi

generate_ready_kustomization $KUSTOMIZATION $KUSTOMIZATION_READY

if [[ "$OPERATION" == "delete" ]]
then
	printf "$FT_SERVICES_PREFIX Deleting...\n"
	
	kubectl delete configmap grafana-database
	kubectl delete -k $KUSTOMIZATION_READY
else
	printf "$FT_SERVICES_PREFIX Applying...\n"
	
	kubectl create configmap grafana-database --from-file=./srcs/databases/grafana.db
	kubectl apply -k $KUSTOMIZATION_READY

	print_info
fi

printf "$FT_SERVICES_PREFIX Done!\n"
