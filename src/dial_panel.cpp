#include <kcctplugin/dial_panel.h>
#include <pluginlib/class_list_macros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float32.h>

#include "ui_dial_panel.h"
#include <kcctplugin/button_status.h>

namespace kcctplugin
{
NavigationPanel::NavigationPanel(QWidget* parent) : Panel(parent),  ui_(new Ui::DialUI())
{
  ui_->setupUi(this);
}

NavigationPanel::~NavigationPanel() = default;

void NavigationPanel::onInitialize()
{
  //connect(ui_->dial, SIGNAL(valueChanged(int)), this , SLOT(dialValueChanged(int)));
  connect(ui_->start_button, SIGNAL(clicked()), this, SLOT(startClicked()));
  connect(ui_->pause_button, SIGNAL(clicked()), this, SLOT(pauseClicked()));
  connect(ui_->initialpose_button, SIGNAL(clicked()), this, SLOT(initialposeClicked()));
  connect(ui_->plus_button, SIGNAL(clicked()), this, SLOT(plusClicked()));
  connect(ui_->mynus_button, SIGNAL(clicked()), this, SLOT(mynusClicked()));
  connect(ui_->reset_button, SIGNAL(clicked()), this, SLOT(resetClicked()));

  connect(ui_->waypoint_box, SIGNAL(valueChanged(int)), this , SLOT(ValueChanged(int)));
  connect(ui_->publish_button, SIGNAL(clicked()), this, SLOT(publishClicked()));

  //3d pose estimate
  connect(ui_->zposition, SIGNAL(valueChanged(double)), this , SLOT(zposition(double)));
  connect(ui_->zposition_button, SIGNAL(clicked()), this, SLOT(zpublishClicked()));


  //ui_->line_edit->setPlaceholderText("Input topic name (Default : dial)");
  //connect(ui_->line_edit,  SIGNAL(textChanged(const QString &)), this, SLOT(lineEditChanged()));

  pub_ = nh_.advertise<std_msgs::Int32>("buttons", 1);
  wppub_ = nh_.advertise<std_msgs::Int32>("waypoint/set", 1);
  zpub=nh_.advertise<std_msgs::Float32>("initialpose_z", 1);
  parentWidget()->setVisible(true);
}

void NavigationPanel::onEnable()
{
  show();
  parentWidget()->show();
}

void NavigationPanel::onDisable()
{
  hide();
  parentWidget()->hide();
}

/*
void NavigationPanel::lineEditChanged()
{
  std::string old_topic_name = topic_name_;
  if(ui_->line_edit->text().isEmpty())
    topic_name_ = "dial";
  else
    topic_name_ = ui_->line_edit->text().toStdString();

  ROS_INFO("You set the topic name : %s", topic_name_.c_str());

  if(old_topic_name != topic_name_)
    pub_ = nh_.advertise<std_msgs::Float64>(topic_name_, 1);
}*/
/*
void NavigationPanel::dialValueChanged(int value)
{
  ui_->lcd->display(value);
  value_ = value;
  ROS_INFO("You set the value : %d", value_);
}*/

void NavigationPanel::startClicked(){buttonClicked(buttons_status_start);}
void NavigationPanel::pauseClicked(){buttonClicked(buttons_status_pause);}
void NavigationPanel::initialposeClicked(){buttonClicked(buttons_status_initialpose);}
void NavigationPanel::plusClicked(){buttonClicked(buttons_status_plus);}
void NavigationPanel::mynusClicked(){buttonClicked(buttons_status_mynus);}
void NavigationPanel::zpublishClicked(){buttonClicked(buttons_status_zpublish);}

void NavigationPanel::resetClicked(){
  buttonClicked(buttons_status_reset);
  std_msgs::Int32 msg;
  msg.data = 0;
  wppub_.publish(msg);
}

void NavigationPanel::buttonClicked(int button_num)
{
  std_msgs::Int32 msg;
  msg.data = button_num;
  pub_.publish(msg);
  //ROS_INFO("You pushed the button Number[%d]",button_num);
}

void NavigationPanel::ValueChanged(int value)
{
  value_ = value;
  //ROS_INFO("You set the value : %d", value_);
}

void NavigationPanel::publishClicked()
{
  std_msgs::Int32 msg;
  msg.data = value_;
  wppub_.publish(msg);
  //ROS_INFO("WayPoint Number[%d]",value_);
}

void NavigationPanel::zposition(double zpos){
  std_msgs::Float32 msg;
  msg.data=zpos;
  zpub.publish(msg);
}


}  // namespace kcctplugin

PLUGINLIB_EXPORT_CLASS(kcctplugin::NavigationPanel, rviz::Panel )
