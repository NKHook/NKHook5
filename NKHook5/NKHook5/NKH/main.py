# Made by mellowmarshe#0001
#
import glob
import os

# pip install robotpy-cppheaderparser
import CppHeaderParser

output = ""
errors = []

for i in glob.glob("./sdk/*.h"):
    try:
        b = os.path.basename(i)
        f, e = os.path.splitext(b)
        h = CppHeaderParser.CppHeader(i)
        c = h.classes[f]

        f = f"# {f}\n"

        param = False

        for m in c["methods"]["public"]:
            f += f"""## {m['rtnType']} {m['name']}({', '.join([f"{p['type']} {p['name']}".replace('&', '') for p in m['parameters']])})\n"""

        output += f"{f}\n"

    except CppHeaderParser.CppParseError as e:
        errors.append(f"{i}: {e}")

print(output)

f = open("./sdk.md", "a")
f.truncate(0)
f.write(output)
f.close()
