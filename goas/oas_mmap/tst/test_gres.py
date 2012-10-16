import commands,os,time

# names = os.listdir('pgres_queries/select/')
times = []
RUNS = 10

os.system('purge')
def main():
    global times
    rootDir = '.'
    for dirN, subDir, fName in os.walk('pgres_queries'):
        if dirN == 'pgres_queries/scan' or dirN == 'pgres_queries/select' or dirN == 'pgres_queries' or dirN == 'pgres_queries/all':
            continue
        for name0 in fName:
            name = dirN + '/' + name0
            for i in range(RUNS):
                print name, i
                times.append(commands.getoutput('time ./'+name))
                time.sleep(.2)
                os.system('purge')
            print times
            dumpData(name0)

def dumpData(name):
    global times
    with open('pgres_results/times.txt','a') as f:
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
