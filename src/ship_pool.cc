#include "ship_pool.h"

//-------------------------------------------------------------------------------------------------
ShipPool::ShipPool() :
  numShips_(0),
  freeListDequeue_(0),
  freeListEnqueue_(kMaxShips-1)
{
  for (uint16_t i = 0; i < kMaxShips; ++i) 
  {
    indices_[i].id = i;
    indices_[i].next = i + 1;
  }
}

//-------------------------------------------------------------------------------------------------
bool ShipPool::has(uint32_t id) const
{
  const Index& idx = indices_[id & kIndexMask];
  return idx.id == id && idx.index != USHRT_MAX;
}

//-------------------------------------------------------------------------------------------------
ShipState& ShipPool::Add(FactionState& factionState)
{
  Index& idx = indices_[freeListDequeue_];
  freeListDequeue_ = idx.next;
  idx.id += kNewObjectAdd;
  idx.index = numShips_++;
  return *new (ships_.data() + idx.index) ShipState(factionState, idx.id);
}

//-------------------------------------------------------------------------------------------------
void ShipPool::Remove(ShipState& state)
{
  Remove(state.id());
}

//-------------------------------------------------------------------------------------------------
void ShipPool::Remove(uint32_t id)
{
  Index& idx = indices_[id & kIndexMask];

  ShipState& ship = ships_.data()[idx.index];
  if (idx.index < numShips_ - 1)
    ship = std::move(ships_.data()[numShips_ - 1]);
  ships_.data()[numShips_ - 1].~ShipState();
  indices_[ship.id() & kIndexMask].index = idx.index;
  numShips_--;

  idx.index = USHRT_MAX;
  indices_[freeListEnqueue_].next = id & kIndexMask;
  freeListEnqueue_ = id & kIndexMask;
}