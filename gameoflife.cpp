#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <ctime>
using namespace std;

int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    int row, col, gen=1, gencount =1, opt;
    ifstream file("grid.txt");
    file>>row>>col;

    cout<<"Press 1 for random config and 2 for file reading: ";
    cin>>opt;
    int arr[row][col], arr2[row][col] = {};

    if (opt == 2)
    {
        cout<<"Initial pattern: "<<endl;
        for(int i =0; i<row; i++)
        {
            for (int j=0; j< col; j++)
            {
                file>>arr[i][j];
                if(arr[i][j] == 0)
                    cout<<"- ";
                if(arr[i][j] == 1)
                    cout<<"X ";
            }
            cout<<endl;
        }
    }

    if(opt ==1)
    {
        cout<<"Enter the no of rows and column: ";
        cin>>row>>col;
        srand(time(0));
        cout<<"Initial pattern: "<<endl;
        for(int i =0; i<row; i++)
        {
            for (int j=0; j< col; j++)
            {
                arr[i][j] = rand()%2;
                if(arr[i][j] == 0)
                    cout<<"- ";
                if(arr[i][j] == 1)
                    cout<<"X ";
            }
            cout<<endl;
        }
    }

    cout<<"Enter the amount of generations you want: ";
    cin>>gen;
    
    while(gencount <= gen)
    {
        cout << "\033[2J\033[1;1H"; //for clearing the screen
        int ncount =0;
        for(int i =0; i<row; i++)
        {
            for (int j=0; j< col; j++)
            {
                for (int v=i-1; v<= i+1; v++)
                {
                    for(int h=j-1; h<= j+1; h++)
                    {
                        if(v== -1 || h == -1 || v >= row || h >= col || (v==i && h ==j))
                            continue;
                        
                        else{
                            if (arr[v][h] == 1)
                                ncount++;
                        }
                    }
                }
                arr2[i][j] = ncount;
                ncount = 0;
            }
        }

        for(int i=0; i<row; i++)
        {
            for (int j=0; j<col; j++)
            {
                if (arr2[i][j] <= 1)
                    arr[i][j] = 0;
                
                if (arr2[i][j] == 3)
                    arr[i][j] = 1;

                if (arr2[i][j] >= 4)
                    arr[i][j] = 0;
            }
        }
        cout<<endl<<"Gen: "<<gencount<< endl;
        for(int i =0; i<row; i++)
        {
            for (int j=0; j<col; j++)
            {
                if(arr[i][j] == 0)
                    cout<<"- ";
                else
                    cout<<"X ";
            }
            cout<<endl;
        }
        sleep_for(microseconds(600000));
        // sleep_until(system_clock::now() + seconds(1));
        cout<<endl;
        gencount++;
    }
    return 0;
}