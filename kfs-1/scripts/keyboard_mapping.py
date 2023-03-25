# http://www.osfree.org/docs/cmdref/cmdref.2.0476.php
# https://regex101.com/r/AsEX15/1

import re

regex = r"^\s+(?:(\w{2,})|(?:(.)|(.)  (.)))\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(?:(\d+)|(?:\s+(\d+)\s+(\d+)\s+(\d+)))$"

test_str = ("     Esc       1      27     1      27     1      27     1\n"
    "     1  !      2      49     2      33                   120\n"
    "     2  @      3      50     3      64     3      0      121\n"
    "     3  #      4      51     4      35                   122\n"
    "     4  $      5      52     5      36                   123\n"
    "     5  %      6      53     6      37                   124\n"
    "     6  ^      7      54     7      94     7      30     125\n"
    "     7  &      8      55     8      38                   126\n"
    "     8  *      9      56     9      42                   127\n"
    "     9  (      10     57     10     40                   128\n"
    "     0  )      11     48     11     41                   129\n"
    "     -  _      12     45     12     95     12     31     130\n"
    "     =  +      13     61     13     43                   131\n"
    "     Backspace 14     8      14     8      14     127    14\n"
    "     Tab       15     9      15     0      148    0      165\n"
    "     Q         16     113    16     81     16     17     16\n"
    "     W         17     119    17     87     17     23     17\n"
    "     E         18     101    18     69     18     5      18\n"
    "     R         19     114    19     82     19     18     19\n"
    "     T         20     116    20     84     20     20     20\n"
    "     Y         21     121    21     89     21     25     21\n"
    "     U         22     117    22     85     22     21     22\n"
    "     I         23     105    23     73     23     9      23\n"
    "     O         24     111    24     79     24     15     24\n"
    "     P         25     112    25     80     25     16     25\n"
    "     [  {      26     91     26     123    26     27     26\n"
    "     ]  }      27     93     27     125    27     29     27\n"
    "     Enter     28     13     28     13     28     10     28\n"
    "    A          30     97     30     65     30     1      30\n"
    "    S          31     115    31     83     31     19     31\n"
    "    D          32     100    32     68     32     4      32\n"
    "    F          33     102    33     70     33     6      33\n"
    "    G          34     103    34     71     34     7      34\n"
    "    H          35     104    35     72     35     8      35\n"
    "    J          36     106    36     74     36     10     36\n"
    "    K          37     107    37     75     37     11     37\n"
    "    L          38     108    38     76     38     12     38\n"
    "    ;  :        39     59     39     58                   39\n"
    "    '  \"       40     39     40     34                   40\n"
    "    `  ˜       41     96     41     126                  41\n"
    "    \\  |       43     92     43     124    43     28     43\n"
    "    Z          44     122    44     90     44     26     44\n"
    "    X          45     120    45     88     45     24     45\n"
    "    C          46     99     46     67     46     3      46\n"
    "    V          47     118    47     86     47     22     47\n"
    "    B          48     98     48     66     48     2      48\n"
    "    N          49     110    49     78     49     14     49\n"
    "    M          50     109    50     77     50     13     50\n"
    "    ,  <       51     44     51     60                   51\n"
    "    .  >       52     46     52     62                   52\n"
    "    /  ?       53     47     53     63                   53\n"
    "    Space      57     32     57     32     57     32     57\n"
    "     *      55     42     55     42     150    0      55\n"
    "     Home   71     0      71     55     119    0              0\n"
    "     Up     72     0      72     56     141    0              0\n"
    "     PgUp   73     0      73     57     132    0              0\n"
    "     Minus  74     45     74     45     142    0      74\n"
    "     Left   75     0      75     52     115    0              0\n"
    "     5      76     0      76     53     143    0              0\n"
    "     Right  77     0      77     54     116    0              0\n"
    "     Plus   78     43     78     43     144    0      78\n"
    "     End    79     0      79     49     117    0              0\n"
    "     Down   80     0      80     50     145    0              0\n"
    "     PgDn   81     0      81     51     118    0              0\n"
    "     Ins    82     0      82     48     146    0              0\n"
    "     Del    83     0      83     46     147    0              0\n"
    "     /      224    47     224    47     149    0      164")

matches = re.finditer(regex, test_str, re.MULTILINE)

lines = []

for match in matches:
    long_name = match.group(1)
    letter = match.group(2)
    letter1 = match.group(3)
    letter2 = match.group(4)
    scan_code = match.group(5)
    ascii_code = match.group(6)
    shift_scan_code = match.group(7)
    shift_ascii_code = match.group(8) or 0
    ctrl_scan_code = match.group(10)
    ctrl_ascii_code = match.group(11) or 0
    alt_scan_code = match.group(9) or match.group(12)

    if long_name:
        comment = long_name
    elif letter:
        comment = letter
    else:
        comment = f"{letter1} {letter2}"
    
    lines.append((
        int(scan_code),
        f"[{scan_code}] = {{ {ascii_code}, {shift_ascii_code}, {ctrl_ascii_code} }}, // {comment}"
    ))

lines.sort(key=lambda x: x[0])

print(f"[0] = {{ 0, 0, 0 }},")

for index, (scan_code, line) in enumerate(lines):
    if index != 0:
        previous = lines[index - 1][0]
        
        if scan_code - 1 != previous:
            for i in range(previous + 1, scan_code):
                print(f"[{i}] = {{ 0, 0, 0 }},")
    
    print(line)
    
for i in range(scan_code + 1, 255):
    print(f"[{i}] = {{ 0, 0, 0 }},")
