from turtle import *
r=65
tracer(False)
t=Turtle(visible=False)
x,y=-250,150

for i in range(4):
    for j in range(5):
        t.penup()
        t.setpos(x,y)
        t.down()
        t.circle(r)
        x+=r*2+5

    y-=r*2-10
    x-=r*3+7

    for j in range(4):
        t.penup()
        t.setpos(x,y)
        t.down()
        t.circle(r)
        x-=r*2+5

    y-=r*2-10
    x+=r+7

update()
# getscreen().getcanvas().postscript(file='outputname.ps')
done()
