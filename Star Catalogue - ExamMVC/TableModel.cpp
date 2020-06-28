#include "TableModel.h"
#include <algorithm>

int TableModel::rowCount(const QModelIndex& parent) const
{
	return this->repo.getStars().size();
}

int TableModel::columnCount(const QModelIndex& parent) const
{
	return 5;
}


QVariant TableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row(), col = index.column();
	Star current = this->repo.getStars()[row];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (col)
		{
		case 0:
			return QString::fromStdString(current.getName());
		case 1:
			return QString::fromStdString(current.getConstellation());
		case 2:
			return QString::number(current.getRA());
		case 3:
			return QString::number(current.getDec());
		case 4:
			return QString::number(current.getDiam());
		default:
			break;
		}
	}
	return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return "Name";
			case 1:
				return "Constellation";
			case 2:
				return "Right Ascension";
			case 3:
				return "Declination";
			case 4:
				return "Diameter";
			default:
				break;
			}
		}
	}
	return QVariant();
}

void TableModel::update()
{
	emit layoutAboutToBeChanged();
	emit layoutChanged();
}