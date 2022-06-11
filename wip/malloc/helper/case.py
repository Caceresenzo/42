import re

variables = set(["_0x0"])

print("void *_0x0 = NULL;")

with open("case.log", "r") as fd:
    for line in fd:
        line: str = line.strip()
        
        if line.startswith("malloc"):
            match = re.search(r"malloc\(size=(\d+)\): (0x[\da-f]+)", line)
            size = match.group(1)
            ptr = match.group(2)
            
            var = f"_{ptr}"
            if var not in variables:
                print("void *", end="")
                variables.add(var)
            
            print(f"{var} = xmalloc({size});")
        
        elif line.startswith("free"):
            match = re.search(r"free\(ptr=(0x[\da-f]+)\)", line)
            ptr = match.group(1)
            
            var = f"_{ptr}"
            if var not in variables:
                print("// ", end="")
            
            print(f"xfree({var});")
        
        elif line.startswith("realloc"):
            match = re.search(r"realloc\(ptr=([0x\da-f]+)\): malloc\(size=(\d+)\): ([0x\da-f]+)", line)
            ptr = match.group(1)
            size = match.group(2)
            new_ptr = match.group(3)
            
            var = f"_{ptr}"
            
            new_var = f"_{new_ptr}"
            if new_var not in variables:
                print("void *", end="")
                variables.add(new_var)
            
            print(f"{new_var} = xrealloc({var}, {size});")
        
        else:
            print(f"// {line}")
            
