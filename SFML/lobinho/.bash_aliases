

function ksf{
    g++ -Wall -Wextra -Werror -std=c++20 -g -lm -lsfml-graphics -lsfml-window -lsfml-system solver.cpp -o solver.out && ./solver.out
}

g++ solver.cpp -o solver -lsfml-graphics -lsfml-window -lsfml-system

