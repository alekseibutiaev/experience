#!/usr/bin/python3

def parse_line(line) :
    flags_set = set()
    name = ""
    l = line.split(' ')
    for v in l :
        if 0 == v.find('-D') :
            flags_set.add(v)
        elif 0 != v.find('.cc')
            name = v
    return {}



def main() :
    d = dict()
    d[1]="one"
    d[2]="two"
    for key, value in d.items():
        print(key, '=', value)   
    file=open('/home/butiaev/v8/v8_library/build.log', 'r')
    for line in file:
        parse_line(line)


if __name__ == '__main__':
    main()
