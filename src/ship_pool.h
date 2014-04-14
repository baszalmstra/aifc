#pragma once

#include <array>
#include "ship_state.h"

class FactionState;
class ShipPool
{
  enum
  {
    kMaxShips = 4 * 1024,
    kIndexMask = 0xffff,
    kNewObjectAdd = 0x10000,
  };

public:
  typedef ShipState* iterator;
  typedef ShipState const* const_iterator;

public:
  // Default constructor
  ShipPool();

  /// Returns true if a ship with the given id exists
  bool has(uint32_t id) const;

  /// Returns the ship with the given id
  ShipState &lookup(uint32_t id) { return ships_[indices_[id & kIndexMask].index]; }
  const ShipState &lookup(uint32_t id) const { ships_[indices_[id & kIndexMask].index]; }

  /// Adds a new ship for the given faction
  ShipState& Add(FactionState& faction);  

  /// Removes the ship with the given id
  void Remove(uint32_t id);
  void Remove(ShipState& state);

  /// Returns an iterator to the beginning 
  iterator begin() { return ships_.data(); }
  const_iterator begin() const { return ships_.data(); }
  iterator end() { return ships_.data() + numShips_; }
  const_iterator end() const { return ships_.data() + numShips_; }

  /// Erases an element from the pool
  iterator erase(iterator it) { Remove(*it); return it; }

private:
  struct Index
  {
    uint32_t id;
    uint16_t index;
    uint16_t next;
  };

  std::array<Index, kMaxShips> indices_;
  std::array<ShipState, kMaxShips> ships_;
  uint16_t numShips_;
  uint16_t freeListDequeue_, freeListEnqueue_;
};