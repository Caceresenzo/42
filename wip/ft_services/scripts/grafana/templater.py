import os

containers = [
	"influxdb",
	"grafana",
	"mysql",
	"phpmyadmin",
	"nginx",
	"wordpress",
	"ftps"
]

containers.sort()

template = open("grafana_dashboard.template.json", "r").read()

os.system("rm -rf outputs/*.json")

for container in containers:
	with open("outputs/{}.json".format(container), "w") as file:
		file.write(template.replace("__container__name__", container))