#ifndef EXAM_TIMER_H
#define EXAM_TIMER_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/drawingarea.h>
#include "timer.h"

class exam_timer : public Gtk::Window
{
  public:
    exam_timer();
  protected:
    // Child widgets:
    Gtk::Box m_box1, m_hbox, m_spinButtonBox, m_labels_box, m_time;
    Glib::RefPtr<Gtk::Adjustment> m_adjustment_hours, m_adjustment_minutes, m_adjustment_seconds;   
    Gtk::Alignment m_alignment;
    Gtk::ProgressBar m_progressbar; 
    Gtk::Button m_start_button, m_pause_button, m_resume_button, m_stop_button;
    Gtk::Label m_label_hours, m_label_minutes, m_label_seconds, m_label_explanation;
    Gtk::SpinButton m_spinbutton_hours, m_spinbutton_minutes, m_spinbutton_seconds;

    timer timerArea;

    //functions to tie the timer to the buttons
    void start();
    void pause();
    void resume();
    void stop();
  private:
    double input_hours, input_minutes, input_seconds;
};

#endif //EXAM_TIME_H
