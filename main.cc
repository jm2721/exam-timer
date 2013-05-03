#include "exam_timer.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char** argv)
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "our.exam.timer");

  exam_timer exam_timer;

 
  return app->run(exam_timer);
}
