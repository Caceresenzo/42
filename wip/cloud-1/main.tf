provider "aws" {
  region = var.region
}

provider "tls" {}

resource "tls_private_key" "private_key" {
  algorithm = "RSA"
  rsa_bits  = 4096
}

resource "aws_key_pair" "deployer" {
  key_name_prefix = "cloud1-"
  public_key = tls_private_key.private_key.public_key_openssh
}

resource "aws_security_group" "app_security_group" {
  name_prefix = "cloud1-sg-"
  ingress {
    description = "SSH Port"
    from_port = 22
    to_port = 22
    protocol = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
  ingress {
    description = "HTTP Port"
    from_port = 80
    to_port = 80
    protocol = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
  ingress {
    description = "HTTPS Port"
    from_port = 443
    to_port = 443
    protocol = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }
  egress {
    from_port        = 0
    to_port          = 0
    protocol         = "-1"
    cidr_blocks      = ["0.0.0.0/0"]
    ipv6_cidr_blocks = ["::/0"]
  }
}

resource "aws_instance" "app_instance" {
  ami = var.ami
  instance_type = var.instance_type
  availability_zone = "${var.region}a"
  associate_public_ip_address = true
  vpc_security_group_ids = [aws_security_group.app_security_group.id]
  key_name = aws_key_pair.deployer.id
  root_block_device {
    delete_on_termination = true
    encrypted = false
    volume_size = 20
    volume_type = "gp3"
  }
  user_data = <<-EOF
              #!/bin/bash
              apt update
              apt install -y apt-transport-https ca-certificates curl software-properties-common
              curl -fsSL https://download.docker.com/linux/ubuntu/gpg | apt-key add -
              add-apt-repository -y "deb [arch=amd64] https://download.docker.com/linux/ubuntu  $(lsb_release -cs)  stable"
              apt update
              apt install -y docker-ce
              systemctl start docker
              systemctl enable docker
              usermod -aG docker ubuntu
              mkdir /app
              chown -R ubuntu:ubuntu /app
              EOF
  tags = {
    Name = "cloud1-instance"
  }

  connection {  
    type        = "ssh"  
    user        = "ubuntu"  
    private_key = tls_private_key.private_key.private_key_openssh
    host        = aws_instance.app_instance.public_ip
    timeout     = "4m"  
  }

  provisioner "remote-exec" {  
    inline = [  
      "echo 'Waiting for user data script to finish'",  
      "cloud-init status --wait >/dev/null"  
    ]
  }

  provisioner "file" {
    source      = "docker-compose.yml"
    destination = "/app/docker-compose.yml"
  }

  provisioner "file" {
    source      = "services"
    destination = "/app/services"
  }

  provisioner "remote-exec" {
    inline = [
      "cd /app",
      "docker compose build --progress plain",
      "docker compose up -d"
    ]
  }
}
