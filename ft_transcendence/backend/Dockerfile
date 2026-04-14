FROM node:24-alpine

WORKDIR /app

COPY package*.json  ./

RUN npm install prom-client

COPY . .

CMD ["npm", "run", "start"]
