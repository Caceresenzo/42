import re

regex = r'PRINTF_MACRO\("Bla bla (.*?)",(.*?)\)\);'

test_str = open("raw_tests.txt").read()

matches = re.finditer(regex, test_str, re.MULTILINE)

for match in matches:
    format = match.group(1)
    arguments = match.group(2)
    if ' ' in format or 'o' in format or '+' in format:
        continue
    print("DO_TEST(__LINE__, \"{}\",{});".format(format, arguments))