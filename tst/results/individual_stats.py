import sys, math

def main():
    if len(sys.argv) < 4:
        print "Usage: python individual_stats.py <input_file> <language> <type>"
        exit()

    for arg in sys.argv:
        print arg
    with open(sys.argv[1], 'r') as f:
        lines = f.readlines()

    new_file = open(sys.argv[2]+'_stats_'+sys.argv[3]+'.txt', 'w')
    for line in lines:
        line = line.strip('\n')
        line_nums = line.split('\t')[1:-1]
        av = avg(map(lambda x: float(x), line_nums))
        st = std(map(lambda x: float(x), line_nums))

        new_file.write('%s\t%.2f\t%.2f\n' %
                       (line.split('\t')[0], av, st))

def avg(nums):
    return sum(nums)/len(nums)

def std(nums):
    return math.sqrt(sum(map(lambda x: pow(x-avg(nums),2), nums)) / len(nums))
    
if __name__ == '__main__':
    main()
