/***************************************************************************
 *                                                                         *
 * Copyright (C) 2007-2015 by Johan De Taeye, frePPLe bvba                 *
 *                                                                         *
 * This library is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU Affero General Public License as published   *
 * by the Free Software Foundation; either version 3 of the License, or    *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This library is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            *
 * GNU Affero General Public License for more details.                     *
 *                                                                         *
 * You should have received a copy of the GNU Affero General Public        *
 * License along with this program.                                        *
 * If not, see <http://www.gnu.org/licenses/>.                             *
 *                                                                         *
 ***************************************************************************/

#define FREPPLE_CORE
#include "frepple/model.h"

namespace frepple
{

template<class Item> DECLARE_EXPORT Tree utils::HasName<Item>::st;
DECLARE_EXPORT const MetaCategory* Item::metadata;
DECLARE_EXPORT const MetaClass* ItemDefault::metadata;


int Item::initialize()
{
  // Initialize the metadata
  metadata = MetaCategory::registerCategory<Item>("item", "items", reader, writer, finder);
  registerFields<Item>(const_cast<MetaCategory*>(metadata));

  // Initialize the Python class
  return FreppleCategory<Item>::initialize();
}


int ItemDefault::initialize()
{
  // Initialize the metadata
  ItemDefault::metadata = MetaClass::registerClass<ItemDefault>("item", "item_default",
      Object::create<ItemDefault>, true);

  // Initialize the Python class
  return FreppleClass<ItemDefault,Item>::initialize();
}


DECLARE_EXPORT Item::~Item()
{
  // Remove references from the buffers
  for (Buffer::iterator buf = Buffer::begin(); buf != Buffer::end(); ++buf)
    if (buf->getItem() == this) buf->setItem(NULL);

  // Remove references from the demands
  for (Demand::iterator l = Demand::begin(); l != Demand::end(); ++l)
    if (l->getItem() == this) l->setItem(NULL);
}


} // end namespace
