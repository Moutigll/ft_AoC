with open('day09/input.txt') as f:
    lines = [int(x) for l in f.readlines() for x in l.rstrip('\n')]

def sum_n(a, b):
    return (b-a+1)*(a+b)//2

j = 0
b = 0
res = 0
id = len(lines)//2
x = lines[len(lines)-1]
for i in range(len(lines)//2):
    if len(lines)-2*j-1 - 2*i == 0:
        res += sum_n(b, b+x-1)*i
        break
    nb = b + lines[2*i]
    res += sum_n(b, nb-1)*i
    b = nb
    space = lines[2*i+1]
    while space > 0:
        if x > space:
            nb = b + space
            res += sum_n(b, nb-1)*id
            x -= space
            space = 0
        else:
            nb = b + x
            res += sum_n(b, nb-1)*id
            id -= 1
            space -= x
            j += 1
            x = lines[len(lines)-2*j-1]
        b = nb
print(res)
