import commands,os,time

RUNS = 10

def main():
    c_times = []
    r_times = []

    os.system('purge')
    for dirN, subDir, fName in os.walk('oas_queries'):
        if dirN == 'oas_queries':
            continue
        names = [(int(x[:min(x.find('_'),abs(x.find('k')))]),x) for x in fName]
        names.sort()
        names = [x[1] for x in names]

        for name in names:
            os.chdir('../oas_mp/')
            for i in range(RUNS):
                print dirN,name, i
                c_times.append(commands.getoutput('time ./goas ../testing/'+dirN+'/'+name))
                time.sleep(.2)
                r_times.append(commands.getoutput('time ./temp > /dev/null'))
                time.sleep(.2)
                os.remove('temp')
                os.remove('src/temp.c')
                os.system('purge')
            os.chdir('../testing/')
            print c_times
            print r_times
            c_times, r_times = dumpData(c_times, r_times, name)


def dumpData(c_times, r_times, name):
    with open('oas_mp_results/c_timesO2.txt','a') as f:
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

    with open('oas_mp_results/r_timesO2.txt','a') as f:
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
