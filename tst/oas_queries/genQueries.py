import os,re
dirs = os.listdir('./')[1:-1]

# sizes = ['1','1k','10k','50k','100k','200k','300k','400k','500k','600k','700k',
#          '800k','900k','1000k']
sizes = ['100','1k','10k','50k']

for d in dirs:
    print d
    for s in sizes:
        if d == '1select':
            x = [i for i in range(1,6,1)]
        else:
            x = [1,3,6,9,12]
        for i in x:
            name = d+'/100k_scan_'+d[1:]+str(i)
            print name
            with open(name,'r') as f:
                content = f.read()
            print content
            search = re.search('/[0-9]+k?',content)
            if search == None:
                print name,'RE ERROR'
            else:
                f_name = d+'/'+s+'_scan_'+d[1:]+str(i)
                print f_name
                new = content[:search.start()+1]+s+content[search.end():]
                with open(f_name,'w') as f:
                    f.write(new)
            print
