import random

test = open("test.txt", "w")
ans = open("our.txt", "w")
for i in range(1000):
    a = random.randint(0, pow(10, random.randint(1, 3200)))
    b = random.randint(0, pow(10, random.randint(1, 3200)))
    test.write(str(a) + '\n')
    test.write(str(b) + '\n')
    test.write("/\n")
    if b == 0:
        ans.write('Error\n')
    else:
        ans.write(str(a // b) + '\n')
# for i in range(100):
#     a = random.randint(0, pow(10, random.randint(1, 10)))
#     b = random.randint(0, pow(10, random.randint(1, 10)))
#     test.write(str(a) + '\n')
#     test.write(str(b) + '\n')
#     test.write("+\n")
#     ans.write(str(a + b) + '\n')
# for i in range(100):
#     a = random.randint(0, pow(10, random.randint(1, 10)))
#     b = random.randint(0, pow(10, random.randint(1, 10)))
#     test.write(str(a) + '\n')
#     test.write(str(b) + '\n')
#     test.write("-\n")
#     if (a < b):
#         ans.write('Error\n')
#     else:
#         ans.write(str(a - b) + '\n')
# for i in range(100):
#     a = random.randint(0, pow(10, random.randint(1, 10)))
#     b = random.randint(0, pow(10, random.randint(1, 10)))
#     test.write(str(a) + '\n')
#     test.write(str(b) + '\n')
#     test.write("=\n")
#     if (a == b):
#         ans.write('true\n')
#     else:
#         ans.write('false\n')
# for i in range(100):
#     a = random.randint(0, pow(10, random.randint(1, 10)))
#     b = random.randint(0, pow(10, random.randint(1, 10)))
#     test.write(str(a) + '\n')
#     test.write(str(b) + '\n')
#     test.write(">\n")
#     if (a > b):
#         ans.write('true\n')
#     else:
#         ans.write('false\n')
# for i in range(100):
#     a = random.randint(0, pow(10, random.randint(1, 100)))
#     b = random.randint(0, pow(10, random.randint(1, 100)))
#     test.write(str(a) + '\n')
#     test.write(str(b) + '\n')
#     test.write("<\n")
#     if (a < b):
#         ans.write('true\n')
#     else:
#         ans.write('false\n')

