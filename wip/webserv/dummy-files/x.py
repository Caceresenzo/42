#!/usr/bin/env python3

import os
import sys

#print(os.environ.items(), file=sys.stderr)

print('Content-Type: text/html')
print('')
print('<html>')
print("""<style>
tr:nth-child(even) {
  background-color: #eee;
}
tr:nth-child(odd) {
  background-color: #fff;
}
th {
  color: white;
  background-color: black;
  width: 1hv;
}
</style>""")
print("""<body><table style="width: 100%">
  <tr>
    <th>#</th>
    <th>KEY</th>
    <th>VALUE</th>
  </tr>""")

inc = 0

for key, value in os.environ.items():
    inc += 1
    print(f"""<tr>
    <td style="white-space: nowrap"><p>{inc} / {len(os.environ)}</p></td>
    <td>{key}</td>
    <td>{value}</td>
  </tr>""")
    #print(key, file=sys.stderr)
print("</table>")

for i in range(50):
    print("<p style='display:none'>" + ("x" * 1024) + "</p> BLOCK #" + str(i) + "<br>")

print('</body>')
print('</html>')

#import time
#time.sleep(3)
#print("Hello")
#time.sleep(30)