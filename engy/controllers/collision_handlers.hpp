/**
  * @file
  */

#pragma once

#include "stdafx.hpp"


namespace Engy
{

/**
  * @addtogroup controllers
  * @{
  */

class Entity;

/**
 * @brief basicCollisionHandler
 * @param a considered entity
 * @param b object of the field
 */
void basicCollisionHandler(Entity * a, Entity const * b);

/**
 * @}
 */

} // Engy
