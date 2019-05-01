/**
  * @file
  */

#pragma once

#include "stdafx.hpp"


namespace Engy
{

class Entity;
using EntityS = std::shared_ptr<Entity>;
using EntityW = std::weak_ptr  <Entity>;

}
