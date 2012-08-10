import os
names = os.listdir('select')
for i in range(len(names)):
    with open('select/'+names[i],'r') as f:
        lines = f.readlines()
    start = lines[0].find('where')
    lines[0] = 'select * from ' +  names[i][:names[i].find('_')] + ' ' + lines[0][start:]

    with open('select/'+names[i],'w') as f:
        f.write(''.join(lines))
