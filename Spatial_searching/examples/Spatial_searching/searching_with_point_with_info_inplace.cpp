#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/basic.h>
#include <CGAL/Search_traits_3.h>
#include <CGAL/Search_traits_with_info.h>
#include <CGAL/point_generators_3.h>
#include <CGAL/Orthogonal_k_neighbor_search.h>
#include <boost/iterator/counting_iterator.hpp>
#include <utility>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point_3;

typedef std::size_t Point;

struct My_Point_accessor{
  const std::vector<Point_3>& points;
  My_Point_accessor(const std::vector<Point_3>& pts):points(pts){}
  const Point_3& operator[](std::size_t i) const {return points[i];}
};


typedef CGAL::Random_points_in_cube_3<Point_3>                                          Random_points_iterator;
typedef CGAL::Search_traits_3<Kernel>                                                   Traits_base;
typedef CGAL::Search_traits_with_info<Point,My_Point_accessor,Traits_base>              Traits;


typedef CGAL::Orthogonal_k_neighbor_search<Traits>                      K_neighbor_search;
typedef K_neighbor_search::Tree                                         Tree;
typedef Tree::Splitter                                                  Splitter;
typedef K_neighbor_search::Distance                                     Distance;

int main() {
  const unsigned int K = 5;
  // generator for random data points in the cube ( (-1,-1,-1), (1,1,1) )
  Random_points_iterator rpit( 1.0);
  std::vector<Point_3> points;
  
  points.push_back(Point_3(*rpit++));
  points.push_back(Point_3(*rpit++));
  points.push_back(Point_3(*rpit++));
  points.push_back(Point_3(*rpit++));
  points.push_back(Point_3(*rpit++));
  points.push_back(Point_3(*rpit++));
  points.push_back(Point_3(*rpit++));

  My_Point_accessor accessor(points);

  // Insert number_of_data_points in the tree
  Tree tree(
    boost::counting_iterator<std::size_t>(0),
    boost::counting_iterator<std::size_t>(points.size()),
    Splitter(),
    Traits(accessor)
  );
  Point_3 query(0.0, 0.0, 0.0);
  Distance tr_dist(accessor);

  // search K nearest neighbours
  K_neighbor_search search(tree, query, K,0,true,tr_dist);
  for(K_neighbor_search::iterator it = search.begin(); it != search.end(); it++){
    std::cout << " d(q, nearest neighbor)=  "
	      << tr_dist.inverse_of_transformed_distance(it->second) << " " << points[it->first] << " " << it->first << std::endl;
  }
  return 0;
}
