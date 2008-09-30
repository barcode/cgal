#include <fstream>

// CGAL headers
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/partition_2.h>
#include <CGAL/Partition_traits_2.h>

// Qt headers
#include <QtGui>
#include <QString>
#include <QActionGroup>
#include <QFileDialog>
#include <QInputDialog>

// GraphicsView items and event filters (input classes)
#include <CGAL/Qt/GraphicsViewPolylineInput.h>
#include <CGAL/Qt/PolygonGraphicsItem.h>
  
// the two base classes
#include "ui_Polygon_2.h"
#include <CGAL/Qt/DemosMainWindow.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

typedef CGAL::Polygon_2<K,std::list<Point_2> > Polygon; // it must be a list for the partition

class MainWindow :
  public CGAL::Qt::DemosMainWindow,
  public Ui::Polygon_2
{
  Q_OBJECT
  
private:  
  Polygon poly; 
  QGraphicsScene scene;  

  CGAL::Qt::PolygonGraphicsItem<Polygon> * pgi;

  CGAL::Qt::GraphicsViewPolylineInput<K> * pi;

  std::list<Polygon> partitionPolygons;
  std::list<CGAL::Qt::PolygonGraphicsItem<Polygon>* >  partitionGraphicsItems;

public:
  MainWindow();

public slots:

  void processInput(CGAL::Object o);

  void on_actionClear_triggered();

  void on_actionRecenter_triggered();

  void on_actionCreateInputPolygon_toggled(bool);

  void on_actionPartition_triggered();

signals:
  void changed();
};


MainWindow::MainWindow()
  : DemosMainWindow()
{
  setupUi(this);

  // Add a GraphicItem for the Polygon_2
  pgi = new CGAL::Qt::PolygonGraphicsItem<Polygon>(&poly);

  QObject::connect(this, SIGNAL(changed()),
		   pgi, SLOT(modelChanged()));

  pgi->setVerticesPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  scene.addItem(pgi);

  // Setup input handlers. They get events before the scene gets them
  pi = new CGAL::Qt::GraphicsViewPolylineInput<K>(this, &scene, 0, true);

  this->actionCreateInputPolygon->setChecked(true);
  QObject::connect(pi, SIGNAL(generate(CGAL::Object)),
		   this, SLOT(processInput(CGAL::Object)));

  // 
  // Manual handling of actions
  //
  QObject::connect(this->actionQuit, SIGNAL(triggered()), 
		   this, SLOT(close()));

 
  //
  // Setup the scene and the view
  //
  scene.setItemIndexMethod(QGraphicsScene::NoIndex);
  scene.setSceneRect(-100, -100, 100, 100);
  this->graphicsView->setScene(&scene);

  // Uncomment the following line to get antialiasing by default.
//   actionUse_Antialiasing->setChecked(true);

  // Turn the vertical axis upside down
  this->graphicsView->matrix().scale(1, -1);
                                                      
  // The navigation adds zooming and translation functionality to the
  // QGraphicsView
  this->addNavigation(this->graphicsView);

  this->setupStatusBar();
  this->setupOptionsMenu();
  this->addAboutDemo(":/cgal/help/about_Polygon_2.html");
  this->addAboutCGAL();
}


void
MainWindow::processInput(CGAL::Object o)
{
  std::cout << "processInput" << std::endl;
  this->actionCreateInputPolygon->setChecked(false);
  std::list<Point_2> points;
  if(CGAL::assign(points, o)){
    if((points.size() == 1)&& poly.size()>0){
      Point_2 p = points.front();
      // make the inside test
      CGAL::Bounded_side bside   = poly.bounded_side(p);
      switch (bside) {
      case CGAL::ON_BOUNDED_SIDE:
	textEdit->append("  The point is inside the polygon"); break;
      case CGAL::ON_BOUNDARY:
	textEdit->append("  The point is on the boundary of the polygon"); break;
      case CGAL::ON_UNBOUNDED_SIDE:
	textEdit->append("  The point is outside the polygon"); break;
      }
    } else {
      poly.clear();
      if(points.front() == points.back()){
	points.pop_back();
      }
      poly.insert(poly.vertices_begin(), points.begin(), points.end());
      textEdit->clear();
      if(poly.is_empty()){
	textEdit->append("P is empty!");
      } else {
	if(poly.is_simple()){
	  textEdit->append("P is simple");
	  CGAL::Orientation o = poly.orientation();
	  switch (o) {
	  case CGAL::CLOCKWISE:
	    textEdit->append("P.orientation() == CLOCKWISE");
	    break;
	  case CGAL::COUNTERCLOCKWISE:
	    textEdit->append("P.orientation() == COUNTERCLOCKWISE");
	    break;
	  case CGAL::COLLINEAR:
	    textEdit->append("P.orientation() == COLLINEAR");
	    break;
	  }
	  textEdit->append(QString("The area of P is %1").arg(poly.area()));
	} else {
	  textEdit->append("P is not simple");
	}
      }
    }
    emit(changed());
  }
}

/* 
 *  Qt Automatic Connections
 *  http://doc.trolltech.com/4.4/designer-using-a-component.html#automatic-connections
 * 
 *  setupUi(this) generates connections to the slots named
 *  "on_<action_name>_<signal_name>"
 */

void
MainWindow::on_actionClear_triggered()
{
  poly.clear();
  emit(changed());
}

void
MainWindow::on_actionCreateInputPolygon_toggled(bool checked)
{
  poly.clear();
  if(checked){
    scene.installEventFilter(pi);
  } else {
    scene.removeEventFilter(pi);
  }
  emit(changed());
}

void
MainWindow::on_actionRecenter_triggered()
{
  this->graphicsView->setSceneRect(pgi->boundingRect());
  this->graphicsView->fitInView(pgi->boundingRect(), Qt::KeepAspectRatio);  
}

void
MainWindow::on_actionPartition_triggered()
{
  if(poly.size()>0){
    partitionPolygons.clear();
    if(! poly.is_counterclockwise_oriented()){
      poly.reverse_orientation();
    }
    CGAL::approx_convex_partition_2(poly.vertices_begin(), poly.vertices_end(), std::back_inserter(partitionPolygons));
    for(std::list<CGAL::Qt::PolygonGraphicsItem<Polygon>* >::iterator it = partitionGraphicsItems.begin();
	it != partitionGraphicsItems.end();
	++it){
      scene.removeItem(*it);
    }
    partitionGraphicsItems.clear();
    for(std::list<Polygon>::iterator it = partitionPolygons.begin();
	it != partitionPolygons.end();
	++it){
      partitionGraphicsItems.push_back(new CGAL::Qt::PolygonGraphicsItem<Polygon>(&(*it)));
      scene.addItem(partitionGraphicsItems.back());
    }
  }
}

#include "Polygon_2.moc"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  // Import resources from libCGALQt4.
  // See http://doc.trolltech.com/4.4/qdir.html#Q_INIT_RESOURCE
  Q_INIT_RESOURCE(File);
  Q_INIT_RESOURCE(Polygon_2);
  Q_INIT_RESOURCE(Input);
  Q_INIT_RESOURCE(CGAL);

  MainWindow mainWindow;
  mainWindow.show();
  return app.exec();
}
