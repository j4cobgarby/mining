# This creates files and generates their contents for each filename in
# the file 'forscript', which should be in the same directory as this.
# Create it, if it's not there.
# The generated files represent the .cpp implementation of items
# Fill forscript like this, for example
#
# forscript: '''
#
# SomeItem_i.cpp
# SomeOtherItem_i.cpp
#
# '''

with open("forscript") as f:
    content = f.readlines()
content = [n.strip() for n in content]

towrite = """\
#include "../include/ItemTypes.hpp"

void {0}::leftclick() {{
}}

void {0}::rightclick() {{
}}

inline bool {0}::canBreakBlock(size_t block_id) {{
    return true;
}}

inline bool {0}::canHarvestBlock(size_t block_id) {{
    return true;
}}
"""

for name in content:
    f = open(name, "w+")
    f.write(towrite.format(name.split('.')[0]))
    f.close()

