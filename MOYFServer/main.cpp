
#include <iostream>
#include <MOYFNetworking/server/tcp_server.h>
#include <string>
#include "gra.h"


int main(int argc, char* argv[]) {

    MOYF::TCPServer server {MOYF::IPV::V4, 1337};
    std::string first_user;
//    std::string game_explain = "Tic-Tac-Toe is a classic and popular paper-and-pencil game played on a 3x3 grid. It's a two-player game where each player takes turns marking a square with their respective symbol, either \"X\" or \"O\". The goal is to form a straight line of three of your symbols horizontally, vertically, or diagonally.\n"
//                               "\n"
//                               "How to Play:\n"
//                               "\n"
//                               "    The game starts with an empty 3x3 grid, and one player is assigned \"X\" while the other is assigned \"O\".\n"
//                               "    The players take turns making their moves, starting with \"X\".\n"
//                               "    Each square in the grid is labeled with a number from 1 to 9, representing its position.\n"
//                               "    To make a move, a player enters the number corresponding to the square they want to mark.\n"
//                               "    The number entered corresponds to the position on the grid as follows:\n"
//                               "    1 | 2 | 3\n"
//                               "    4 | 5 | 6\n"
//                               "    7 | 8 | 9\n"
//                               "    The player's symbol (\"X\" or \"O\") is then placed in the chosen square.\n"
//                               "    The game continues with players alternating turns until one of the following conditions is met:\n"
//                               "        A player gets three of their symbols in a horizontal, vertical, or diagonal line.\n"
//                               "        All squares on the grid are filled, resulting in a tie.\n"
//                               "    If a winning condition is met, the player who achieved it is declared the winner.\n"
//                               "    If the game ends in a tie, it is declared a draw.\n";
//    server.Broadcast(game_explain);
    Tictactoe* game = new Tictactoe("Player1", "player2");

    server.OnJoin = [](MOYF::TCPConnection::pointer server) {
        std::cout << "User has joined the server: " << server->GetUsername() << std::endl;

    };

    server.OnLeave = [](MOYF::TCPConnection::pointer server) {
        std::cout << "User has left the server: " << server->GetUsername() << std::endl;
    };

    server.OnClientMessage = [&server, &game](const std::string& message) {
//        std::cout << "printing message" << message << std::endl;
        std::string play = message.substr(message.length() - 3, 2);
        game->move(play);
        std::string game_state = game->broadcasting();

        // Send message to client
        server.Broadcast(game_state);
        char won  = game->get_won();
        if (won != '-') {
            std::string who_won = " won the game!!";
            who_won = won + who_won;
            server.Broadcast(who_won);


            //Close and quit server
            return 0;

        }
    };

    server.Run();

    return 0;
}