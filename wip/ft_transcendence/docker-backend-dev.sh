docker run \
  --name ft-transcendence-backend \
  -it \
  --net ft-transcendence \
  -v $(pwd)/backend:/app \
  -p 3001:3001 \
  --rm \
  ft-transcendence-base
