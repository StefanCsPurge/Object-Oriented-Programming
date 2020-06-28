#pragma once

#include <QWidget>
#include "ui_ViewWindow.h"
#include <QtWidgets/QMainWindow>
#include <QPen>
#include "domain.h"

class ViewWindow : public QWidget
{
	Q_OBJECT

public:
	ViewWindow(QWidget *parent = Q_NULLPTR);
	~ViewWindow();
	QSize sizeHint() const Q_DECL_OVERRIDE; // this must be redefined (the default implementation returns an invalid size, if there is no layout)
	void paintStars();

	void setStars(const vector<Star>& stars, const string& currentStar);
private:
	Ui::ViewWindow ui;
	vector<Star> stars;
	string currentStarName;

protected:
	void paintEvent(QPaintEvent* event) override;
};
