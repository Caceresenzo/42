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


def to_bonus(n: int):
    return f"bonus{n}"


def read_flag(directory: str):
    path = os.path.join(directory, "flag")

    if not os.path.exists(path):
        return None
    
    with open(path) as fd:
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
        to_bonus(0): read_flag(to_username(9)),
        **{
            to_bonus(n): read_flag(to_bonus(n - 1))
            for n in range(1, 3 + 1)
        },
        "end": read_flag(to_bonus(3))
    }

    for username, password in combos.items():
        if password is None:
            print(f"{username}: skip since no password")
            print()
            continue

        print(f"{username}: trying password `{password}`")

        if connect(hostname, port, username, password):
            print(f"{username}: password OK")
            print()
        else:
            print(f"{username}: password KO")
            exit(1)


if __name__ == "__main__":
    cli()
