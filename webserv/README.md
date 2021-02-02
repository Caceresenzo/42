# webserv

A 42 project!

- [webserv](#webserv)
	- [Goal](#goal)
	- [Usage](#usage)
		- [Options](#options)
			- [Testing](#testing)
	- [Building](#building)
	- [Project stucture](#project-stucture)
	- [Tools](#tools)
		- [Simple TCP Proxy](#simple-tcp-proxy)
		- [slowcat](#slowcat)
	- [Can it run Wordpress?](#can-it-run-wordpress)
	- [Know issues](#know-issues)
		- [Always timeout-ing socket](#always-timeout-ing-socket)
	- [Team](#team)

## Goal

Re-make a simple NGINX, without blocking IO and with CGI support.

## Usage

```
./webserv -f conf.json
```

### Options

| Short | Long                           | Argument  | Default     | Supported                                          | Description                                                              |
|-------|--------------------------------|-----------|-------------|----------------------------------------------------|--------------------------------------------------------------------------|
| `-h`  | `--help`                       |           |             |                                                    | Display an help message                                                  |
| `-v`  | `--version`                    |           |             |                                                    | Display the build version                                                |
| `-l`  | `--log-level`                  | `<level>` | `INFO`      | `FATAL`, `ERROR`, `WARN`, `INFO`, `DEBUG`, `TRACE` | Change the log level                                                     |
| `-c`  | `--check`                      |           |             |                                                    | Only check the configuration file                                        |
| `-f`  | `--config-file`                | `<file>`  | `conf.json` |                                                    | Specify a configuration file                                             |
| `-m`  | `--ignore-mime-includes-error` |           |             |                                                    | Do not report an error when a `mime.includes` fail                       |
| `-s`  | `--ignore-graceful-stop`       |           |             |                                                    | Do not wait for a graceful shutdown when receiving an SIGINT (or CTRL+C) |
| `-n`  | `--no-color`                   |           |             |                                                    | Disable colored logging output                                           |

#### Testing

| Short | Long                           | Argument  | Default     | Supported                                          | Description                                                              |
|-------|--------------------------------|-----------|-------------|----------------------------------------------------|--------------------------------------------------------------------------|
| `-h`  | `--help`                       |           |             |                                                    | Display an help message                                                  |
| `-l`  | `--log-level`                  | `<level>` | `INFO`      | `FATAL`, `ERROR`, `WARN`, `INFO`, `DEBUG`, `TRACE` | Change the log level                                                     |
| `-c`  | `--continue`                   |           |             |                                                    | Do not stop at the first failed test                                     |
| `-p`  | `--print-location`             |           |             |                                                    | Print the test methods location in their files                           |

## Building

Even if the code is in the `/source` directory, a proxying makefile is available at the root of the project.

Some of the available commands are:
| Command              | Description                                                           |
|----------------------|-----------------------------------------------------------------------|
| `make` or `make all` | Build the project                                                     |
| `make clean`         | Clean the compiled object files                                       |
| `make fclean`        | Clean the compiled object files and the executable                    |
| `make re`            | Clean the project and compile everything again                        |
| `make rej`           | Same as `make re`, but with `-j $(nproc)`                             |
| `make update`        | Find for `.cpp` files and update the project's makefile automatically |
| `make run`           | Compile and run the project                                           |
| `make test`          | Compile and run the tests                                             |
| `make test-configs`  | Compile and run the configuration tests                               |
| `make docker-run`    | Start a throw-away docker container with the projet.                  |
| `make docker-test`   | Start a throw-away docker with the 42's included testing program      |
| `make siege`         | Stress a running webserv with the 'siege' program                     |

## Project stucture

| Directory             | Description                                        |
|-----------------------|----------------------------------------------------|
| /docker               | Dockerfiles used for various things (e.g. testing) |
| /dummy-files          | Sambles files used for testing                     |
| /research             | Research and explanations in various languages     |
| /scripts              | Helping scripts                                    |
| /source               | Source directory                                   |
| /source/buffer        | Byte buffer with FD integration                    |
| /source/config/block  | Possible configuration blocks                      |
| /source/http          | HTTP related classes and logic                     |
| /source/io            | IO releated classes                                |
| /source/json          | JSON parser and type classes                       |
| /source/libs/ft       | A small extract of libft                           |
| /source/log           | Logging                                            |
| /source/main          | main() versions (normal and test)                  |
| /source/net/address   | Networking Address classes (4, 6, Socket)          |
| /source/nio           | Non-blocking IO                                    |
| /source/options       | CLI parser                                         |
| /source/os            | OS related file                                    |
| /source/tests/units   | Testing units used with `make test`                |
| /source/tests/configs | Invalid config files used with `make test-configs` |
| /source/unit          | Unit classes                                       |
| /source/util          | Utilities classes and helpers                      |
| /tools                | Tools used to help the development                 |

## Tools

### Simple TCP Proxy

Used to look at exactly what is send through a socket.

### slowcat

cat, but slower.

## Can it run Wordpress?

Yes. The docker even have one included with a MySQL ready to be used to install Wordpress on it! Do `make docker-run` and visit [http://localhost:80/wordpress](http://localhost/wordpress). (v. 5.6)

## Know issues

### Always timeout-ing socket

Chrome always connect a second socket in case there is an immediate request to do. In contrary, if no such request need to be done, the socket is leaved empty without any data send and/or received. ([source](https://stackoverflow.com/a/5734486/7292958))

## Team

- [Alice TÊTU](https://profile.intra.42.fr/users/atetu)
- [Enzo CACERES](https://profile.intra.42.fr/users/ecaceres)
- [Romain SANCHEZ](https://profile.intra.42.fr/users/rosanche)