#include "RenderableObjects.h"
#include <algorithm>

RenderableObjects::RenderableObjects()
{

}

void RenderableObjects::AddRenderableObject(RenderableObject renderableObject)
{
    renderableObjectsData.push_back(renderableObject);
}

void RenderableObjects::Draw(std::shared_ptr<GameData> gameData)
{
    std::sort(renderableObjectsData.begin(), renderableObjectsData.end(), [](auto& v1, auto& v2){
        return v1.distance > v2.distance;
    });
    for(auto& renderableObject : renderableObjectsData) gameData->window.draw(renderableObject.sprite);
    renderableObjectsData.clear();
}