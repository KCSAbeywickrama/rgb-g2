with open("calib_data/dataset5.txt","r") as file:
    data=file.read()

sets=[[[c for c in p.split(',')] for p in s.split('\n')] for s in data.split('\n\n')]

r=sets[0][1]
g=sets[1][1]
b=sets[2][1]
bc=sets[3][1]
w=sets[5][1]
# print(1,2,3,sep='\t')

# print(r,g,b,bc,w,sep='\n')

def red_line():
    h1="{}".format(w[0])
    h2="({}+{})/2".format(r[0],w[0])
    h3="({}*3+{})/4".format(r[0],w[0])

    l1="{}".format(bc[0])
    l2="({}+{}+{})/3".format(bc[0],g[0],b[0])
    l3="({}*3+{}+{})/5".format(bc[0],g[0],b[0])

    print(255,h1,h2,h3,sep=',')
    print(0,l1,l2,l3,sep=',')
    

def green_line():
    h1="{}".format(w[1])
    h2="({}+{})/2".format(g[1],w[1])
    h3="({}*3+{})/4".format(g[1],w[1])

    l1="{}".format(bc[1])
    l2="({}+{}+{})/3".format(bc[1],r[1],b[1])
    l3="({}*3+{}+{})/5".format(bc[1],r[1],b[1])

    print(255,h1,h2,h3,sep=',')
    print(0,l1,l2,l3,sep=',')

   

def blue_line():
    h1="{}".format(w[2])
    h2="({}+{})/2".format(b[2],w[2])
    h3="({}*3+{})/4".format(b[2],w[2])

    l1="{}".format(bc[2])
    l2="({}+{}+{})/3".format(bc[2],r[2],g[2])
    l3="({}*3+{}+{})/5".format(bc[2],r[2],g[2])

    print(255,h1,h2,h3,sep=',')
    print(0,l1,l2,l3,sep=',')
    
lines=red_line,green_line,blue_line

for c in range(3):
    lines[c]()
    print()

    for s in sets:
        print(s[0][c],s[1][c],sep=',')
    print('---')
