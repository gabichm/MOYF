//
// Created by gabi on 6/21/23.
//

#ifndef MOYFCLIENT_GRA_H
#define MOYFCLIENT_GRA_H

#include <iostream>
#include <string>
#include <random>
//#include "gra.cpp"

#define MAX_PLAYER_NAME 1024

class Tictactoe {
private:
    std::string board[3][3];
    std::string player1, player2;
    static int round;
    char won;

public:
    Tictactoe() = default;
    Tictactoe(std::string p1, std::string p2)  : won('-'), player1(p1), player2(p2), board{{"00","01", "02"},
                                                                                       {"10", "11","12"},
                                                                                       {"20","21","22"}}{}
    ~Tictactoe() = default;


    void move(std::string play);
    std::string broadcasting();
    char get_won() {return won;}
private:

    int checking_for_win();
    std::pair<int,int> space(std::string input);

    void print_board();
    int board_is_full();
    bool check_wrong_input(std::string input);


};
int Tictactoe::round = 0;
//Tictactoe::Tictactoe(std::string p1, std::string p2) : won('-'), player1(p1), player2(p2), board{{"00","01", "02"},
//                                                                                       {"10", "11","12"},
//                                                                                       {"20","21","22"}}{
//    std::cout << player1 << " is: 0, " << player2 << " is: X\n" << player1  << " will start" << std::endl;}

void Tictactoe::move(std::string play) {
    print_board();
    int player = round%2;
//    switch (player){
//        case 0:
//            std::cout << player1 << " where do you want to play? ";
//            break;
//        default: std::cout << player2 << " where do you want to play? ";
//    }
    if(check_wrong_input(play)) { return;}
    std::pair<int,int> play_ = space(play);
    int play_i = play_.first;
    int play_j = play_.second;
    std::string& _play = board[play_i][play_j];
//    int play_int = std::stoi(_play);
    bool taken = false;
    if (_play == "00" || _play == "01" || _play == "02" || _play == "10" || _play == "11" || _play == "12" || _play == "20" || _play == "21" || _play == "22"){taken = true;}
    if (taken){
        if (round%2 == 0){
            _play = "O ";
            round++;
        }
        else{
            _play = "X ";
            round++;
        }
    }
    else {
        std::cout << "This space is already taken, try again ";
        return;
//        move(play);
    }
    print_board();
    int win = checking_for_win();
    if (!win) return;
    else if(win == 1) won = 'O';
    else if (win == 2) won = 'X';
//        std::cout << player2 << " wins the game" << std::endl;}
    else if (win == 3) won = 'N'; //std::cout << "Nobody wins" << std::endl;

}

int Tictactoe::checking_for_win()  {
    int i;
    for (i = 0; i < 3; i++){
        if (board[i][0] == board[i][1]  && board[i][0] == board[i][2]){
            if (board[i][0] == "O ")return 1;
            else return 2;
        }
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            if (board[i][0] == "O ") return 1;
            else return 2;
        }
    }

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        if (board[i][0] == "O ") return 1;
        else return 2;
    }
    else if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        if (board[i][0] == "O ") return 1;
        else return 2;
    }
    else if(board_is_full() == 9){
        return 3;
    }
    else return 0;
}

std::pair<int, int> Tictactoe::space(std::string input) {
    int i = input[0] - '0';
    int j = input[1] - '0';
    return std::make_pair(i,j);
}

void Tictactoe::print_board() {
    system("clear");
    std::cout << "    |    |    \n";
    std::cout << " " << board[0][0] <<" | " << board[0][1] << " | " << board[0][2] << "\n";
    std::cout << "____|____|____\n";
    std::cout << "    |    |    \n";
    std::cout << " " << board[1][0] <<" | " << board[1][1] << " | " << board[1][2] << "\n";
    std::cout << "____|____|____\n";
    std::cout << "    |    |    \n";
    std::cout << " " << board[2][0] <<" | " << board[2][1] << " | " << board[2][2] << "\n";
    std::cout << "    |    |    \n";
}

int Tictactoe::board_is_full() {
    int counter = 1;
    for (int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if ((board[i][j] == "O ") || (board[i][j] == "X ")) {
                counter++;
            }

        }
    }
    return counter;
}

bool Tictactoe::check_wrong_input(std::string input) {
    if(input == "01" || input == "02" || input == "00" || input == "10" || input == "11" || input == "12" || input == "20" || input == "21" || input == "22") {return false;}
    return true;
}

std::string Tictactoe::broadcasting() {
    std::cout << 1;
    std::string broadcast_message;
    for(auto i = 0; i < 3; ++i) {
        broadcast_message += "    |    |    \n";
        for (auto j = 0; j < 3; ++j) {
            broadcast_message += " " + board[i][j] + " |";
        }
        broadcast_message = broadcast_message.substr(0,broadcast_message.length()-2);
        broadcast_message += "\n____|____|____\n";
    }
    broadcast_message = broadcast_message.substr(0,broadcast_message.length() - 15);
    broadcast_message += "\n";
    return broadcast_message;
}


#endif //MOYFCLIENT_GRA_H
