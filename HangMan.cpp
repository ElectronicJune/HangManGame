#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

string hangMan[7][6];

void getHangManLine(int row){
    for (int i = 0;i<6;i++){
        if (hangMan[row][i].length()>0){
            cout<<hangMan[row][i];
        }else{
            cout<<" ";
        }
    }
}
void setHangManGraphic(int update){
    switch (update){
        case 0 :
            for (int i=0;i<7;i++){
                for (int j=0;j<6;j++){
                    hangMan[i][j]="";
                }
            }
            break;
        case 1 :
            hangMan[6][0]="_";hangMan[6][1]="_";hangMan[6][2]="_";hangMan[6][3]="_";hangMan[6][4]="_";hangMan[6][5]="_";
            break;
        case 2 :
            hangMan[1][1]="|";hangMan[2][1]="|";hangMan[3][1]="|";hangMan[4][1]="|";hangMan[5][1]="|";hangMan[6][1]="|";
            break;
        case 3 :
            hangMan[0][2]="_";hangMan[0][3]="_";
            break;
        case 4 :
            hangMan[1][4]="|";
            break;
        case 5 :
            hangMan[2][3]="(";hangMan[2][5]=")";
            break;
        case 6 :
            hangMan[3][4]="|";hangMan[4][4]="|";
            break;
        case 7 :
            hangMan[3][3]="/"; hangMan[3][5]="\\";
            break;
        case 8 :
            hangMan[5][3]="/"; hangMan[5][5]="\\";
            break;
    }
}
bool equalString(string a,string b){
    if (a.length()!=b.length()){return false;}
    for (int i=0;i<a.length();i++){
        if (a[i]!=b[i]){return false;}
    }
    return true;
}
void hr(char character , bool firstEnter , int repeat , bool endEnter){
    if(firstEnter){cout<<endl;}
    for (int i=0;i<repeat;i++){
        cout<<character;
    }
    if (endEnter){cout<<endl;}
}
int countLines(ifstream& file){
    int lines=0;
    string word;
    while (true){
        getline(file,word);
        if (word[0]=='-'){
            break;
        }
        lines++;
    }
    return lines;
}
 

int main(){
    bool playAgain=true;
    int wins=0;
    int loses=0;
    ifstream myfile;
    myfile.open("dictionary.txt");
    int linesInDictionary =countLines(myfile);
    myfile.close();
    while(playAgain){
        setHangManGraphic(0);
        srand(time(NULL));
        int randomLine = (rand()%linesInDictionary)+1;
        myfile.open("dictionary.txt");
        int currentLine = 0;
        string word ;
        while (true){
            currentLine++;
            getline(myfile,word);
            if (currentLine==randomLine){
                break;
            }
        }
        myfile.close();
        hr('-',false,60,true);
        cout<<"HANG MAN GAME";
        hr('-',true,60,true);
        char guessedWord[word.length()] ;
        for (int i=0;i<word.length();i++){
            guessedWord[i]='_';
        }
        string guessedWrong[8];
        int wrongGuesses =0;
        int correctGuesses=0;

        while (true){
            string myGuess;
            getHangManLine(0);cout<<endl;
            getHangManLine(1);cout<<"\t";
            for (int i=0;i<word.length();i++){
                cout<<guessedWord[i]<<" ";
            }
            cout<<endl;
            getHangManLine(2);cout<<"\t";cout<<endl;
            getHangManLine(3);cout<<"\t";
            cout<<"Guessed Wrong : ";
            for (int i=0;i<8;i++){
                cout<<guessedWrong[i]<<" ";
            }
            cout<<endl;
            getHangManLine(4);cout<<"\t";cout<<endl;
            getHangManLine(5);cout<<"\t";cout<<endl;
            getHangManLine(6);cout<<"\t";
        
            if (wrongGuesses>7){
                cout<<"YOU LOSE THE GAME! "<<"Answer is "<<word;
                hr('-',true,60,true);
                loses++;
                break;
            }else{
                cout<<"Your Guess : ";
                cin>>myGuess;
                hr('-',true,60,true);
                if (myGuess.length()>1){
                    if(equalString(myGuess,word)){cout<<"YOU WIN!";hr('-',true,60,true);wins++;break;}
                    else{
                        wrongGuesses++;
                        setHangManGraphic(wrongGuesses);
                        guessedWrong[wrongGuesses-1]=myGuess;
                    }
                }else {
                    int included=false;
                    for (int i=0;i<word.length();i++){
                        if (myGuess[0]==guessedWord[i]){included=true;break;}
                    }
                    if(!included){
                        int include=false;
                        for (int i=0;i<word.length();i++){
                            if (word[i]==myGuess[0]){
                                guessedWord[i]=myGuess[0];
                                include=true;
                                correctGuesses++;
                            }
                        }
                        if(!include){
                            wrongGuesses++;
                            setHangManGraphic(wrongGuesses);
                            guessedWrong[wrongGuesses-1]=myGuess;
                        }
                    }
                }
                if (correctGuesses==word.length()){cout<<"YOU WIN!";hr('-',true,60,true);;wins++;break;}
            
            }
        }
        cout<<"Play Again? (yes=y,no=n) ";
        string playAgainInput;
        cin>>playAgainInput;
        if (!(playAgainInput[0]=='y')){
            playAgain=false;
        }
    }
    cout<<"\n= Summary =====================\n";
    cout<<"Played "<<wins+loses<<" times.\n";
    cout<<"Wins: "<<wins<<endl;
    cout<<"Loses: "<<loses<<endl;
    cout<<"===============================";
    while (true){};
    return 0;
}
