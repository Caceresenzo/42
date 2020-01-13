import re

with open('keys.h', 'r') as content_file:
    content = content_file.read()
    
matches = re.finditer(r"# define KEY_(.*) (.*)", content, re.MULTILINE)

keys = [0] * 300

for  match in matches:
    keys[int(match.group(2))] = "\"{}\"".format(match.group(1))

for key in keys:
    print(str(key).replace("_", " ") + ",")