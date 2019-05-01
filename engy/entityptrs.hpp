/**
  * @file
  */

#pragma once

#include "stdafx.hpp"


namespace Engy
{

/**
 * @addtogroup core
 * @{
 */
class Entity;
using EntityS = std::shared_ptr<Entity>;
using EntityW = std::weak_ptr  <Entity>;

/**
  * @}
  */

} // Engy
