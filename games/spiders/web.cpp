// Generated by Creer at 03:31AM on April 24, 2016 UTC, git hash: '087b1901032ab5bed5806b24830233eac5c2de55'
// A connection (edge) to a Nest (node) in the game that Spiders can converge on (regardless of owner). Spiders can travel in either direction on Webs.

#include "web.h"
#include "gameManager.h"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// you can add additional #includes(s) here.
// <<-- /Creer-Merge: includes -->>




void Spiders::Web::deltaUpdateField(const std::string& fieldName, boost::property_tree::ptree& delta)
{
    Spiders::GameObject::deltaUpdateField(fieldName, delta);

    if (fieldName == "length")
    {
        this->length = this->gameManager->unserializeDouble(delta);
    }
    else if (fieldName == "load")
    {
        this->load = this->gameManager->unserializeInt(delta);
    }
    else if (fieldName == "nestA")
    {
        this->nestA = (Spiders::Nest*)this->gameManager->unserializeGameObject(delta);
    }
    else if (fieldName == "nestB")
    {
        this->nestB = (Spiders::Nest*)this->gameManager->unserializeGameObject(delta);
    }
    else if (fieldName == "spiderlings")
    {
        this->spiderlings = this->gameManager->unserializeVectorOfGameObjects<Spiders::Spiderling*>(delta, &this->spiderlings);
    }
    else if (fieldName == "strength")
    {
        this->strength = this->gameManager->unserializeInt(delta);
    }
}




// <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// if you forward declaired additional methods to the Web then you can code them here.
// <<-- /Creer-Merge: methods -->>
