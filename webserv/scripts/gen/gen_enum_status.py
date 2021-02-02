import re
import urllib.request
import ssl

regex = r"([A-Z_]+)\((\d+), .*, \"(.+)\"\),"

with urllib.request.urlopen("https://raw.githubusercontent.com/spring-projects/spring-framework/master/spring-web/src/main/java/org/springframework/http/HttpStatus.java", context=ssl._create_unverified_context()) as f:
    java_code = f.read().decode('utf-8')

print(java_code)

for match in re.finditer(regex, java_code, re.MULTILINE):
    print("static HttpStatus *{};".format(match.group(1)))

for match in re.finditer(regex, java_code, re.MULTILINE):
    print("ENUM_DEFINE(HttpStatus, {}, HttpStatus({}, \"{}\"));".format(match.group(1), match.group(2), match.group(3)))

longest = -1
for match in re.finditer(regex, java_code, re.MULTILINE):
    longest = max(longest, len(match.group(1)))

longest += 8;

for match in re.finditer(regex, java_code, re.MULTILINE):
    name = match.group(1);
    name += "/*" + ((longest - len(name) - 4) * " ") + "*/"
    
    print("DEFINE_HTTP_STATUS({}, {}, \"{}\");".format(name, match.group(2), match.group(3)))
