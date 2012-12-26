# report.py
# Josh Reese
# Purdue University
# reese5@purdue.edu
#
# This program takes as input the type of files to be examined
# (run-time / compile-time). This will read in all the stats files
# and perform a stats analysis.

import sys, re, os
from math import sqrt

MAX_S=len('1000k_scan_select_project_sort12')
MAX_T=len('10425.80')
report = open('report.txt','w')
files = []
lines = []
names = []

def main():
    global report
    results = ''
    if len(sys.argv) < 3:
        print 'Usage: python report.py <type (r / c)> <query_set (scan, select, project, sort, all, full)> <flags (-diff-check)>>'
        exit()

    for d in os.listdir('./'):
        if re.search('.*stats\_'+sys.argv[1]+'.txt', d):
            files.append(d)
            names.append(d[:d.find('_')])
    print files
    print names
    for fi in files:
        with open(fi, 'r') as f:
            lines.append(f.readlines())

    # write the header to the report (names of the languages)
    report.write('%s\t' % (' '*MAX_S))
    for n in names:
        report.write('%s%s\t' % (n,' '*(MAX_T-len(n))))
    report.write('\n')
    # with open('times.txt','r') as f:
    #     o_lines = f.readlines()
    
    # with open(sys.argv[1], 'r') as f:
    #     r_lines = f.readlines()

    o_lines = []
    for line in lines:
        o_lines.append(map(lambda x: x.strip('\n '), line))
    # r_lines = map(lambda x: x.strip('\n'), r_lines)
    o2_lines = []
    tuples = []
    if sys.argv[2] == 'scan':
        j = 0
        for o in lines[0]:
            if re.search('t?[0-9]+k?\_scan$',o.split('\t')[0]):
                # print repr(o.split('\t')[0])
                for i in range(len(lines)):
                    if j<len(lines[i]):
                        o2_lines.append(lines[i][j].strip('\n'))
                # print o2_lines
                tuples.append(tuple(i for i in o2_lines))
                o2_lines = []
            j += 1
    print tuples
    #     o_lines = o2_lines
    #     r_lines = r2_lines

    # elif sys.argv[2] == 'select':
    #     for o in o_lines:
    #         if re.search('[0-9]+k?\_scan\_select[0-9]+ *',o.split('\t')[0]):
    #             o2_lines.append(o)

    #     for o in r_lines:
    #         if re.search('[0-9]+k?\_scan\_select[0-9]+$',o.split('\t')[0]):
    #             r2_lines.append(o)
    #     o_lines = o2_lines
    #     r_lines = r2_lines

    # elif sys.argv[2] == 'project':
    #     for o in o_lines:
    #         if re.search('[0-9]+k?\_scan\_project[0-9]+ *',o.split('\t')[0]):
    #             o2_lines.append(o)

    #     for o in r_lines:
    #         if re.search('[0-9]+k?\_scan\_project[0-9]+$',o.split('\t')[0]):
    #             r2_lines.append(o)
    #     o_lines = o2_lines
    #     r_lines = r2_lines

    # elif sys.argv[2] == 'sort':
    #     for o in o_lines:
    #         if re.search('[0-9]+k?\_scan\_sort[0-9]+ *',o.split('\t')[0]):
    #             o2_lines.append(o)

    #     for o in r_lines:
    #         if re.search('[0-9]+k?\_scan\_sort[0-9]+$',o.split('\t')[0]):
    #             r2_lines.append(o)
    #     o_lines = o2_lines
    #     r_lines = r2_lines

    # elif sys.argv[2] == 'all':
    #     for o in o_lines:
    #         if re.search('[0-9]+k?\_scan\_select\_project\_sort[0-9]+ *',o.split('\t')[0]):
    #             o2_lines.append(o)

    #     for o in r_lines:
    #         if re.search('[0-9]+k?\_scan\_select\_project\_sort[0-9]+$',o.split('\t')[0]):
    #             r2_lines.append(o)

    #     o_lines = o2_lines
    #     r_lines = r2_lines

    # if '-diff-check' in sys.argv:
    #     diffCheck(map(lambda x: x.split('\t')[0].strip(' \t'), o_lines))

    # # print
    # # print
    # # print r_lines
    # # for line,r_line in zip(lines,res_lines):
    # print 'Performing analysis for report...'
    # for o_line,r_line in zip(o_lines,r_lines):
    #     o_line = o_line.split('\t')
    #     r_line = r_line.split('\t')

    #     # print r_line
    #     o_line = filter(lambda x: x != '', o_line)
    #     o_line[1:] = map(lambda x: float(x.strip(' ')), o_line[1:])
    #     r_line = filter(lambda x: x != '', r_line)
    #     r_line[1:] = map(lambda x: float(x), r_line[1:])

    #     r_stats = meanstdv(r_line[1:])

    #     pgres = False
    #     # check for failure against pgres
    #     if r_stats[0] > o_line[1]:
    #         results+='%s%s Fail pgres (%.2f, %.2f)' % \
    #             (o_line[0],' '*(MAX_S-len(o_line[0])),o_line[1],r_stats[0])
    #         pgres = True
    #     else:
    #         results+='%s%s Success pgres (%.2f, %.2f)' % \
    #             (o_line[0],' '*(MAX_S-len(o_line[0])),o_line[1],r_stats[0])
    #         pgres = True
    #     # fail against goas
    #     if r_stats[0] > o_line[3]:
    #         if pgres:
    #             results+='\tFail goas (%.2f, %.2f)\n' % \
    #                 (o_line[3], r_stats[0])
    #         else:
    #             results+='%s Fail goas (%.2f, %.2f)\n' % \
    #                 (o_line[0],o_line[3], r_stats[0])
    #     else:
    #         if pgres:
    #             results+='\tSuccess goas (%.2f, %.2f)\n' % \
    #                 (o_line[3], r_stats[0])
    #         else:
    #             results+='%s Success goas (%.2f, %.2f)\n' % \
    #                 (o_line[0],o_line[3], r_stats[0])

    for t in tuples:
        print 't',t
        queries = map(lambda x: x.split('\t')[0], t)
        avgs = map(lambda x: x.split('\t')[1], t)
        stds = map(lambda x: x.split('\t')[2], t)
        print avgs
        print stds
        minavg = sys.maxint
        minavgindex = 0
        for a in range(len(avgs)):
            print float(avgs[a]), minavg
            if float(avgs[a]) < minavg:
                minavg = float(avgs[a])
                minavgindex = a
            print minavg, minavgindex, names[minavgindex],queries[0]
        report.write('%s\t' %
                     (queries[0]+' '*(MAX_S-len(queries[0]))))
        for av in avgs:
            report.write('%.2f%s\t' % (float(av),' '*(MAX_T-len(av))))
        report.write('WINNER: %s\n' % names[minavgindex])
                         
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

    
