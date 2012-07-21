import commands,os

for fname in os.listdir('input'):
    print 'input/'+fname
    print commands.getoutput('time ./goas input/'+fname+' > results/'+fname)
    os.remove('bin/temp')
