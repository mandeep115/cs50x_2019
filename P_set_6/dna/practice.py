import re
import csv
from sys import exit, argv

if len(argv) != 3:
    print("Usage .\\dna.py database sequence")
    exit(0)

database = argv[1]
sequence_file = argv[2]

DATA = {}
str_line = []
str_lenghts = []

# with open(database, "r") as database_file:
#     for row in csv.DictReader(database_file):
#         DATA[row["name"]] = row[i for i ]

with open(database, "r") as database_file:
    for row in database_file:
        each_char = row.split(",")
        name = each_char[0]
        STR = each_char
        STR.pop(0)
        STR[-1] = STR[-1].strip('\n')
        # name = re.search("", row, "i")
        # STR = re.search("*", row)
        DATA[name] = STR

with open(sequence_file, "r") as f:
    for row in f:
        row = row.strip('\n')
        str_line.append(row)

# print(str_line)
# print(DATA['name'])

for STR in DATA['name']:
    # STR length
    str_lnegth = len(re.findall(STR, str_line[0]))
    str_lenghts.append(str(str_lnegth))
    print(str_lenghts)

for each_name in DATA:
    if DATA[each_name] == str_lenghts:
    # if cmp(DATA[each_name], str_lenghts):
        print(f"{each_name}")
    # print(f"{DATA[each_name]} : {str_lenghts}")
