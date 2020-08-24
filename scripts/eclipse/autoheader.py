# name            : Auto-Header
# description     : Generate the header automatically
# toolbar         : Project Explorer

import os
import sys
import re
import math
from datetime import datetime
from datetime import date

loadModule('/System/Environment');
loadModule('/System/Resources');
loadModule('/System/UI');
loadModule('/System/Platform');
loadModule('/System/JVM');

TAB_SIZE = 4
PROTOTYPE_EXTRACT_REGEX = r"^(?!static)(.+?)( __attribute__\(\(.*\)\))?\n\t(\**)([a-z]+[\da-z_]*)\((.*)\)$"
DOT_AUTOHEADER = ".autoheader"
VERSION = 1.1


class CPrototype:
    
    def __init__(self, return_type, return_type_stars, name, parameters):
        self.return_type = return_type
        self.return_type_stars = return_type_stars
        self.name = name
        self.parameters = parameters if len(parameters) else "void"
    
    def tab_align(self):
        length = len(self.return_type) * 1.0
        extra = 1 if length % TAB_SIZE == 0 else 0
        
        return int(math.ceil(length / TAB_SIZE) + extra)
    
    def export(self, tab_align):
        return "".join([
            self.return_type,
            "\t" * int((tab_align + (1 if self.tab_align() < tab_align else 0))),
            "*" * self.return_type_stars,
            self.name,
            "(",
            self.parameters,
            ");"
        ]);
    
    def category(self, level=1):
        return "_".join(self.name.split("_")[:level])
    
    def __lt__(self, other):
        self_cat = self.category();
        other_cat = other.category();
        
        if self_cat != other_cat:
            return self_cat < other_cat
        
        return self.name < other.name


today = date.today()
now = datetime.now()

for project in getWorkspace().getProjects():
    if not project.isOpen():
        continue

    if not project.getFile(DOT_AUTOHEADER).exists():
        continue
    
    config_block_high = r"^#[ ]*define AUTO_HEADER_SECTION$"
    config_block_low = r"^#[ ]*undef AUTO_HEADER_SECTION$"
    config_auto_backup = "true"
    config_recursive_find = "true"
    config_debug_output = "false"
    config_header_file = None
    config_add_debug_output = "true"
    
    for line in readFile(project.getFile(DOT_AUTOHEADER)).split("\n"):
        property = line.split("=", 2)
        
        key = property[0]
        value = property[1]
        
        if key == "block-high":
            config_block_high = value
        elif key == "block-low":
            config_block_low = value
        elif key == "auto-backup":
            config_auto_backup = value
        elif key == "recursive-find":
            config_recursive_find = value
        elif key == "debug-output":
            config_debug_output = value
        elif key == "header-file":
            config_header_file = value
        elif key == "add-debug-output":
            config_add_debug_output = value
    
    if config_header_file is None or not project.getFile(config_header_file).exists():
        print project.getName() + ": No valid header file provided. (.autoheader, key: `header-file`)"
        continue
    
    print project.getName() + ": Generating..."
    
    header_file = project.getFile(config_header_file)
    
    def is_true(val):
        return val.lower() == "true"
    
    
    files = findFiles("*.c", project, is_true(config_recursive_find))
    
        
    prototypes = []
    
    for file in files:
        for match in re.finditer(PROTOTYPE_EXTRACT_REGEX, readFile(file), re.MULTILINE):
            prototypes.append(CPrototype(
                return_type=match.group(1),
                return_type_stars=len(match.group(3)),
                name=match.group(4),
                parameters=match.group(5),
            ))
    
    prototypes.sort()
    tabs_align = 1;
    for prototype in prototypes:
        tabs_align = max(tabs_align, prototype.tab_align())
    
    if is_true(config_debug_output):
        for prototype in prototypes:
            print " ".join([str(prototype.tab_align()), "-", prototype.category(), "-", prototype.export(tabs_align)])
    
    current_content = readFile(project.getFile(config_header_file))
    
    topEnd, bottomStart = None, None
    
    for match in re.finditer(config_block_high, current_content, re.MULTILINE):
        topEnd = match.end(0) + 1
        break;
    
    for match in re.finditer(config_block_low, current_content, re.MULTILINE):
        bottomStart = match.start(0) - 1
        break;
    
    if None in [ topEnd, bottomStart ]:
        print project.getName() + ": Bound not found.."
        continue
    
    
    top = current_content[:topEnd]
    bottom = current_content[bottomStart:]
    middle = ""
    
    if is_true(config_add_debug_output):
        middle = """/*
** Automatic header generation:
** - from {} file{}
** - found {} prototype{}
** - at {}, the {}
** - with version {}
*/

""".format(len(files), "s" if len(files) > 1 else "",
               len(prototypes), "s" if len(prototypes) > 1 else "",
               now.strftime("%H:%M:%S"), today.strftime("%B %d (%Y)"),
               VERSION)
    
    previous = None
    for index in range(len(prototypes)):
        prototype = prototypes[index];
        
        if previous is not None and previous.category() != prototype.category():
            middle += '\n';
        previous = prototype
        
        middle += prototype.export(tabs_align) + ('\n' if index != len(prototypes) - 1 else "")
    
    if is_true(config_auto_backup):
        writeFile(project.getFile(config_header_file + ".back-" + datetime.now().strftime("%Y%m%d%H%M%S")), current_content)
    
    writeFile(header_file, "".join([
        top,
        "\n",
        middle,
        "\n",
        bottom
    ]))
