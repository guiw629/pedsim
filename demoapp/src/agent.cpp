//
// pedsim - A microscopic pedestrian simulation system. 
// Copyright (c) 2003 - 2004 by Christian Gloor
//                              


#include "math.h"

#include "ped_vector.h"

#include "agent.h"

#include "obstacle.h"
#include "config.h"

#include <iostream>

#include <QPen>
#include <QGraphicsScene>

extern Config config;

using namespace std;

/// 
/// \author  chgloor
/// \date    2012-01-17
Agent::Agent(QGraphicsScene *pscene) : Tagent() {
  graphicsscene = pscene;
  rect = graphicsscene->addRect(QRectF(0,0,1,1), QPen(Qt::darkGreen, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin), QBrush(QColor(Qt::darkGreen)));	
  lineea = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::red, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  lineoa = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::blue, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  linesa = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::green, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  linelfa = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::magenta, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
  linev  = graphicsscene->addLine(QLineF(0, 0, 1, 1), QPen(Qt::yellow, 0.1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));	
};


/// 
/// \author  chgloor
/// \date    2012-01-17
Ped::Tvector Agent::socialForce() {
	Ped::Tvector t = Tagent::socialForce();
	if (config.showForces == true) {
		linesa->setLine(getx(), gety(), getx()+config.simPedForce*t.x, gety()+config.simPedForce*t.y);
		linesa->setVisible(true);
	} else {
		linesa->setVisible(false);
	}	
	return t;
}

/// 
/// \author  chgloor
/// \date    2012-01-17
Ped::Tvector Agent::obstacleForce() {
	Ped::Tvector t = Tagent::obstacleForce();
	if (config.showForces == true) {
		lineoa->setLine(getx(), gety(), getx()+config.simWallForce*t.x, gety()+config.simWallForce*t.y);
		lineoa->setVisible(true);
	} else {
		lineoa->setVisible(false);
	}	
	return t;
}

/// 
/// \author  chgloor
/// \date    2012-01-17
Ped::Tvector Agent::desiredForce() {
	Ped::Tvector t = Tagent::desiredForce();
	if (config.showForces == true) {
		lineea->setLine(getx(), gety(), getx()+1.0f*t.x, gety()+1.0*t.y);
		lineea->setVisible(true);
	} else {
		lineea->setVisible(false);
	}	
	return t;
}

/// 
/// \author  chgloor
/// \date    2012-01-17
Ped::Tvector Agent::lookaheadForce(Ped::Tvector desired) {
	Ped::Tvector t;
	if (config.mlLookAhead == true) {
		t = Tagent::lookaheadForce(desired);
	}
	if (config.showForces == true) {
		linelfa->setLine(getx(), gety(), getx()+1.0f*t.x, gety()+1.0*t.y);
		linelfa->setVisible(true);
	} else {
		linelfa->setVisible(false);
	}	
	return t;
}


/// 
/// \author  chgloor
/// \date    2012-01-17
void Agent::move(double h) {

	setfactorsocialforce(config.simPedForce);
	setfactorobstacleforce(config.simWallForce);

	Tagent::move(h);

	rect->setPos(getx()-0.5, gety()-0.5); // upper left edge
	
 	if (config.showDirection == true) {
		linev->setLine(getx(), gety(), getx()+1.0*getvx(), gety()+1.0*getvy());
		linev->setVisible(true);
	} else { linev->setVisible(false); }

}