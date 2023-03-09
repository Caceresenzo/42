DROP USER ''@'localhost';

CREATE DATABASE `wordpress`;
CREATE USER 'wordpress'@'%' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON `wordpress`.* TO 'wordpress'@'%';

FLUSH PRIVILEGES;
