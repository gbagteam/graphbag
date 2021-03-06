///////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify	 //
// it under the terms of the GNU General Public License as published by	 //
// the Free Software Foundation, either version 3 of the License, or	 //
// (at your option) any later version.					 //
//   									 //
// This program is distributed in the hope that it will be useful,	 //
// but WITHOUT ANY WARRANTY; without even the implied warranty of	 //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	 //
// GNU General Public License for more details.				 //
// 									 //
// You should have received a copy of the GNU General Public License	 //
// along with this program.  If not, see <http://www.gnu.org/licenses/>. //
///////////////////////////////////////////////////////////////////////////

#include <QtGui>

#include<QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsEllipseItem>


#include<QDebug>

class Vertex : public QGraphicsEllipseItem
{

public:

  Vertex( double x, double y, double r=20.0 )
    : QGraphicsEllipseItem( x-r/2, y-r/2, r, r ), radius( r )
  {

    //setPos( x, y );
    setFlag( QGraphicsItem::ItemIsMovable, true );

    //setFlag( QGraphicsItem::ItemIsSelectable, true );

    pen_color.setRgb( 88, 61, 164 );
    brush_color.setRgb( 154, 204, 50 );

    QPen pen(Qt::SolidLine);
    pen.setColor( Qt::black );
    pen.setWidth( 2 );

    setPen( pen );
    
    //QRadialGradient gradient(x, y, radius, x, y);
    //gradient.setColorAt(1, brush_color );
    //gradient.setColorAt(0, QColor::fromRgbF(0, 0, 0, 1));
    QBrush brush( Qt::darkGreen );
    setBrush( brush );

  }


  void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
  {

    QPointF pos(mouseEvent->pos());
    QPointF scene_pos( mouseEvent->scenePos());
      
    qDebug() << "Press in Vertex.";
    qDebug() <<"\tpos: " << pos;
    qDebug() <<"\tscene_pos: "<< scene_pos;
    qDebug() <<"\tItem currently at pos: " << this->pos();
    qDebug() <<"\tItem currently at scene_pos: "<< scenePos();

    qDebug();
    
    QGraphicsEllipseItem::mousePressEvent( mouseEvent );  

  }


  enum { Type = UserType + 1 };

  int type() const
  {
    return Type;
  }

private:

  double radius;
  QColor pen_color;
  QColor brush_color;


};

class GraphScene : public  QGraphicsScene
{
  
public:

  GraphScene( QGraphicsView *parent )
    : QGraphicsScene( parent )
  {}

  void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
  {
    
    QPointF pos(mouseEvent->pos());
    QPointF scene_pos( mouseEvent->scenePos());
    QPoint screen_pos( mouseEvent->screenPos());
      
    qDebug() << "Press in Scene.";
    qDebug() <<"\tpos: " << pos;
    qDebug() <<"\tscene_pos: "<< scene_pos;
    qDebug() <<"\tscreen_pos: "<< screen_pos;
    
    qDebug();

    if( itemAt( scene_pos ) ){

    QGraphicsScene::mousePressEvent( mouseEvent );  

    }else{

      Vertex* vx = new Vertex( scene_pos.x(), scene_pos.y() );
    
      addItem( vx );
    }

  }

};

class GraphView :
  public QGraphicsView
{

public:
  GraphView(): QGraphicsView()
  {
    setRenderHint(QPainter::Antialiasing);
  }

  void mousePressEvent ( QMouseEvent * event )
  {


    QPoint pos(event->pos());

    qDebug() << "Press in View.";
    qDebug() << "\tpos: "<< pos;

    QGraphicsView::mousePressEvent( event );  

  }

};


int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

  GraphView view;

  GraphScene scene( &view );

  view.setScene( &scene );
 
  
  scene.addLine(-100,0,0,0);
  scene.addLine(0,0,100,0);

  scene.addLine(0,-100,0,0);
  scene.addLine(0,-100,0,100);
  


  view.show();
  return app.exec();
}
