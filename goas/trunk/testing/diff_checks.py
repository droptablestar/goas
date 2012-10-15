import commands,os,time

o_names = os.listdir('oas_queries')
o_names = filter(lambda x: x[0] == '1',o_names)

p_names = os.listdir('pgres_queries')
p_names = filter(lambda x: x[0:2] == 't1',p_names)

for i in range(len(p_names)):
    print p_names[i], o_names[i]
    commands.getoutput('diff -w '+p_names[i]+' '+o_names[i]+' > diff_checks/'+p_names[i])
    time.sleep(.5)
