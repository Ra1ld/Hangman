#include <iostream>
#include <string>       //strings
#include <ctime>        //time
#include <cstdlib>      //srand


using namespace std;

class Hang{
    public:

        int num_bad = 0;    // counting incorect
        int num_right = 0;  // containing correct
        
        // constructor
        Hang(int l){
            MAX = 3;
            tries_left = MAX;
            for(int i = 0; i < l; i++)
                game.push_back('-');   
        };

        //destructor
        ~Hang(){

        };

        // Entering correct letters to game
        void found(char guess, int pos){
            game[pos] = guess;
        };

        // reduce DISPLAY tries
        void reduce_display(){
            tries_left--;
        };

        // pushing wrong guesses(if not found)
        void enter_wrong(char c){
            if(wrong_guess.find(c) == string::npos)
                wrong_guess.push_back(c);
        };

        // (getter) MAX 
        int max_Tries(){
            return MAX;
        };

        // (getter) tries_left
        int left(){
            return tries_left;
        };

        // game printing
        void print_result(){
            system("cls");
            cout << "\n\nCurrent: "<< game << endl;
            cout << "Tries Left: "<<tries_left<< endl;
            cout << "Bad guesses: "<<wrong_guess<< endl;
        };
    private:
        string game;
        string wrong_guess;
        int MAX;
        int tries_left;
};

int main(){

    srand(time(NULL));  // seeding time through unix epoch
    string choice_arr[] = {"Tomato", "lemon", "Orange", "Apple"};
    

    
    int choice = rand() % 4;                                // chosing randonly a word(index) from the array(0 to 3)
    const int init_length = choice_arr[choice].length();    // char length of the choosen string
    string buf = choice_arr[choice];                        // copying the chosen string to a buffer to be used/changed

    // creating game
    Hang game1(init_length); 
    game1.print_result();

    do{
        char guess; //(scope variable) 
        
        // user input
        cout << "\nPlease insert a letter: ";
        cin >> guess;


        size_t pos = buf.find(guess);   // finding position of the guessed word(if exists)
        if( pos != string::npos ){

            // counting correct(for the "while" argument)
            game1.num_right += 1; 
            
            // placing the letters in the "game" array(string) to be displayed later
            game1.found( guess , pos ); 
            
            // replacing the found letter with "-" in buffer array so "find" method works as logically unrestricted
            buf.replace(pos,1,"-"); 

            // checking for more instanses of that letter
            while( ( pos = buf.find(guess) ) != string::npos ){
                game1.num_right += 1;
                game1.found( guess , pos ); 
                buf.replace(pos,1,"-");      
            }
        }
        else{   
            game1.num_bad += 1;
            game1.enter_wrong(guess);
            game1.reduce_display();
        }
        game1.print_result();

    }while( ( game1.num_right < init_length )  &&  game1.num_bad < game1.max_Tries() );

    //check if won
    system("cls");
    if( game1.left() <= 0 )         cout<<"GAME OVER"<<endl;
    else                            cout<<"Congratulations, you won!"<<endl;
    
    cout<<"The word was: "<<choice_arr[choice];
    return 0;
}
