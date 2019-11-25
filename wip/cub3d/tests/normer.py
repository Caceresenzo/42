import re
out = '''$result'''
matches = re.finditer(r'Norme: (.*?)$[\n]{0,1}Error', out, re.MULTILINE)
for match in matches:
    print(match.group(1))