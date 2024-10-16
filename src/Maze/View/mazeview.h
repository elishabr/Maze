#ifndef MAZEVIEW_H
#define MAZEVIEW_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

#include "../Controller/controller.h"

namespace s21 {
class MazeView : public QWidget {
  Q_OBJECT

 public:
  MazeView(BaseController* mazeWalls, QWidget* parent = nullptr);
  void SetMazeWalls(BaseController* mazeWalls);

 protected:
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;

 private:
  void handleMousePress(const QPoint& pos);
  void paintPath(QPainter& painter, int colSize, int rowSize);
  BaseController* mazeWalls_ = nullptr;

  Point startPos_{};
  Point endPos_{};
  std::vector<Point> pointsPath_{};
  bool isStartPositionSet_ = false;
  bool isPressMazeView_ = false;
  bool isEndPositionSet_ = false;
};
}  // namespace s21

#endif  // MAZEVIEW_H
