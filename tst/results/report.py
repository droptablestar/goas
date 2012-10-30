# report.py
# Josh Reese
# Purdue University
# reese5@purdue.edu
#
# This program takes as input a results file to be compared to the previous
# results. The file should be formatted in the same fasion as org_results.txt.

import sys, re
from math import sqrt

MAX_S=len('Success pgres (30149.80, 28331.30)')

report = open('report.txt','w')

def main():
    global report
    results = ''
    if len(sys.argv) < 3:
        print 'Usage: python report.py <new_times> <query_set (scan, select, project, sort, all, full)> <flags (-diff-check)>>'
        exit()

    with open('org_times.txt','r') as f:
        o_lines = f.readlines()
    
    with open(sys.argv[1], 'r') as f:
        r_lines = f.readlines()
        
    o_lines = map(lambda x: x.strip('\n '), o_lines[1:])
    r_lines = map(lambda x: x.strip('\n'), r_lines)

    o2_lines = []
    r2_lines = []
    if sys.argv[2] == 'scan':
        for o in o_lines:
            if re.search('[0-9]+k?\_scan +',o.split('\t')[0]):
                o2_lines.append(o)

        for o in r_lines:
            if re.search('[0-9]+k?\_scan$',o.split('\t')[0]):
                r2_lines.append(o)
        o_lines = o2_lines
        r_lines = r2_lines

    elif sys.argv[2] == 'select':
        for o in o_lines:
            if re.search('[0-9]+k?\_scan\_select[0-9]+ *',o.split('\t')[0]):
                o2_lines.append(o)

        for o in r_lines:
            if re.search('[0-9]+k?\_scan\_select[0-9]+$',o.split('\t')[0]):
                r2_lines.append(o)
        o_lines = o2_lines
        r_lines = r2_lines

    elif sys.argv[2] == 'project':
        for o in o_lines:
            if re.search('[0-9]+k?\_scan\_project[0-9]+ *',o.split('\t')[0]):
                o2_lines.append(o)

        for o in r_lines:
            if re.search('[0-9]+k?\_scan\_project[0-9]+$',o.split('\t')[0]):
                r2_lines.append(o)
        o_lines = o2_lines
        r_lines = r2_lines

    elif sys.argv[2] == 'sort':
        for o in o_lines:
            if re.search('[0-9]+k?\_scan\_sort[0-9]+ *',o.split('\t')[0]):
                o2_lines.append(o)

        for o in r_lines:
            if re.search('[0-9]+k?\_scan\_sort[0-9]+$',o.split('\t')[0]):
                r2_lines.append(o)
        o_lines = o2_lines
        r_lines = r2_lines

    elif sys.argv[2] == 'all':
        for o in o_lines:
            if re.search('[0-9]+k?\_scan\_select\_project\_sort[0-9]+ *',o.split('\t')[0]):
                o2_lines.append(o)

        for o in r_lines:
            if re.search('[0-9]+k?\_scan\_select\_project\_sort[0-9]+$',o.split('\t')[0]):
                r2_lines.append(o)

        o_lines = o2_lines
        r_lines = r2_lines

    if '-diff-check' in sys.argv:
        diffCheck(map(lambda x: x.split('\t')[0].strip(' \t'), o_lines))

    # print
    # print
    # print r_lines
    # for line,r_line in zip(lines,res_lines):
    print 'Performing analysis for report...'
    for o_line,r_line in zip(o_lines,r_lines):
        o_line = o_line.split('\t')
        r_line = r_line.split('\t')

        # print r_line
        o_line = filter(lambda x: x != '', o_line)
        o_line[1:] = map(lambda x: float(x.strip(' ')), o_line[1:])
        r_line = filter(lambda x: x != '', r_line)
        r_line[1:] = map(lambda x: float(x), r_line[1:])

        r_stats = meanstdv(r_line[1:])

        pgres = False
        # check for failure against pgres
        if r_stats[0] > o_line[1]:
            results+='%s%s Fail pgres (%.2f, %.2f)' % \
                (o_line[0],' '*(MAX_S-len(o_line[0])),o_line[1],r_stats[0])
            pgres = True
        else:
            results+='%s%s Success pgres (%.2f, %.2f)' % \
                (o_line[0],' '*(MAX_S-len(o_line[0])),o_line[1],r_stats[0])
            pgres = True
        # fail against goas
        if r_stats[0] > o_line[3]:
            if pgres:
                results+='\tFail goas (%.2f, %.2f)\n' % \
                    (o_line[3], r_stats[0])
            else:
                results+='%s Fail goas (%.2f, %.2f)\n' % \
                    (o_line[0],o_line[3], r_stats[0])
        else:
            if pgres:
                results+='\tSuccess goas (%.2f, %.2f)\n' % \
                    (o_line[3], r_stats[0])
            else:
                results+='%s Success goas (%.2f, %.2f)\n' % \
                    (o_line[0],o_line[3], r_stats[0])

    print 'report.txt generated successfully!' 
    report.write(results)
    report.close()


def meanstdv(x):
    n, mean, std = len(x), 0, 0
    for a in x:
        mean = mean + a
    mean = mean / float(n)
    for a in x:
        std = std + (a - mean)**2
        std = sqrt(std / float(n-1))
    return mean, std

def diffCheck(files):
    import commands,os,time
    global report
    
    print 'Performing diff checks...'
    for name in files:
        x = commands.getoutput('diff -w ../tables/'+name+' ../new_tables/'+name)
        if x != '':
            report.write('Failed diff check: %s\n' % (name))
        time.sleep(.05)

    pass

if __name__ == '__main__':
    main()

    
