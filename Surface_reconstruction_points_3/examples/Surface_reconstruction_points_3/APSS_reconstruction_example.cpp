#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh_default_triangulation_3.h>
#include <CGAL/make_surface_mesh.h>
#include <CGAL/Implicit_surface_3.h>
#include <CGAL/IO/Complex_2_in_triangulation_3_file_writer.h>
#include <CGAL/APSS_reconstruction_function.h>
#include <CGAL/Point_with_normal_3.h>
#include <CGAL/property_map.h>
#include <CGAL/IO/read_xyz_points.h>

#include <vector>
#include <fstream>

// Types
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::FT FT;
typedef Kernel::Point_3 Point;
typedef CGAL::Point_with_normal_3<Kernel> Point_with_normal;
typedef Kernel::Sphere_3 Sphere;
typedef std::vector<Point_with_normal> PointList;
typedef CGAL::APSS_reconstruction_function<Kernel> APSS_reconstruction_function;
typedef CGAL::Surface_mesh_default_triangulation_3 STr;
typedef CGAL::Surface_mesh_complex_2_in_triangulation_3<STr> C2t3;
typedef CGAL::Implicit_surface_3<Kernel, APSS_reconstruction_function> Surface_3;

int main(void)
{
    // Reads the point set file in points[].
    // Note: read_xyz_points_and_normals() requires an iterator over points
    // + property maps to access each point's position and normal.
    // The position property map can be omitted here as we use iterators over Point_3 elements.
    PointList points;
    std::ifstream stream("data/dragon.xyz");
    if (!stream ||
        !CGAL::read_xyz_points_and_normals(
                              stream,
                              std::back_inserter(points),
                              CGAL::make_normal_of_point_with_normal_pmap(std::back_inserter(points))))
    {
      std::cerr << "Error: cannot read file data/dragon.xyz" << std::endl;
      return EXIT_FAILURE;
    }

    // Creates implicit function from the read points.
    // Note: APSS_reconstruction_function() requires an iterator over points
    // + property maps to access each point's position and normal.
    // The position property map can be omitted here as we use iterators over Point_3 elements.

	// Smoothness factor: ranges from 2 for clean datasets
	// to 8 for noisy datasets
    const FT smoothness = (FT)2.0;
    APSS_reconstruction_function function(
                              points.begin(), points.end(),
                              CGAL::make_normal_of_point_with_normal_pmap(points.begin()),
                              smoothness);

    // Gets point inside the implicit surface
    // and computes implicit function bounding sphere radius
    Point inner_point = function.get_inner_point();
    Sphere bsphere = function.bounding_sphere();
	FT bsphere_radius = std::sqrt(bsphere.squared_radius());

    // Defines implicit surface: requires defining a
	// conservative bounding sphere centered at inner point
	FT radius = 2.01 * bsphere_radius;
    Surface_3 surface(function,
                      Sphere(inner_point,radius*radius));

    // defining meshing criteria
    // APSS options
    FT sm_shape = 20.0; // min triangle angle in degrees
    FT sm_size = 0.1; // max triangle size
    FT sm_approx = 0.003; // surface approximation error
    CGAL::Surface_mesh_default_criteria_3<STr> criteria(sm_shape,
                                                        sm_size * bsphere_radius,
                                                        sm_approx * bsphere_radius);

    // generates surface mesh with manifold-with-boundary option
    STr tr; // 3D Delaunay triangulation
    C2t3 c2t3(tr);  // 2D complex in 3D Delaunay triangulation
    CGAL::make_surface_mesh(c2t3,
                            surface,
                            criteria,
                            CGAL::Manifold_with_boundary_tag());

    if(tr.number_of_vertices() == 0)
      return EXIT_FAILURE;

    // saves reconstructed surface mesh
    std::ofstream out("dragon_apss.off");
    CGAL::output_surface_facets_to_off(out, c2t3);

    return EXIT_SUCCESS;
}