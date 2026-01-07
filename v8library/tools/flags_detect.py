#!/usr/bin/python3

def parse_line(line) :
    f = set()
    name = None
    l = line.split(' ')
    for v in l :
        if '-D' in v :
            f.add(v)
        elif '.cc' in v :
            name = v
        else :
            continue
    if None != name :
        return {name: f}
    return None

def main() :
    d = dict()
    file=open('build.log', 'r')
    for line in file:
        v = parse_line(line)
        if None != v :
            d.update(v)
    of = open("defenition.log", 'w')
    for key, value in d.items() :
        print(key, ' ', value, file=of)
    of.close()
    return 0

if __name__ == '__main__':
    main()
