DROP USER ''@'localhost';

CREATE DATABASE `wordpress`;
CREATE USER 'wordpress'@'%' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON `wordpress`.* TO 'wordpress'@'%';

CREATE DATABASE `phpmyadmin`;
CREATE USER 'phpmyadmin'@'%' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON *.* TO 'phpmyadmin'@'%';

FLUSH PRIVILEGES;
