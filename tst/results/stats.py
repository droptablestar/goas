# stats.py
# Josh Reese
# Purdue University
# reese5@purdue.edu
#
# This program takes as input a 3 tab delimited files of test results. This
# file should be formatted as such: query_name\tresult0\tresult1\t...\tresult9.
# From this file the average and standard deviation will be calculated for
# each query in each file.

import sys
from math import sqrt

RUNS=10
MAX_S=len('1000k_scan_select_project_sort12')
MAX_N=len('67390.30')
MAX_C=len('2280.0')

def main():
    if len(sys.argv) < 3:
        print 'Usage: python stats.py <filename1> <filename2> <filename3>'
        exit()

    res = open('times.txt','w')
    res.write(' '*MAX_S+'\tpgres\t\t\toas\n')
    
    with open(sys.argv[1], 'r') as f:
        p_lines = f.readlines()
    with open(sys.argv[2], 'r') as f:
        m_lines = f.readlines()
    with open(sys.argv[3], 'r') as f:
        c_lines = f.readlines()

    p_lines = map(lambda x: x.strip('\n'), p_lines)
    m_lines = map(lambda x: x.strip('\n'), m_lines)
    c_lines = map(lambda x: x.strip('\n'), c_lines)
    
    # for line,r_line in zip(lines,res_lines):
    for p_line,m_line,c_line in zip(p_lines,m_lines,c_lines):
        p_line = p_line.split('\t')
        m_line = m_line.split('\t')
        c_line = c_line.split('\t')

        p_line = filter(lambda x: x != '', p_line)
        p_line[1:] = map(lambda x: float(x), p_line[1:])
        m_line = filter(lambda x: x != '', m_line)
        m_line[1:] = map(lambda x: float(x), m_line[1:])
        c_line = filter(lambda x: x != '', c_line)
        c_line[1:] = map(lambda x: float(x), c_line[1:])

        p_stats = meanstdv(p_line[1:])
        m_stats = meanstdv(m_line[1:])
        c_stats = meanstdv(c_line[1:])

        print p_line[0], m_line[0], p_stats
        res.write("%s%s\t%.2f%s\t%.2f%s\t%.2f%s\t%.2f%s\t%.2f%s\t%.2f%s\n" % \
                      (m_line[0], ' '*(MAX_S-len(m_line[0])),
                       p_stats[0], ' '*(MAX_N-len(str(p_stats[0]))),
                       p_stats[1], ' '*(MAX_N-len(str(p_stats[1]))),
                       m_stats[0], ' '*(MAX_N-len(str(m_stats[0]))),
                       m_stats[1], ' '*(MAX_N-len(str(m_stats[1]))),
                       c_stats[0], ' '*(MAX_C-len(str(c_stats[0]))),
                       c_stats[1], ' '*(MAX_C-len(str(c_stats[1])))))

    res.close()

def meanstdv(x):
    n, mean, std = len(x), 0, 0
    for a in x:
        mean = mean + a
    mean = mean / float(n)
    for a in x:
        std = std + (a - mean)**2
        std = sqrt(std / float(n-1))
    return mean, std
    
if __name__ == '__main__':
    main()
