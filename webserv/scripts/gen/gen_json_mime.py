import json
import urllib.request

with urllib.request.urlopen("https://raw.githubusercontent.com/micnic/mime.json/master/index.json") as f:
    raw_json = f.read().decode('utf-8')

root = json.loads(raw_json)

typeByExtensions = {}

for key, value in root.items():
    arr = typeByExtensions.get(value, [])
    arr.append(key)
    
    typeByExtensions[value] = arr
    
print(json.dumps(typeByExtensions, indent=4))
    
    