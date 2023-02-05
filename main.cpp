#include "mainwindow.h"
//#include "explorer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    Explorer exp;
    w.show();
    return a.exec();
}


//#include <QScrollArea>
//#include <QVBoxLayout>
//#include <QSpinBox>
//#include <QApplication>

//class Window : public QWidget
//{
//   QScrollArea m_area{this};
//   QWidget m_contents;
//   QVBoxLayout m_contentsLayout{&m_contents};
//   QSpinBox m_spinBoxes[10];
//public:
//   Window(QWidget *parent = {}) : QWidget(parent) {
//       m_contentsLayout.setSizeConstraint(QLayout::SetMinimumSize);
//       m_area.show();
//      m_area.setWidget(&m_contents);
//      for (auto & spinbox : m_spinBoxes)
//         m_contentsLayout.addWidget(&spinbox);
//   }
//};

//int main(int argc, char *argv[])
//{
//   QApplication app(argc, argv);
//   Window w;
//   w.show();
//   return app.exec();
//}
