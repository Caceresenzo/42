docker network create ft-transcendence

docker run \
  --name ft-transcendence-mysql \
  --net ft-transcendence \
  -e MYSQL_ROOT_PASSWORD=password \
  -e MYSQL_ROOT_HOST='%' \
  -e MYSQL_DATABASE=ft_transcendence \
  -p 3306:80 \
  -d \
  mysql:5

docker run \
  --name ft-transcendence-phpmyadmin \
  --net ft-transcendence \
  -e PMA_HOST=ft-transcendence-mysql \
  -e PMA_USER=root \
  -e PMA_PASSWORD=password \
  -p 5050:80 \
  -d \
  phpmyadmin:latest