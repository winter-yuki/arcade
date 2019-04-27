#include "stdafx.hpp"

#include "game.hpp"


int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    Game game;
    game.launch();

    return QApplication::exec();
}
