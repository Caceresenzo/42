# coding=utf8

import re
import click
import subprocess
import dataclasses


@dataclasses.dataclass
class Symbol:
    
    name: str
    start: str
    end: str = None


NAME_REGEX = r"^[0]*([\da-f]{1,8}) <(.*?)>:$"
ADDRESS_REGEX = r"^[ ]*?([\da-f]{1,8}):"


@click.command()
@click.argument("file")
def cli(
    file: str
):
    output = subprocess.check_output(
        f"objdump -dC {file}; exit 0",
        stderr=subprocess.STDOUT,
        shell=True
    )
    
    symbols = list()
    last_symbol = None
    
    def commit():
        if last_symbol is None:
            return
        
        symbols.append(last_symbol)
        last_symbol = None
    
    for line in output.decode().split("\n"):
        if match := re.search(NAME_REGEX, line):
            name = match.group(2)
            
            try:
                index = name.index("(")
                name = name[:index]
            except ValueError:
                pass
            
            last_symbol = Symbol(
                name=name,
                start=match.group(1)
            )
            
            symbols.append(last_symbol)
        
        elif match := re.search(ADDRESS_REGEX, line):
            if last_symbol is not None:
                last_symbol.end = match.group(1)
    
    symbols.sort(key=lambda symbol: symbol.start)
    
    print("#include <kernel/trace.hpp>")
    print("")
    print("kfs::trace::symbol_t kfs::trace::symbols_table[] = {")
    
    for symbol in symbols:
        print(f'\t{{ 0x{symbol.start}, 0x{symbol.end}, "{symbol.name}" }},')
    
    print("\t{ 0, 0, 0 },")
    print("};")

    
if __name__ == '__main__':
    cli()
