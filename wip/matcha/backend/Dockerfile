FROM maven:3.8-openjdk-18-slim

WORKDIR /app

COPY pom.xml ./
RUN mvn clean package -DskipTests

COPY . ./
RUN mvn clean package -DskipTests

EXPOSE 4567

CMD [ "java", "-jar", "target/matcha-latest-jar-with-dependencies.jar" ]
