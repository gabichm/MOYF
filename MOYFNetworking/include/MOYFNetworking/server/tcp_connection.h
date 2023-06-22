//
// Created by ozzadar on 2021-08-22.
//

#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <queue>

namespace MOYF {
    using boost::asio::ip::tcp;
    namespace io = boost::asio;

    using MessageHandler = std::function<void(std::string)>;
    using ErrorHandler = std::function<void()>;

class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
    public:
        using pointer = std::shared_ptr<TCPConnection>;

        static pointer Create(io::ip::tcp::socket&& socket) {
            return pointer(new TCPConnection(std::move(socket)));
        }

        inline const std::string& GetUsername() const { return _username; }

        tcp::socket& Socket() {
            return _socket;
        }

        void Start(MessageHandler&& messageHandler, ErrorHandler&& errorHandler);
        void Post(const std::string& message);

    private:
        explicit TCPConnection(io::ip::tcp::socket&& socket);

        // Wait for a new message from client
        void asyncRead();
        void onRead(boost::system::error_code ec, size_t bytesTranferred);

        void asyncWrite();
        void onWrite(boost::system::error_code ec, size_t bytesTransferred);

    private:
        tcp::socket _socket;
        std::string _username;
        std::string init_message = "Tic-Tac-Toe is a classic and popular paper-and-pencil game played on a 3x3 grid. It's a two-player game where each player takes turns marking a square with their respective symbol, either \"X\" or \"O\". The goal is to form a straight line of three of your symbols horizontally, vertically, or diagonally.\n"
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
                                   "    If the game ends in a tie, it is declared a draw.\n"
                                   "\n"
                                   "To play tic-tac-toe on a computer by entering \"ij\" numbers, follow these steps:\n"
                                   "\n"
                                   "    The game is played on a 3x3 grid. Each square in the grid is labeled with two numbers, \"i\" and \"j\", representing its row and column positions.\n"
                                   "    The grid is labeled as follows:\n"
                                   "\n"
                                   "    00 | 01 | 02\n"
                                   "    10 | 11 | 12\n"
                                   "    20 | 21 | 22\n"
                                   "\n"
                                   "    Two players take turns playing the game. The first player to enter a valid input becomes Player 1 and is assigned the symbol \"O\", and the second player becomes Player 2 and is assigned the symbol \"X\".\n"
                                   "\n"
                                   "    If you enter your input and a new board doesn't print out, it means something went wrong or the space is already taken. Try entering one more time.\n"
                                   "\n"
                                   "    The game begins with an empty grid. Each player takes turns entering the \"ij\" number corresponding to the square they want to mark.\n"
                                   "\n"
                                   "    To make a move, the player enters the \"ij\" number representing the position they want to mark. For example, if Player 1 wants to mark the top-right corner, they would enter \"02\".\n"
                                   "\n"
                                   "    After each move, the updated grid is displayed, showing the current positions of the symbols.\n"
                                   "\n"
                                   "    The game continues with players taking turns until one of the following conditions is met:\n"
                                   "        A player gets three of their symbols in a horizontal, vertical, or diagonal line, forming a winning combination. For example, three \"X\" symbols in a row.\n"
                                   "        All squares on the grid are filled, resulting in a tie if no winning combination is formed.\n"
                                   "\n"
                                   "    If a winning condition is met, the game ends, and the player who achieved it is declared the winner. The winning player's symbol (\"X\" or \"O\") is displayed.\n"
                                   "\n"
                                   "    If the game ends in a tie, it is announced by printing \"It's a tie!\", indicating that no player has won.\n"
                                   "\n"
                                   "Remember, the \"ij\" numbers correspond to the row and column positions on the grid, allowing you to specify where you want to place your symbol.";
        std::queue<std::string> _outgoingMessages;
        io::streambuf _streamBuf {65536};

        MessageHandler _messageHandler;
        ErrorHandler _errorHandler;
    };
}


