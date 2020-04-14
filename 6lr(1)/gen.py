import random

test = open("test.txt", "w")
ans = open("out.txt", "w")
for i in range(10):
    a = random.randint(0, pow(10, random.randint(1, 1000)))
    b = random.randint(0, 10)
    test.write(str(a) + '\n')
    test.write(str(b) + '\n')
    test.write("^\n")
    if b == 0 and a == 0:
        ans.write('Error\n')
    else:
        ans.write(str(pow(a, b)) + '\n')

for i in range(10):
    a = random.randint(0, pow(10, random.randint(1, 10000)))
    b = random.randint(0, pow(10, random.randint(1, 10000)))
    test.write(str(a) + '\n')
    test.write(str(b) + '\n')
    test.write("/\n")
    if b == 0:
        ans.write('Error\n')
    else:
        ans.write(str(a // b) + '\n')
for i in range(10):
    a = random.randint(0, pow(10, random.randint(1, 10000)))
    b = random.randint(0, pow(10, random.randint(1, 10000)))
    test.write(str(a) + '\n')
    test.write(str(b) + '\n')
    test.write("+\n")
    ans.write(str(a + b) + '\n')
for i in range(10):
    a = random.randint(0, pow(10, random.randint(1, 10000)))
    b = random.randint(0, pow(10, random.randint(1, 10000)))
    test.write(str(a) + '\n')
    test.write(str(b) + '\n')
    test.write("-\n")
    if (a < b):
        ans.write('Error\n')
    else:
        ans.write(str(a - b) + '\n')
for i in range(10):
    a = random.randint(0, pow(10, random.randint(1, 10000)))
    b = random.randint(0, pow(10, random.randint(1, 10000)))
    test.write(str(a) + '\n')
    test.write(str(b) + '\n')
    test.write("=\n")
    if (a == b):
        ans.write('true\n')
    else:
        ans.write('false\n')
for i in range(10):
    a = random.randint(0, pow(10, random.randint(1, 10000)))
    b = random.randint(0, pow(10, random.randint(1, 10000)))
    test.write(str(a) + '\n')
    test.write(str(b) + '\n')
    test.write(">\n")
    if (a > b):
        ans.write('true\n')
    else:
        ans.write('false\n')
for i in range(10):
    a = random.randint(0, pow(10, random.randint(1, 10000)))
    b = random.randint(0, pow(10, random.randint(1, 10000)))
    test.write(str(a) + '\n')
    test.write(str(b) + '\n')
    test.write("<\n")
    if (a < b):
        ans.write('true\n')
    else:
        ans.write('false\n')
