#include<iostream>
#include<map>
#include<set>
#include<string>
#include<unistd.h>
#include<stdlib.h>
using namespace std;
unsigned int mic = 1;
int Nbox =3;
int N =Nbox*Nbox;
map <int, set<int> > row, col, box;
map <pair<int, int>, int> board;
set<pair<int,int> > EMPTY;
typedef pair< pair<int, int>, int> triplet;
typedef map <pair<int, int>, int> Mpint;



void disp()
{
    system("clear");
    for(int i = 1;i<N+1;i++)
    {
        for(int j = 1;j<N+1;j++)
        {
            cout << board[make_pair(i,j)] << "\t";
        }
        cout << "\n\n";
    }
    cout << "\n\n";
}
triplet make_triplet(int i, int j, int k)
{
    pair<int, int> ij = make_pair(i,j);
    triplet ijk = make_pair(ij, k);
    return ijk;
}
bool CheckRow(int i,  int val)
{
    set<int>::iterator it;
    it = row[i].find(val);
    if(it!=row[i].end())
    {
        return false;
    }
    else
    {
        return true;
    }
    
}
bool CheckCol(int j, int val)
{
    set<int>::iterator it;
    it = col[j].find(val);
    if(it!=col[j].end())
    {
        return false;
    }
    else
    {
        return true;
    }
    
}
bool CheckBox(int boxindex, int val)
{
    set<int>::iterator it;
    it = box[boxindex].find(val);
    if(it!=box[boxindex].end())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Solve(map <pair<int, int>, int> newboard)
{
    
    pair<int,int> gridpt;
    
    if(!EMPTY.empty())
    {
        set <pair<int, int> >::iterator itboard;
        bool rcheck, ccheck, boxcheck;
        itboard = EMPTY.begin();
        int i, j, boxi, boxj, boxindex;
        i = itboard->first ;
        j = itboard->second ;
        EMPTY.erase(itboard);
        gridpt = make_pair(i,j);
        boxi= ((i-1)/Nbox);
        boxj = (j-1)/Nbox;
        boxindex = boxi*Nbox + boxj;

        int val = 1;
        while(val <= N)
        {
            rcheck =CheckRow(i, val);
            ccheck = CheckCol(j,val);
            boxcheck = CheckBox(boxindex, val);
            board[gridpt] = val;
            triplet ijval = make_triplet(i, j, val);
            
            if(ccheck)
            {
                col[j].insert(val);
                if(rcheck)
                {
                    row[i].insert(val);
                    if(boxcheck)
                    {
                        box[boxindex].insert(val);
                        if(Solve(board))
                        {
                            return true;
                        }
                        else
                        {
                            box[boxindex].erase(val);
                            row[i].erase(val);
                            col[j].erase(val);
                            
                        }
                    }
                    else
                    {
                        row[i].erase(val);
                        col[j].erase(val);
                        
                    }
                }
                else
                {
                    col[j].erase(val);
                    
                }
            }
            val++;
        }
        
        EMPTY.insert(gridpt);
        board[gridpt] = 0;
        return false;
    }
    else
    {
       // cout << "\n3. \n";
        disp();
        return true;
    }
    return false;
}

int main()
{
    for(int i = 1; i <N+1;i++)
    {
        for(int j =1; j< N+1;j++)
        {
            board[make_pair(i,j)] = 0;
            EMPTY.insert(make_pair(i,j));
        }
    }
    int numknown;
    cin >> numknown;
    int r, c, val, boxi, boxj, boxindex;
    for(int k =0; k<numknown; k++)
    {
        cin >> r >> c >> val;
        board[make_pair(r,c)] = val;
        row[r].insert(val);
        col[c].insert(val);
        boxi= ((r-1)/Nbox);
        boxj = (c-1)/Nbox;
        boxindex = boxi*Nbox + boxj;
        box[boxindex].insert(val);
        EMPTY.erase(make_pair(r,c));
    }
    disp();
    if(Solve(board))
    {
        cout << "\nThe End \n";
    }
    return 0;
}

/*
 
 26
 1 4 1
 1 6 5
 1 8 6
 1 9 8
 2 7 7
 2 9 1
 3 1 9
 3 3 1
 3 8 3
 4 3 7
 4 5 2
 4 6 6
 5 1 5
 5 9 3
 6 4 8
 6 5 7
 6 7 4
 7 2 3
 7 7 8
 7 9 5
 8 1 1
 8 3 5
 9 1 7
 9 2 9
 9 4 4
 9 6 1
 
 */

/*
27
1 7 6
1 8 8
2 5 7
2 6 3
2 9 9
3 1 3
3 3 9
3 8 4
3 9 5
4 1 4
4 2 9
5 1 8
5 3 3
5 5 5
5 7 9
5 9 2
6 8 3
6 9 6
7 1 9
7 2 6
7 7 3
7 9 8
8 1 7
8 4 6
8 5 8
9 2 2
9 3 8
 
 
*/

