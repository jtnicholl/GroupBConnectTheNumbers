#include "GameController.h"

namespace controller
{

GameController* GameController::getSingleton()
{
    if (GameController::controller == nullptr)
    {
        // TODO: Instantiate with the concrete implementation class here.
        //GameController::controller = new ...
    }
    return GameController::controller;
}

GameController::~GameController()
{
}

}
