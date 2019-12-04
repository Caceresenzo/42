import re

TEMPLATE_HERE = "// TEST HERES"

template_parts = open("main_template.c").read().split(TEMPLATE_HERE)
all_tests = open("raw_tests.txt").read()
matches = re.finditer(r'PRINTF_MACRO\("Bla bla (.*?)",(.*?)\)\);', all_tests, re.MULTILINE)

with open("main.c", "w") as file:
    file.write(template_parts[0])
    for match in matches:
        format = match.group(1)
        arguments = match.group(2)
        if ' ' in format or 'o' in format or '+' in format:
            continue
        line = "DO_TEST(__LINE__, \"{}\",{});".format(format, arguments)
        print(line)
        file.write(line + "\n")
    file.write(template_parts[1])