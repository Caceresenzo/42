output "eip_public_url" {
  value = "https://${aws_eip.ip.public_ip}/"
}

output "https_url" {
  value = "https://${local.domain}/"
}
