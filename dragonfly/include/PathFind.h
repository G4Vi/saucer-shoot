///
/// An A* pathfinding class.
///

#ifndef __PATHFIND_H__
#define __PATHFIND_H__

// Engine includes.
#include "EventPath.h"
#include "Object.h"
#include "Vector.h"

namespace df {

class Object;     // Forward reference.

// Coordinates for pathfinding.
struct coord_struct {
  int x, y;
};

// Graph nodes for pathfinding.
struct node_struct {
  float from_start; // cost from start
  float to_end;     // estimate to end + cost from start
  struct coord_struct came_from;  // most efficient path back
};

class PathFind {

 private:
  Object *p_o;	                        ///< Object finding path.
  coord_struct start;			///< Start position.
  coord_struct end;			///< End target position.
  struct node_struct **node;            ///< Nodes in graph.
  std::vector<coord_struct> open_set;   ///< Set of nodes not yet visited.
  std::vector<coord_struct> closed_set; ///< Set of nodes visited.
  int num_plies;		        ///< Number of plies cycled.

 public:
  PathFind(Object *p_o, Vector start, Vector end);
  ~PathFind();

  /// Go through one search cycle.  
  /// Returns indicatation if found path (found, not found, incomplete).
  SearchResult cycleOnce();

  /// Return path.
  Path getPath() const;

  /// Set object seeking path.
  void setObject(Object *new_p_o);

  /// Return object seeking path.
  Object *getObject() const;

  /// Return number of plies.
  int getNumPlies() const;
};

} // end of namespace df
#endif //__PATHFIND_H__
