#ifndef RENDERABLEOBJECTS_H_
#define RENDERABLEOBJECTS_H_
#include "../RenderableObject/RenderableObject.h"
#include "../GameData/GameData.h"
#include <vector>
#include <memory>


class RenderableObjects
{
public:
    RenderableObjects();
    void Draw(std::shared_ptr<GameData> gameData);
    void AddRenderableObject(RenderableObject);
private:
    std::vector<RenderableObject> renderableObjectsData;
};
#endif