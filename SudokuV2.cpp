#include<iostream>
#include<map>
#include<set>
#include<string>
#include<unistd.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
unsigned int mic = 1;
int Nbox =3;
int N =Nbox*Nbox;
map <int, set<int> > row, col, box;
map <pair<int, int>, int> board;
set<pair<int,int> > EMPTY;
typedef pair< pair<int, int>, int> triplet;
typedef map <pair<int, int>, int> Mpint;

void disp(string filename)
{
    ofstream fptr(filename.c_str());
    system("clear");
    for(int i = 1;i<N+1;i++)
    {
        for(int j = 1;j<N+1;j++)
        {
            fptr << board[make_pair(i,j)] << " ";
        }
        fptr << "\n";
    }
    cout << "\n\n";
    fptr.close();
    string pythcommand = "python SudokuVis.py "+filename;
    system(pythcommand.c_str());
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
        disp("FinalBoard.txt");
        return true;
    }
    return false;
}

int main()
{
    int **a;
    a = new int*[N];
    int numknown = 0;
    int r, c, val, boxi, boxj, boxindex;
    string PuzzleFile;
    cout << "Enter the name of the file with the Sudoku Puzzle (eg. Puzzle3.txt): ";
    cin >> PuzzleFile;
    ifstream puzzlePtr(PuzzleFile.c_str());
    for(int i = 1; i <N+1;i++)
    {
        a[i-1] = new int[N];
        for(int j =1; j< N+1;j++)
        {
            puzzlePtr >> a[i-1][j-1];
            board[make_pair(i,j)] = 0;
            EMPTY.insert(make_pair(i,j));
            if(a[i-1][j-1])
            {
                numknown++;
                r = i;
                c = j;
                val = a[i-1][j-1];
                board[make_pair(r,c)] = val;
                row[r].insert(val);
                col[c].insert(val);
                boxi= ((r-1)/Nbox);
                boxj = (c-1)/Nbox;
                boxindex = boxi*Nbox + boxj;
                box[boxindex].insert(val);
                EMPTY.erase(make_pair(r,c));
            }

        }
    }

    disp("InitialBoard.txt");
    if(Solve(board))
    {
        cout << "\nThe End \n";
    }
    return 0;
}

/*
 


