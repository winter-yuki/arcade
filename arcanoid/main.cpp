#include "stdafx.hpp"

#include "game.hpp"


int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    auto * game = new Game;
    game->launch();

    return QApplication::exec();
}
