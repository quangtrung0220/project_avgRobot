#include <ros/ros.h>

#include "std_msgs/String.h"

#include "project_avgRobot/keyboard.h"

#include <string.h>

#include <signal.h>
#include <stdio.h>
#ifndef _WIN32
# include <termios.h>
# include <unistd.h>
#else
# include <windows.h>
#endif

#define KEYCODE_RIGHT 0x43
#define KEYCODE_LEFT 0x44
#define KEYCODE_UP 0x41
#define KEYCODE_DOWN 0x42
#define KEYCODE_Q 0x71

class KeyboardReader
{
public:
  KeyboardReader()
#ifndef _WIN32
    : kfd(0)
#endif
  {
#ifndef _WIN32
    // get the console in raw mode
    tcgetattr(kfd, &cooked);
    struct termios raw;
    memcpy(&raw, &cooked, sizeof(struct termios));
    raw.c_lflag &=~ (ICANON | ECHO);
    // Setting a new line, then end of file
    raw.c_cc[VEOL] = 1;
    raw.c_cc[VEOF] = 2;
    tcsetattr(kfd, TCSANOW, &raw);
#endif
  }
  void readOne(char * c)
  {
#ifndef _WIN32
    int rc = read(kfd, c, 1);
    if (rc < 0)
    {
      throw std::runtime_error("error");
    }
#else
    for(;;)
    {
      HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
      INPUT_RECORD buffer;
      DWORD events;
      PeekConsoleInput(handle, &buffer, 1, &events);
      if(events > 0)
      {
        ReadConsoleInput(handle, &buffer, 1, &events);
        if (buffer.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)
        {
          *c = KEYCODE_LEFT;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == VK_UP)
        {
          *c = KEYCODE_UP;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)
        {
          *c = KEYCODE_RIGHT;
          return;
        }
        else if (buffer.Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
        {
          *c = KEYCODE_DOWN;
          return;
        }
      }
    }
#endif
  }
  void shutdown()
  {
#ifndef _WIN32
    tcsetattr(kfd, TCSANOW, &cooked);
#endif
  }
private:
#ifndef _WIN32
  int kfd;
  struct termios cooked;
#endif
};

KeyboardReader input;

class TeleopRobot
{
public:
  TeleopRobot();
  void keyLoop();

private:

  ros::NodeHandle nh_;
  std::string _navigation;
  ros::Publisher twist_pub_;
  
};

TeleopRobot::TeleopRobot():
_navigation()
{

  twist_pub_ = nh_.advertise<project_avgRobot::keyboard>("input_keyboard", 1);
}

void quit(int sig)
{
  (void)sig;
  input.shutdown();
  ros::shutdown();
  exit(0);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "keyboard_publisher");
  TeleopRobot teleop_robot;

  signal(SIGINT,quit);

  teleop_robot.keyLoop();
  quit(0);
  
  return(0);
}


void TeleopRobot::keyLoop()
{
  char c;
  bool dirty=false;

  puts("Reading from keyboard");
  puts("Use arrow keys to move. 'q' to quit.");

  for(;;)
  {
    // get the next event from the keyboard  
    try
    {
      input.readOne(&c);
    }
    catch (const std::runtime_error &)
    {
      perror("read():");
      return;
    }

    ROS_DEBUG("value: 0x%02X\n", c);
  
    switch(c)
    {
      case KEYCODE_LEFT:
        ROS_DEBUG("LEFT");
        _navigation = "left";
        dirty = true;
        break;
      case KEYCODE_RIGHT:
        ROS_DEBUG("RIGHT");
        _navigation = "right";
        dirty = true;
        break;
      case KEYCODE_UP:
        ROS_DEBUG("UP");
        _navigation = "up";
        dirty = true;
        break;
      case KEYCODE_DOWN:
        ROS_DEBUG("DOWN");
        _navigation = "down";
        dirty = true;
        break;
      case KEYCODE_Q:
        ROS_DEBUG("quit");
        _navigation = "quit";
        return;
    }
   

    project_avgRobot::keyboard navi;
    
    navi.navigation=_navigation;
    if(dirty ==true)
    {
      twist_pub_.publish(navi);    
      dirty=false;
    }
  }


  return;
}



