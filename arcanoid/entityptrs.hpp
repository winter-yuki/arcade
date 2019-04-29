#pragma once

#include "stdafx.hpp"


class Entity;
using EntityS = std::shared_ptr<Entity>;
using EntityW = std::weak_ptr  <Entity>;
