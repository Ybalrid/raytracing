#include "Object.hpp"

Object::Object(Vector3d pos) :
 position(pos), diffuseColor(1, 1, 1), specularColor(1, 1, 1), shinyness(12.5), emissiveColor(0.0125, 0.0125, 0.0125)
{
}
