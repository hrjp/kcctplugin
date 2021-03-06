#pragma once

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif

#include <rviz/panel.h>

namespace Ui {
class DialUI;
}

namespace kcctplugin
{
class NavigationPanel: public rviz::Panel
{
  Q_OBJECT
 public:
  NavigationPanel(QWidget* parent = nullptr);
  ~NavigationPanel() override;

  void onInitialize() override;
  void onEnable();
  void onDisable();

  private:

private Q_SLOTS:
  
  //void lineEditChanged();
  void startClicked();
  void pauseClicked();
  void initialposeClicked();
  void plusClicked();
  void mynusClicked();
  void resetClicked();

  void buttonClicked(int button_num);

  void ValueChanged(int value);
  void publishClicked();

  void zposition(double zpos);
  void zpublishClicked();

protected:
  Ui::DialUI* ui_;
  int value_{0};
  std::string topic_name_{"dial"};

  ros::NodeHandle nh_;
  ros::Publisher pub_;
  ros::Publisher wppub_;
  ros::Publisher zpub;
};
} // end namespace kcctplugin
