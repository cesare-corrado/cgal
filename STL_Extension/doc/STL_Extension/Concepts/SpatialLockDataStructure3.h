
/*!
\ingroup PkgStlExtensionConcepts
\cgalConcept

The concept `SpatialLockDataStructure_3` is intended to be used by concurrent
algorithms. It allows to lock points (x, y, z) in a 3D bounding box.
Each templated type called `P3` below must provide x(), y() and z() functions
returning doubles.

\cgalHasModel `CGAL::Spatial_grid_lock_data_structure_3`

*/
class SpatialLockDataStructure_3 {
public:
  
/// \name Operations 
/// @{ 
  /// Set the bounding box of the domain
  /// Depending on the way one manages the 3D domain, this may be an
  /// empty function.
  void set_bbox(const CGAL::Bbox_3 &bbox);
  
  /// Test if `point` is locked by the current thread.
  template <typename P3>
  bool is_locked_by_this_thread(const P3 &point);

  /// Try to lock a point in the domain. Returns true if success.
  template <typename P3>
  bool try_lock(const P3 &point);

  /// Try to lock the point `p`. Returns true if success.
  /// \tparam no_spin If true, ask for non-blocking operation
  template <bool no_spin, typename P3>
  bool try_lock(const P3 &p);

  /// Unlock all the locations locked by this thread
  void unlock_all_points_locked_by_this_thread();
  
  /// Unlock all the locations locked by this thread except point `p`
  template <typename P3>
  void unlock_all_tls_locked_locations_but_one_point(const P3 &p);
/// @} 
};