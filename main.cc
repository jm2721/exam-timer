#include "exam_timer.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char** argv)
{
  //creates the window
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "our.exam.timer");

  //creates an exam_timer object to create the timer and the widgets
  exam_timer exam_timer;

  //runs the program
  return app->run(exam_timer);
}
