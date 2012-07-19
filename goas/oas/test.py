import commands,os

for fname in os.listdir('input'):
    print 'input/'+fname
    print commands.getoutput('time ./goas.sh input/'+fname+' > results/'+fname)
    os.remove('lib/temp')
    os.remove('lib/temp.o')
    os.remove('lib/temp.c')

