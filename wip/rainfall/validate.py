import os

import click
import paramiko


def connect(
    hostname: str,
    port: int,
    username: str,
    password: str
):
    client = paramiko.SSHClient()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())

    try:
        client.connect(
            hostname,
            port=port,
            username=username,
            password=password
        )

        return True
    except paramiko.AuthenticationException:
        return False
    finally:
        client.close()


def to_username(n: int):
    return f"level{n}"


def read_flag(directory: str):
    with open(os.path.join(directory, "flag")) as fd:
        return fd.read().strip()


@click.command()
@click.option("--hostname", default="localhost", show_default=True)
@click.option("--port", default=4242, show_default=True)
def cli(
    hostname: str,
    port: int
):
    combos = {
        **{
            to_username(n): read_flag(to_username(n - 1))
            for n in range(1, 9 + 1)
        },
        "bonus0": read_flag(to_username(9))
    }

    for username, password in combos.items():
        print(f"{username}: trying password `{password}`")

        if connect(hostname, port, username, password):
            print(f"{username}: password OK")
            print()
        else:
            print(f"{username}: password KO")
            exit(1)


if __name__ == "__main__":
    cli()
