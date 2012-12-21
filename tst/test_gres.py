import commands,os,time,sys,re

# names = os.listdir('pgres_queries/select/')
times = []
RUNS = 10

# os.system('purge')
def main():
    global times
    with open('results/g_times.txt','w') as f:
        pass
    if len(sys.argv) < 2:
        print 'Enter operator(s) to test (scan, select, project, sort, all, full)'
        exit()

    rootDir = '.'
    for dirN, subDir, fName in os.walk('pgres_queries'):
        # just scanning
        if sys.argv[1] == 'scan' and '0' not in dirN:
            continue
        if sys.argv[1] == 'select' and '1' not in dirN:
            continue
        if sys.argv[1] == 'project' and '2' not in dirN:
            continue
        if sys.argv[1] == 'sort' and '3' not in dirN:
            continue
        if sys.argv[1] == 'all' and '4' not in dirN:
            continue
        
        if dirN != 'pgres_queries/0scan':
            names = [[int(x[x.find('t')+1:x.find('s')].strip('k_')),int(re.sub('t[0-9]+[a-z\_]+','',x)),x] for x in fName]
            for n in names:
                if 'k' in n[2]:
                    n[0] *= 1000
            names.sort()
            names = [x[2] for x in names]
        else:
            print "here"
            print fName
            names = [[int(x[x.find('t')+1:min(x.find('_'),abs(x.find('s')))].strip('k')),x] for x in fName]
            
            for n in names:
                if 'k' in n[1]:
                    n[0] *= 1000
            names.sort()
            names = [x[1] for x in names]

        for name in names:
            name = dirN + '/' + name
            print name
            for i in range(RUNS):
                print name, i
                times.append(commands.getoutput('time ./'+name+' > /dev/null'))
                time.sleep(.2)
            print times
            dumpData(name)

def dumpData(name):
    global times
    with open('results/gres_'+sys.argv[1]+'.txt','a') as f:
        f.write(name+'\t')
        for j in range(RUNS):
            start = times[0].find('\t') + 1
            end = times[0].find('m', start)
            mins = float(times[0][start:end]) * 60000
            start = end + 1
            end = times[0].find('.', start)
            secs = float(times[0][start:end]) * 1000
            start = end + 1
            end = times[0].find('s')
            ms = float(times[0][start:end])
            total = mins + secs + ms
            f.write(str(total)+'\t')
            
            times.pop(0)
        f.write('\n')

if __name__ == '__main__':
    main()
