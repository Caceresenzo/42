docker run \
  --name ft-transcendence-frontend \
  -it \
  --net ft-transcendence \
  -v $(pwd)/frontend:/app \
  -p 3000:3000 \
  --rm \
  ft-transcendence-base
