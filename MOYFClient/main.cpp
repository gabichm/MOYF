#include <MOYFNetworking/client/tcp_client.h>
#include <iostream>
#include <thread>

using namespace MOYF;

int main(int argc, char* argv[]) {
    TCPClient client {"localhost", 1337};
    std::string game_description = "Tic-Tac-Toe is a classic and popular paper-and-pencil game played on a 3x3 grid. It's a two-player game where each player takes turns marking a square with their respective symbol, either \"X\" or \"O\". The goal is to form a straight line of three of your symbols horizontally, vertically, or diagonally.\n"
                               "\n"
                               "Traditional Rules:\n"
                               "\n"
                               "    The game starts with an empty 3x3 grid, and one player is assigned \"X\" while the other is assigned \"O\".\n"
                               "    The players take turns making their moves, starting with \"X\".\n"
                               "    Each square in the grid is labeled with a number from 1 to 9, representing its position.\n"
                               "    To make a move, a player enters the number corresponding to the square they want to mark.\n"
                               "    The number entered corresponds to the position on the grid as follows:\n"
                               "    1 | 2 | 3\n"
                               "    4 | 5 | 6\n"
                               "    7 | 8 | 9\n"
                               "    The player's symbol (\"X\" or \"O\") is then placed in the chosen square.\n"
                               "    The game continues with players alternating turns until one of the following conditions is met:\n"
                               "        A player gets three of their symbols in a horizontal, vertical, or diagonal line.\n"
                               "        All squares on the grid are filled, resulting in a tie.\n"
                               "    If a winning condition is met, the player who achieved it is declared the winner.\n"
                               "    If the game ends in a tie, it is declared a draw.\n\n\n\n\n";
    std::string on_server_game_explenation = "To play tic-tac-toe on a computer  entering \"ij\" numbers, follow these steps:\n"
                                             "\n"
                                             "1. The game is played on a 3x3 grid. Each square in the grid is labeled with two numbers, \"i\" and \"j\", representing its row and column positions.\n"
                                             "   The grid is labeled as follows:\n"
                                             "   \n"
                                             "        00 | 01 | 02\n"
                                             "        10 | 11 | 12\n"
                                             "        20 | 21 | 22\n"
                                             "\n"
                                             "2. Two players take turns playing the game. The first player to enter a valid input becomes Player 1 abd is assigned the symbol \"O\", and second player is becomes Player 2 and is assigned the symbol \"O\".\n"
                                             "\n"
                                             "3. IF YOU ENTER YOUR INPUT AND A NEW BOARD DOESN'T PRINT OUT IT MEANS SOMETHING WENT WRONG OR THE SPACE IS ALREADY TAKEN. TRY ENTERING ONE MORE TIME\n"
                                             "4. The game begins with an empty grid. Each player takes turns entering the \"ij\" number corresponding to the square they want to mark.\n"
                                             "\n"
                                             "5. To make a move, the player enters the \"ij\" number representing the position they want to mark. For example, if Player 1 wants to mark the top-right corner, they would enter \"02\".\n"
                                             "\n"
                                             "6. After each move, the updated grid is displayed, showing the current positions of the symbols.\n"
                                             "\n"
                                             "7. The game continues with players taking turns until one of the following conditions is met:\n"
                                             "   - A player gets three of their symbols in a horizontal, vertical, or diagonal line, forming a winning combination. For example, three \"X\" symbols in a row.\n"
                                             "   - All squares on the grid are filled, resulting in a tie if no winning combination is formed.\n"
                                             "\n"
                                             "8. If a winning condition is met, the game ends, and the player who achieved it is declared the winner. The winning player's symbol (\"X\" or \"O\") is displayed.\n"
                                             "\n"
                                             "9. If the game ends in a tie, it is announced by printing \"N won the game!\" indicating that no player has won.\n"
                                             "\n"
                                             "\n"
                                             "Remember, the \"ij\" numbers correspond to the row and column positions on the grid, allowing you to specify where you want to place your symbol. Pay attention to the positions and the moves of your opponent to strategize and aim for a winning combination. Enjoy the game and have fun playing tic-tac-toe on your computer!";
    std::cout << game_description << on_server_game_explenation;


    client.OnMessage = [](const std::string& message) {
        std::cout << "\n";
    };

    std::thread t{[&client] () { client.Run(); }};

    while(true) {
        std::string message;
        getline(std::cin, message);

        if (message == "\\q") break;
        message += "\n";

        client.Post(message);

    }

    client.Stop();
    t.join();
    return 0;
}
