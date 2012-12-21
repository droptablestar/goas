import commands,os,time,re,sys

RUNS = 10

def main():
    if len(sys.argv) < 2:
        print 'Enter operator(s) to test (scan, select, project, sort, all, full)'
        exit()
    c_times = []
    r_times = []

    # os.system('purge')
    for dirN, subDir, fName in os.walk('oas_queries'):
        if dirN == 'oas_queries':
            continue

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
        if dirN != 'oas_queries/0scan':
            names = [[int(x[:x.find('s')].strip('k_')),int(re.sub('[0-9]+[a-z\_]+','',x)),x] for x in fName]
            for n in names:
                if 'k' in n[2]:
                    n[0] *= 1000
            names.sort()
            names = [x[2] for x in names]
        else:
            names = [[int(x[:min(x.find('_'),abs(x.find('s')))].strip('k')),x] for x in fName]
            for n in names:
                if 'k' in n[1]:
                    n[0] *= 1000
            names.sort()
            names = [x[1] for x in names]

        for name in names:
            print name
            os.chdir('../bin')
            commands.getoutput('./goas ../tst/'+dirN+'/'+name)
            commands.getoutput('./temp > ../tst/new_tables/'+name+'.txt')
            for i in range(RUNS):
                print dirN,name, i
                # os.system('purge')
                # time.sleep(.2)
                c_times.append(commands.getoutput('time ./goas ../tst/'+
                                                  dirN+'/'+name))
                time.sleep(.3)
                r_times.append(commands.getoutput('time ./temp > /dev/null'))
                time.sleep(.01)
                os.remove('temp')
                os.remove('temp.c')
            os.chdir('../tst/')
            print c_times
            print r_times
            c_times, r_times = dumpData(c_times, r_times, name)

def dumpData(c_times, r_times, name):
    with open('results/goas_'+sys.argv[1]+'_c.txt','a') as f:
        f.write(name+'\t')
        for j in range(RUNS):
            start = c_times[0].find('\t') + 1
            end = c_times[0].find('m', start)
            mins = float(c_times[0][start:end]) * 60000
            start = end + 1
            end = c_times[0].find('.', start)
            secs = float(c_times[0][start:end]) * 1000
            start = end + 1
            end = c_times[0].find('s')
            ms = float(c_times[0][start:end])
            total = mins + secs + ms
            f.write(str(total)+'\t')

            c_times.pop(0)

        f.write('\n')

    with open('results/goas_'+sys.argv[1]+'_r.txt','a') as f:
        f.write(name+'\t')
        for j in range(RUNS):
            start = r_times[0].find('\t') + 1
            end = r_times[0].find('m', start)
            mins = float(r_times[0][start:end]) * 60000
            start = end + 1
            end = r_times[0].find('.', start)
            secs = float(r_times[0][start:end]) * 1000
            start = end + 1
            end = r_times[0].find('s')
            ms = float(r_times[0][start:end])
            total = mins + secs + ms
            f.write(str(total)+'\t')

            r_times.pop(0)
        f.write('\n')
    return c_times, r_times

if __name__ == '__main__':
    main()
