#include "DisplayObject.hpp"

DisplayObject::DisplayObject(DisplayManager& manager)
    : manager(manager), done(false)
{
}

DisplayObject::~DisplayObject()
{
}
