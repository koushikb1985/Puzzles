/*
 This code solves a maze using backtracking method.
 */
#include<iostream>
#include<map>
#include<string>
#include<unistd.h>
#include<stdlib.h>
using namespace std;
unsigned int mic = 500000;
map <pair<int, int>, char> Maze;
int startx, starty,  endx,  endy, Wmax, Hmax;

char EMPTY= ' ';
char Walker = '0';
char Wall = '#';

void disp()
{
    system("clear");
    int i =0;
    while(i<Hmax)
    {
        for(int j = 0;j<Wmax;j++)
        {
            cout << Maze[make_pair(i,j)];
        }
        cout << "\n";
        i++;
    }
}
bool Solve(int x, int y )
{
    pair<int,int> gridpt, gridptL, gridptR, gridptU,gridptD;
    static map <pair<int, int>, bool> Solved;
    gridpt  = make_pair(x,y);
    gridptD = make_pair(x,y-1);
    gridptU = make_pair(x,y+1);
    gridptR = make_pair(x+1,y);
    gridptL = make_pair(x-1,y);
    
    Maze[gridpt]=Walker;
    
    disp();
    usleep(mic);
    map <pair<int, int>, bool>::iterator it;
    it = Solved.find(gridpt);
    if(it!=Solved.end())
    {
        return Solved[gridpt];
    }
    else
    {
        if((x==endx) && (y==endy))
        {
            Solved[gridpt] = true;
            return true;
        }
        
        if((x>0 && Maze[gridptL]==EMPTY) && Solve(x-1,y) )
        {
            Solved[gridpt] = true;
            return true;
        }
        if((x < Hmax && Maze[gridptR]==EMPTY) && Solve(x+1,y))
        {
            Solved[gridpt] = true;
            return true;
        }
        if((y>0 && Maze[gridptD]==EMPTY) && Solve(x,y-1))
        {
            Solved[gridpt] = true;
            return true;
        }
        if((y<Wmax && Maze[gridptU]==EMPTY) && Solve(x,y+1))
        {
            Solved[gridpt] = true;
            return true;
        }
        Maze[gridpt] = EMPTY;
        Solved[gridpt] = false;
        disp();
        usleep(mic);
        return false;
    }
    
}

int main()
{
    string row;
    cout << "Enter Height and Width of the Maze\n" ;
    cout << "(Type 9 9, if you are not sure.): ";
    cin >> Hmax >> Wmax;
    int i = 0;
    cout << "Using # to represent the walls of the maze, represent the maze as a sequence of " <<Hmax << "strings of length " << Wmax <<".";
    cout << "As an example you can copy paste the following maze (with width = height = 9): \n\n";
    cout << "# #######\n";
    cout << "#   #   #\n";
    cout << "# ### # #\n";
    cout << "# #   # #\n";
    cout << "# # # ###\n";
    cout << "#   # # #\n";
    cout << "# ### # #\n";
    cout << "#   #   #\n";
    cout << "####### #\n\n";
    cout << "Your Maze (copy paste the above maze if you are not sure): \n";
    
    getline(cin, row ,'\n');
    while(i<Hmax)
    {
        getline(cin,row ,'\n');
        for(int j = 0;j<Wmax;j++)
        {
            if(row.at(j)!=EMPTY)
            {
                Maze[make_pair(i,j)] = Wall;
                
            }
            else
            {
                Maze[make_pair(i,j)] = EMPTY;
            }
            
            
        }
        
        i++;
    }
    i = 0;

    cout << "Enter coordinates of starting point (Type 0 1 for the example maze): ";
    cin >> startx >> starty;
    cout << "Enter coordinates of terminal point (Type 8 7 for the example maze): ";
    cin >> endx >> endy;
    if(Solve(startx, starty ))
    {
        cout << "\nThe End \n";
    }
    
    return 0;
}

/*
# #######
#   #   #
# ### # #
# #   # #
# # # ###
#   # # #
# ### # #
#   #   #
####### #
 
 */

/*
 
# #######
#       #
# ##### #
# #   # #
# ##### #
#       #
# ### # #
#   #   #
####### #
 
 */

