#include <boost/iterator/transform_iterator.hpp>

template <class Pt>
struct My_point_with_info
{
  typedef Pt Point;
  Pt p;
  explicit My_point_with_info(const Pt& pt):p(pt){}
  const Pt& point() const {return p;}
  int dimension() const { return p.dimension();}
};


template <class Point_>
struct Point_with_info_helper{
  typedef My_point_with_info<Point_> type;
};


struct Point_accessor{
  template <class Point>
  const Point& operator[](const My_point_with_info<Point>& p) const {return p.point();}
};

template <class Point>
const Point& get_point(const Point& p) {return p;}

template <class Point>
const Point& get_point(const My_point_with_info<Point>& p) {return Point_accessor()[p];}

template <class Point>
struct Create_point_with_info : public std::unary_function<Point,Point>{
  const Point& operator() (const Point& p) const { return p; }
};

template <class Point>
struct Create_point_with_info<My_point_with_info<Point> > : public std::unary_function<Point,My_point_with_info<Point> >{
  My_point_with_info<Point> operator() (const Point& p) const { return My_point_with_info<Point>(p); }
};
