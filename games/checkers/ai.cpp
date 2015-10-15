// Generated by Creer at 10:14PM on October 15, 2015 UTC, git hash: '98604e3773d1933864742cb78acbf6ea0b4ecd7b'
// This is where you build your AI for the Checkers game.

#include "ai.h"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// you can add additional #includes here for your AI.
// <<-- /Creer-Merge: includes -->>



/// <summary>
/// This returns your AI's name to the game server. Just replace the string.
/// </summary>
/// <returns>string of you AI's name.</returns>
std::string Checkers::AI::getName()
{
    // <<-- Creer-Merge: get-name -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    return "Checkers C++ Player"; // REPLACE THIS WITH YOUR TEAM NAME!
    // <<-- /Creer-Merge: get-name -->>
}

/// <summary>
/// This is automatically called when the game first starts, once the Game object and all GameObjects have been initialized, but before any players do anything.
/// </summary>
void Checkers::AI::start()
{
    // <<-- Creer-Merge: start -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    std::srand(unsigned(std::time(0)));

    this->checkersMap.resize(this->game->boardWidth);
    for (int x = 0; x < this->game->boardWidth; x++)
    {
        this->checkersMap[x].resize(this->game->boardHeight);
    }

    this->clearCheckersMap();
    // <<-- /Creer-Merge: start -->>
}

/// <summary>
/// This is automatically called every time the game (or anything in it) updates.
/// </summary>
void Checkers::AI::gameUpdated()
{
    // <<-- Creer-Merge: game-updated -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    this->clearCheckersMap();

    this->forceChecker = nullptr;
    this->cantMove = false;

    for (auto checker : this->game->checkers)
    {
        this->checkersMap[checker->x][checker->y] = checker;

        if (checker->owner == this->player && checker == this->game->checkerMoved)
        {
            if (this->game->checkerMovedJumped)
            {
                this->forceChecker = checker;
            }
            else
            {
                this->cantMove = true;
            }
        }
    }
    // <<-- /Creer-Merge: game-updated -->>
}

/// <summary>
/// This is automatically called when the game ends.
/// </summary>
/// <param name="won">true if your player won, false otherwise</param>
/// <param name="reason">a string explaining why you won or lost</param>
void Checkers::AI::ended(bool won, std::string reason)
{
    // <<-- Creer-Merge: ended -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // You can do any cleanup of you AI here, or do custom logging. After this function returns the application will close.
    // <<-- /Creer-Merge: ended -->>
}


/// <summary>
/// This is called every time the AI is asked to respond with a command during their turn
/// </summary>
/// <returns>represents if you want to end your turn. true means end the turn, false means to keep your turn going and re-call runTurn()</returns>
bool Checkers::AI::runTurn()
{
    // <<-- Creer-Merge: runTurn -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    while (true) {
        auto moveData = this->findMove();

        if (moveData != nullptr)
        {
            moveData->checker->move(moveData->point.x, moveData->point.y);
            delete moveData;
        }
        else
        {
            break; // as we can't find any moves, so we are done with our turn
        }
    }

    return true;
    // <<-- /Creer-Merge: runTurn -->>
}

// <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
void Checkers::AI::clearCheckersMap()
{
    for (int x = 0; x < this->game->boardWidth; x++)
    {
        for (int y = 0; y < this->game->boardHeight; y++)
        {
            this->checkersMap[x][y] = nullptr;
        }
    }
}

Checkers::AI::MoveData* Checkers::AI::findMove()
{
    if (this->cantMove) {
        return nullptr;
    }

    std::vector<Checkers::Checker*> checkers;

    if (this->forceChecker != nullptr)
    {
        checkers.push_back(this->forceChecker);
    }
    else
    {
        checkers = std::vector<Checkers::Checker*>(this->player->checkers); // copy all my checkers to a new vector
    }

    std::random_shuffle(checkers.begin(), checkers.end());

    int yDirection = this->player->yDirection;
    auto moveData = new MoveData();
    for (auto checker : checkers)
    {
        std::vector<Checkers::AI::Point> neighbors;
        neighbors.push_back(Checkers::AI::Point(checker->x + 1, checker->y + yDirection));
        neighbors.push_back(Checkers::AI::Point(checker->x - 1, checker->y + yDirection));

        if (checker->kinged)
        {
            neighbors.push_back(Checkers::AI::Point(checker->x + 1, checker->y - yDirection));
            neighbors.push_back(Checkers::AI::Point(checker->x - 1, checker->y - yDirection));
        }

        std::random_shuffle(neighbors.begin(), neighbors.end());

        while (!neighbors.empty())
        {
            Checkers::AI::Point neighbor = neighbors.back();
            neighbors.pop_back();

            if (neighbor.x >= this->game->boardWidth || neighbor.x < 0 || neighbor.y >= this->game->boardHeight || neighbor.y < 0)
            {
                continue;
            }

            if (this->forceChecker != nullptr) // then mew MUST jump
            {
                if (neighbor.requiresJump) // and we can!
                {
                    moveData->checker = checker;
                    moveData->point = neighbor;
                    return moveData;
                }
            }
            else
            {
                Checkers::Checker* jumping = this->checkersMap[neighbor.x][neighbor.y];
                if (jumping == nullptr) // then this space is empty, sand safe!
                {
                    moveData->checker = checker;
                    moveData->point = neighbor;
                    return moveData;
                }
                else if (jumping->owner != checker->owner)
                {
                    if (!neighbor.requiresJump)
                    {
                        int dx = neighbor.x - checker->x;
                        int dy = neighbor.y - checker->y;

                        neighbors.push_back(Point(neighbor.x + dx, neighbor.y + dy, true));
                    }
                }
            }
        }
    }

    delete moveData;
    return nullptr;
}
// <<-- /Creer-Merge: methods -->>
