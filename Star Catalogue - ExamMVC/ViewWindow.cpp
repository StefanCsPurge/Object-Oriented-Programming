#include "ViewWindow.h"
#include <QPainter>

ViewWindow::ViewWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

ViewWindow::~ViewWindow()
{
}

QSize ViewWindow::sizeHint() const
{
	return QSize{ 600, 400 };
}

void ViewWindow::paintStars()
{
	QPainter painter{ this };
	QPen redPen{ Qt::red, 1, Qt::SolidLine, Qt::RoundCap };
	QPen blackPen{ Qt::black, 1, Qt::SolidLine, Qt::RoundCap };
	painter.setPen(blackPen);
	for (auto star : stars)
	{
		if (star.getName() == currentStarName)
		{
			painter.setPen(redPen);
			painter.drawEllipse(star.getRA(), star.getDec(), star.getDiam() / 2, star.getDiam()/2);
			painter.setPen(blackPen);
		}
		else painter.drawEllipse(star.getRA(), star.getDec(), star.getDiam() / 2, star.getDiam() / 2);
	}
}

void ViewWindow::setStars(const vector<Star>& stars, const string& currentStar)
{
	this->stars = stars;
	this->currentStarName = currentStar;
}

void ViewWindow::paintEvent(QPaintEvent* event)
{
	paintStars();
}