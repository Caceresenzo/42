import re
import requests

MEMBERS_SECTION_REGEX = r"<section id=\"functions\">(.*?)<\/section>"
MEMBERS_REGEX = r"<dl class=\"links\"><dt><a href= \"(.*?)\"><b>(.*?)<\/b><\/a><\/dt><dd>(.*?)<span class=\"typ\">(.*?)<\/span><\/dd><\/dl>"
C_PROTOTYPE_REGEX = r"<div class=\"C_prototype\"><pre>[\s]*(.*?)<\/pre><\/div>"
C_PROTOTYPE2_REGEX = r"<div class=\"C_prototype\"><div class=\"C_SwitchCases\">[\s]*<div title=\"C\+\+98\">[\s]*<pre>[\s]*(.*?)[\s]*<\/pre><\/div>.*<\/div>[\s]*<\/div>"

CONTAINERS = [
#    "list",
    "vector",
#    "map",
#    "stack",
#    "deque"
]

REFERENCE_URL = "https://www.cplusplus.com"
CONTAINER_REFERENCE_URL_FORMAT = REFERENCE_URL + "/reference/{container}/{container}/"

for container in CONTAINERS:
    url = CONTAINER_REFERENCE_URL_FORMAT.format(container = container)
    print(" --- {}: {}---".format(container, url))
    
    containerPageHtml = requests.get(url).text

    for match in re.finditer(MEMBERS_SECTION_REGEX, containerPageHtml, re.MULTILINE | re.DOTALL):
        sectionHtml = match.group(1);

        for match in re.finditer(MEMBERS_REGEX, sectionHtml, re.MULTILINE | re.DOTALL):
            member_reference_url = REFERENCE_URL + match.group(1);
            member_name = match.group(2);
            
            if "C++11" in member_name:
                continue
            
            member_short_description = match.group(3);
            member_scope = match.group(4);
            
            memberPageHtml = requests.get(member_reference_url).text
            
            found = False
            for regex in [ C_PROTOTYPE_REGEX, C_PROTOTYPE2_REGEX ]:
                for match in re.finditer(regex, memberPageHtml, re.MULTILINE | re.DOTALL):
                    found = True
                    
                    for line in match.group(1).split("\n"):
                        print(line.replace("&lt;", "<").replace("&gt;", ">").replace("&amp;", "&").strip())
            
            if not found:
                print("// nothing found for: {}".format(member_name))