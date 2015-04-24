from numpy import *
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

import sys
import os
def drawBoard(board):
    fig = plt.figure()
    ax = fig.add_subplot(111)

    ax.set_aspect('equal')   
    x = arange(10)
    xc = ones(10)
    for i in xrange(9):
        plt.plot(x,i*xc,'k')
        plt.plot(i*xc,x,'k')
    for i in xrange(1,3):
        plt.plot(x,3*i*xc,linewidth=3, color='k')
        plt.plot(3*i*xc,x,linewidth=3, color= 'k')
    for i in xrange(9):
        for j in xrange(9):
            plt.text(i+0.5, j+0.5,board[8-j,i],horizontalalignment='center',
        verticalalignment='center')        
    
    frame = plt.gca()
    frame.axes.get_xaxis().set_visible(False)
    frame.axes.get_yaxis().set_visible(False)

board = loadtxt(sys.argv[1],dtype=int)
strboard = chararray((9,9))
for i in xrange(board.shape[0]):
    for j in xrange(board.shape[1]):
        strboard[i,j] = str(board[i,j])
        if(board[i,j]==0):
            strboard[i,j] = ' '
drawBoard(strboard)
plt.savefig(sys.argv[1].split(".")[0]+".png")
os.system("open "+sys.argv[1].split(".")[0]+".png")
