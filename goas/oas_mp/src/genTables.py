import sys,random,string

def main():
    col_names = []
    f = open('tables/'+sys.argv[1],'w')
    col_names.append("id")
    f.write("id")
    for col in range(1,int(sys.argv[2])-1):
        col_names.append('col'+str(col))
        f.write('\t'+col_names[col])
    if (int(sys.argv[2]) > 1):
        col_names.append('\trandom')
        f.write('\trandom\n')
    else:
        f.write('\n')
    for row in range(int(sys.argv[3])):
        for col in range(len(col_names)):
            e_name = 'row'+str(row)+'_col'+str(col)
            if col == 0:
                f.write(str(row)+'\t')
                continue
            if (col != len(col_names)-1):
                f.write(e_name+'\t')
            else:
                f.write(str(random.randint(0,2*int(sys.argv[3]))))
        f.write('\n');
    f.close()


if __name__ == '__main__':
    main()
