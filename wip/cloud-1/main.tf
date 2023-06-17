data "aws_route53_zone" "zone" {
  zone_id = var.route53_zone_id
}

locals {
  domain = "${var.prefix}.${data.aws_route53_zone.zone.name}"
}

resource "tls_private_key" "private_key" {
  algorithm = "RSA"
  rsa_bits  = 4096
}

resource "random_password" "wordpress_database_user" {
  length = 32
  special = false
}

resource "random_password" "phpmyadmin_database_user" {
  length = 32
  special = false
}

resource "aws_key_pair" "deployer" {
  key_name_prefix = "${var.prefix}-"
  public_key = tls_private_key.private_key.public_key_openssh
}

resource "aws_eip" "ip" {
  vpc = true
  public_ipv4_pool = "amazon"
  
  tags = {
    Name = "${var.prefix}-ip"
  }
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

resource "aws_ebs_volume" "app_data" {
  availability_zone = "${var.region}a"
  size = 20
  type = "gp3"
  encrypted = false
}

resource "aws_instance" "app_instance" {
  ami = var.ami
  instance_type = var.instance_type
  availability_zone = "${var.region}a"
  associate_public_ip_address = true
  vpc_security_group_ids = [
    aws_security_group.app_security_group.id
  ]
  key_name = aws_key_pair.deployer.id
  root_block_device {
    delete_on_termination = true
    encrypted = false
    volume_size = 10
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
    type = "ssh"  
    user = "ubuntu"  
    private_key = tls_private_key.private_key.private_key_openssh
    host = aws_instance.app_instance.public_ip
    timeout = "4m"  
  }

  provisioner "remote-exec" {  
    inline = [  
      "echo 'Waiting for user data script to finish'",  
      "cloud-init status --wait >/dev/null"  
    ]
  }
}

resource "aws_volume_attachment" "app_data_attachment" {
  device_name = "/dev/sdh"
  volume_id = aws_ebs_volume.app_data.id
  instance_id = aws_instance.app_instance.id
  skip_destroy = true
  stop_instance_before_detaching = true
}

resource "aws_eip_association" "app_eip" {
  instance_id = aws_instance.app_instance.id
  allocation_id = aws_eip.ip.id
}

resource "null_resource" "compose_up" {
  triggers = {
    instance_id = aws_instance.app_instance.id
  }

  connection {
    type = "ssh"  
    user = "ubuntu"  
    private_key = tls_private_key.private_key.private_key_openssh
    host = aws_eip_association.app_eip.public_ip
    timeout = "4m"
  }

  provisioner "file" {
    content = <<-EOF
      WORDPRESS_DATABASE_PASSWORD=${random_password.wordpress_database_user.result}
      PHPMYADMIN_DATABASE_PASSWORD=${random_password.phpmyadmin_database_user.result}
    EOF
    destination = "/app/.env"
  }

  provisioner "file" {
    source = "docker-compose.yml"
    destination = "/app/docker-compose.yml"
  }

  provisioner "file" {
    source = "services"
    destination = "/app/services"
  }

  provisioner "file" {
    content = acme_certificate.certificate.certificate_pem
    destination = "/app/services/gateway/etc/ssl/certs/nginx.crt"
  }

  provisioner "file" {
    content = acme_certificate.certificate.private_key_pem
    destination = "/app/services/gateway/etc/ssl/private/nginx.key"
  }

  provisioner "remote-exec" {
    inline = [
      "echo '/dev/xvdh     /app/data   auto    rw,user,auto    0    0' | sudo tee -a /etc/fstab",
      "sudo mkfs.xfs /dev/xvdh || true",
      "cd /app",
      "mkdir -p data",
      "sudo mount data",
      "docker compose build --progress plain",
      "docker compose up --detach"
    ]
  }

  depends_on = [
    aws_eip_association.app_eip,
    aws_volume_attachment.app_data_attachment,
    acme_certificate.certificate,
  ]
}

resource "aws_route53_record" "www" {
  zone_id = var.route53_zone_id
  name = local.domain
  type = "A"
  ttl = 60
  records = [
    aws_eip.ip.public_ip
  ]
}

resource "tls_private_key" "webmaster_private_key" {
  algorithm = "RSA"
}

resource "acme_registration" "registration" {
  account_key_pem = tls_private_key.webmaster_private_key.private_key_pem
  email_address = var.email
}

resource "acme_certificate" "certificate" {
  account_key_pem = acme_registration.registration.account_key_pem
  common_name = local.domain

  dns_challenge {
    provider = "route53"
  }
}
