docker run \
  --name ft-transcendence-nginx \
  -it \
  --net ft-transcendence \
  -v $(pwd)/docker/nginx/default.conf:/etc/nginx/conf.d/default.conf:ro \
  -p 80:80 \
  --rm \
  nginx
