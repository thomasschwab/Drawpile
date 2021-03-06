/*
   DrawPile - a collaborative drawing program.

   Copyright (C) 2006-2009 Calle Laakkonen

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/
#ifndef BOARDITEM_H
#define BOARDITEM_H

#include <QGraphicsItem>

namespace dpcore {
	class Layer;
	class LayerStack;
	class Brush;
	class Point;
}

namespace drawingboard {

//! A drawing board item item for QGraphicsScene
/**
 * The board item provides an interface to a LayerStack for QGraphicsScene.
 * Methods are provided for drawing lines and points with a Brush object.
 */
class BoardItem : public QGraphicsItem
{
	public:
		//! Construct an empty layer
		BoardItem(QGraphicsItem *parent=0);

		//! Construct a layer from a QImage
		BoardItem(const QImage& image, QGraphicsItem *parent=0);

		//! Construct using a prepared layer stack
		BoardItem(dpcore::LayerStack *layers, QGraphicsItem *parent=0);

		~BoardItem();

		//! Set layer contents
		void setImage(const QImage& image);

		//! Get the image
		dpcore::LayerStack *image() const { return image_; }

		//! Draw a line between two points with interpolated pressure values
		void drawLine(int layer,const dpcore::Point& point1,
				const dpcore::Point& point2, const dpcore::Brush& brush,
				qreal &distance);

		//! Draw a single point
		void drawPoint(int layer, const dpcore::Point& point,
				const dpcore::Brush& brush);

		/** reimplematation */
		QRectF boundingRect() const;

	protected:
		/** reimplementation */
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
			 QWidget *);

	private:

		dpcore::LayerStack *image_;
		int plastx_, plasty_;
};

}

#endif


