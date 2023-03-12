output "public_url" {
  value = "https://${aws_instance.app_instance.public_ip}/"
}
