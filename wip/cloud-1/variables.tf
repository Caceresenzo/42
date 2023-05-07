variable "region" {
  type = string
  default = "us-east-1"
}

variable "ami" {
  type = string
  default = "ami-0557a15b87f6559cf"
}

variable "instance_type" {
  type = string
  default = "t2.micro"
}

variable "route53_zone_id" {
  type = string
  default = "Z04158572MIBMJFJ69A0S"
}

variable "domain" {
  type = string
  default = "cloud1.aws.caceresenzo.dev"
}

variable "email" {
  type = string
  default = "caceresenzo1502+cloud1@gmail.com"
}

variable "lets_encrypt_staging" {
  type = bool
  default = true
}
