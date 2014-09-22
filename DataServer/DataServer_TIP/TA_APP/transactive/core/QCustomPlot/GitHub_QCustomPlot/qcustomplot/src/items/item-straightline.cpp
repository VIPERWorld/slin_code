/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011, 2012, 2013, 2014 Emanuel Eichhammer               **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 07.04.14                                             **
**          Version: 1.2.1                                                **
****************************************************************************/

#include "item-straightline.h"

#include "../painter.h"
#include "../core.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// QCPItemStraightLine
////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \class QCPItemStraightLine
  \brief A straight line that spans infinitely in both directions

  \image html QCPItemStraightLine.png "Straight line example. Blue dotted circles are anchors, solid blue discs are positions."

  It has two positions, \a point1 and \a point2, which define the straight line.
*/

/*!
  Creates a straight line item and sets default values.
  
  The constructed item can be added to the plot with QCustomPlot::addItem.
*/
QCPItemStraightLine::QCPItemStraightLine(QCustomPlot *parentPlot) :
  QCPAbstractItem(parentPlot),
  point1(createPosition("point1")),
  point2(createPosition("point2"))
{
  point1->setCoords(0, 0);
  point2->setCoords(1, 1);
  
  setPen(QPen(Qt::black));
  setSelectedPen(QPen(Qt::blue,2));
}

QCPItemStraightLine::~QCPItemStraightLine()
{
}

/*!
  Sets the pen that will be used to draw the line
  
  \see setSelectedPen
*/
void QCPItemStraightLine::setPen(const QPen &pen)
{
  mPen = pen;
}

/*!
  Sets the pen that will be used to draw the line when selected
  
  \see setPen, setSelected
*/
void QCPItemStraightLine::setSelectedPen(const QPen &pen)
{
  mSelectedPen = pen;
}

/* inherits documentation from base class */
double QCPItemStraightLine::selectTest(const QPointF &pos, bool onlySelectable, QVariant *details) const
{
  Q_UNUSED(details)
  if (onlySelectable && !mSelectable)
    return -1;
  
  return distToStraightLine(QVector2D(point1->pixelPoint()), QVector2D(point2->pixelPoint()-point1->pixelPoint()), QVector2D(pos));
}

/* inherits documentation from base class */
void QCPItemStraightLine::draw(QCPPainter *painter)
{
  QVector2D start(point1->pixelPoint());
  QVector2D end(point2->pixelPoint());
  // get visible segment of straight line inside clipRect:
  double clipPad = mainPen().widthF();
  QLineF line = getRectClippedStraightLine(start, end-start, clipRect().adjusted(-clipPad, -clipPad, clipPad, clipPad));
  // paint visible segment, if existent:
  if (!line.isNull())
  {
    painter->setPen(mainPen());
    painter->drawLine(line);
  }
}

/*! \internal

  finds the shortest distance of \a point to the straight line defined by the base point \a
  base and the direction vector \a vec.
  
  This is a helper function for \ref selectTest.
*/
double QCPItemStraightLine::distToStraightLine(const QVector2D &base, const QVector2D &vec, const QVector2D &point) const
{
  return qAbs((base.y()-point.y())*vec.x()-(base.x()-point.x())*vec.y())/vec.length();
}

/*! \internal

  Returns the section of the straight line defined by \a base and direction vector \a
  vec, that is visible in the specified \a rect.
  
  This is a helper function for \ref draw.
*/
QLineF QCPItemStraightLine::getRectClippedStraightLine(const QVector2D &base, const QVector2D &vec, const QRect &rect) const
{
  double bx, by;
  double gamma;
  QLineF result;
  if (vec.x() == 0 && vec.y() == 0)
    return result;
  if (qFuzzyIsNull(vec.x())) // line is vertical
  {
    // check top of rect:
    bx = rect.left();
    by = rect.top();
    gamma = base.x()-bx + (by-base.y())*vec.x()/vec.y();
    if (gamma >= 0 && gamma <= rect.width())
      result.setLine(bx+gamma, rect.top(), bx+gamma, rect.bottom()); // no need to check bottom because we know line is vertical
  } else if (qFuzzyIsNull(vec.y())) // line is horizontal
  {
    // check left of rect:
    bx = rect.left();
    by = rect.top();
    gamma = base.y()-by + (bx-base.x())*vec.y()/vec.x();
    if (gamma >= 0 && gamma <= rect.height())
      result.setLine(rect.left(), by+gamma, rect.right(), by+gamma); // no need to check right because we know line is horizontal
  } else // line is skewed
  {
    QList<QVector2D> pointVectors;
    // check top of rect:
    bx = rect.left();
    by = rect.top();
    gamma = base.x()-bx + (by-base.y())*vec.x()/vec.y();
    if (gamma >= 0 && gamma <= rect.width())
      pointVectors.append(QVector2D(bx+gamma, by));
    // check bottom of rect:
    bx = rect.left();
    by = rect.bottom();
    gamma = base.x()-bx + (by-base.y())*vec.x()/vec.y();
    if (gamma >= 0 && gamma <= rect.width())
      pointVectors.append(QVector2D(bx+gamma, by));
    // check left of rect:
    bx = rect.left();
    by = rect.top();
    gamma = base.y()-by + (bx-base.x())*vec.y()/vec.x();
    if (gamma >= 0 && gamma <= rect.height())
      pointVectors.append(QVector2D(bx, by+gamma));
    // check right of rect:
    bx = rect.right();
    by = rect.top();
    gamma = base.y()-by + (bx-base.x())*vec.y()/vec.x();
    if (gamma >= 0 && gamma <= rect.height())
      pointVectors.append(QVector2D(bx, by+gamma));
    
    // evaluate points:
    if (pointVectors.size() == 2)
    {
      result.setPoints(pointVectors.at(0).toPointF(), pointVectors.at(1).toPointF());
    } else if (pointVectors.size() > 2)
    {
      // line probably goes through corner of rect, and we got two points there. single out the point pair with greatest distance:
      double distSqrMax = 0;
      QVector2D pv1, pv2;
      for (int i=0; i<pointVectors.size()-1; ++i)
      {
        for (int k=i+1; k<pointVectors.size(); ++k)
        {
          double distSqr = (pointVectors.at(i)-pointVectors.at(k)).lengthSquared();
          if (distSqr > distSqrMax)
          {
            pv1 = pointVectors.at(i);
            pv2 = pointVectors.at(k);
            distSqrMax = distSqr;
          }
        }
      }
      result.setPoints(pv1.toPointF(), pv2.toPointF());
    }
  }
  return result;
}

/*! \internal

  Returns the pen that should be used for drawing lines. Returns mPen when the
  item is not selected and mSelectedPen when it is.
*/
QPen QCPItemStraightLine::mainPen() const
{
  return mSelected ? mSelectedPen : mPen;
}
