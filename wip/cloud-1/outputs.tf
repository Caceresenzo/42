output "public_url" {
  value = "https://${aws_instance.app_instance.public_ip}/"
}

output "https_url" {
  value = "https://${var.domain}/"
}

# output "certificate_pem" {
#   value = acme_certificate.certificate.certificate_pem
# }

# output "issuer_pem" {
#   value = acme_certificate.certificate.issuer_pem
# }

# output "private_key_pem" {
#   value = nonsensitive(acme_certificate.certificate.private_key_pem)
# }