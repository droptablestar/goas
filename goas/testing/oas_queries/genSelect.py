import os
names = os.listdir('select')
for i in range(len(names)):
    with open('select/'+names[i],'r') as f:
        lines = f.readlines()
    stop = 0
    for j in range(3):
        stop = lines[0].find('/', stop+1)
    lines[0] = lines[0][:stop+1] +  names[i][:names[i].find('_')]+');\n'

    with open('select/'+names[i],'w') as f:
        f.write(''.join(lines))
