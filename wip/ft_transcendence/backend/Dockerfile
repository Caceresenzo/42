FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y curl

RUN curl -sL https://deb.nodesource.com/setup_12.x | bash - && \
    apt-get install -y nodejs

WORKDIR /app
COPY package.json /app/

RUN npm install

COPY . /app/

CMD [ "npm", "run", "start" ]

HEALTHCHECK --start-period=5s --retries=3000 CMD curl --fail http://localhost:3001/ping || exit 1