/// 
/// PathManager.h
/// 
/// Manage pathfinding for all Objects.
/// 

#ifndef __PATH_MANAGER_H__
#define __PATH_MANAGER_H__

// System includes.
#include <string>
#include <vector>

// Engine includes.
#include "Manager.h"
#include "PathFind.h"

namespace df {

class PathManager : public Manager {

 private:
  PathManager();		      ///< Private since a singleton.
  PathManager(PathManager const&);    ///< Don't allow copy.
  void operator=(PathManager const&); ///< Don't allow assignment.
  std::vector<PathFind *> finder;     ///< PathFind's registered.
  int cycle_time;                     ///< Time for pathfinding, in millisec.
  
 public:

  /// Get the one and only instance of the PathManager.
  static PathManager &getInstance();

  /// Start up PathManager.
  int startUp();

  /// Shut down PathManager.
  void shutDown();

  /// Accept only pathfinding events.
  /// Returns false for other engine events.
  bool isValid(std::string event_type) const;

  /// Register PathFind with PathManager.
  /// Return 0 if ok, else -1.
  int registerPathFind(PathFind *p_path_find);

  /// Unregister PathFind with PathManager.
  /// Return 0 if ok, else -1.
  int unregisterPathFind(PathFind *p_path_find);

  // Cycle through the registered PathFinders until timeslice is used up.
  void cycle();
};

} // end of namespace df

#endif // __PATH_MANAGER_H__
