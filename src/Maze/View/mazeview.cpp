#include "mazeview.h"

#include <QDebug>

#include "../Model/maze_path_finding.h"

s21::MazeView::MazeView(s21::BaseController *mazeWalls, QWidget *parent)
    : QWidget(parent) {
  mazeWalls_ = mazeWalls;
}

void s21::MazeView::SetMazeWalls(BaseController *mazeWalls) {
  isPressMazeView_ = false;
  isStartPositionSet_ = false;
  isEndPositionSet_ = false;
  startPos_.first = 0;
  startPos_.second = 0;
  mazeWalls_ = mazeWalls;
}

void s21::MazeView::paintEvent(QPaintEvent *event) {
  if (mazeWalls_ == nullptr) return;
  QPainter painter(this);
  int colSize =
      mazeWalls_->GetSizeCol() == 0
          ? 0
          : 500 / (mazeWalls_->GetSizeCol());  // Размер одной клетки лабиринта
  int rowSize =
      mazeWalls_->GetSizeRow() == 0 ? 0 : 500 / (mazeWalls_->GetSizeRow());

  for (size_t i = 0; i < mazeWalls_->GetSizeRow(); ++i) {
    painter.fillRect(0, i * rowSize, 2, rowSize, Qt::black);
    for (size_t j = 0; j < mazeWalls_->GetSizeCol(); ++j) {
      painter.fillRect(j * colSize, 0, colSize, 2, Qt::black);
      if (mazeWalls_->GetRightWalls()[i][j] == 1) {
        painter.fillRect((j + 1) * colSize - 2, i * rowSize, 2, rowSize,
                         Qt::black);
      }
      if (mazeWalls_->GetBottomWalls()[i][j] == 1) {
        painter.fillRect(j * colSize, (i + 1) * rowSize - 2, colSize, 2,
                         Qt::black);
      }
    }
  }
  paintPath(painter, colSize, rowSize);
}

void s21::MazeView::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    handleMousePress(event->pos());
  }
}

void s21::MazeView::handleMousePress(const QPoint &pos) {
  if (mazeWalls_->GetSizeCol() == 0 || mazeWalls_->GetSizeRow() == 0) return;
  qDebug() << "Mouse pressed at:" << pos;
  qDebug() << "CoordX:" << qFloor(pos.x() / 500.0 * mazeWalls_->GetSizeCol());
  qDebug() << "CoordY:" << qFloor(pos.y() / 500.0 * mazeWalls_->GetSizeRow());
  if (isStartPositionSet_ == false) {
    startPos_.second = qFloor(pos.x() / 500.0 * mazeWalls_->GetSizeCol());
    startPos_.first = qFloor(pos.y() / 500.0 * mazeWalls_->GetSizeRow());
    isStartPositionSet_ = true;
    isPressMazeView_ = true;
  } else {
    endPos_.second = qFloor(pos.x() / 500.0 * mazeWalls_->GetSizeCol());
    endPos_.first = qFloor(pos.y() / 500.0 * mazeWalls_->GetSizeRow());
    isEndPositionSet_ = true;

    //вычисление маршрута
    MazePathFinding mazePathFinding(mazeWalls_->GetRightWalls(),
                                    mazeWalls_->GetBottomWalls());
    std::vector<Point> vec = mazePathFinding.Solver(startPos_, endPos_);
    pointsPath_.clear();
    pointsPath_.push_back(Point(startPos_.second, startPos_.first));
    for (Point p : vec) {
      pointsPath_.push_back(Point(p.second, p.first));
      qDebug() << p.first << p.second;
    }
  }
  update();
}

void s21::MazeView::paintPath(QPainter &painter, int colSize, int rowSize) {
  if (isPressMazeView_)
    painter.fillRect(startPos_.second * colSize + colSize / 2 - 5,
                     startPos_.first * rowSize + rowSize / 2 - 5, 10, 10,
                     Qt::blue);
  if (isPressMazeView_ && isEndPositionSet_)
    painter.fillRect(endPos_.second * colSize + colSize / 2 - 5,
                     endPos_.first * rowSize + rowSize / 2 - 5, 10, 10,
                     Qt::red);
  endPos_.first = startPos_.first;
  endPos_.second = startPos_.second;

  // Устанавливаем перо толщиной 2 пикселя
  QPen pen(Qt::red);
  pen.setWidth(2);
  painter.setPen(pen);

  if (pointsPath_.size() > 0) {
    for (size_t i = 0; i < pointsPath_.size() - 1; ++i) {
      painter.drawLine(pointsPath_[i].first * colSize + colSize / 2,
                       pointsPath_[i].second * rowSize + rowSize / 2,
                       pointsPath_[i + 1].first * colSize + colSize / 2,
                       pointsPath_[i + 1].second * rowSize + rowSize / 2);
    }
    pointsPath_.clear();
  }

  if (isPressMazeView_)
    painter.fillRect(startPos_.second * colSize + colSize / 2 - 5,
                     startPos_.first * rowSize + rowSize / 2 - 5, 10, 10,
                     Qt::blue);
}
