terraform {
  required_providers {
    acme = {
      source  = "vancluever/acme"
    }
  }
}

provider "aws" {
  region = var.region
}

provider "tls" {}

provider "acme" {
  server_url = "https://acme${var.lets_encrypt_staging ? "-staging" : ""}-v02.api.letsencrypt.org/directory"
}
