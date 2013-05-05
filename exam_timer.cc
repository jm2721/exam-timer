#include "exam_timer.h"
#include "timer.h" 
#include <iostream>

exam_timer::exam_timer() : 
  //creates the boxes for the window
  m_box1(Gtk::ORIENTATION_VERTICAL, 5), m_hbox(Gtk::ORIENTATION_HORIZONTAL, 5),
  m_spinButtonBox(Gtk::ORIENTATION_HORIZONTAL, 5),
  m_labels_box(Gtk::ORIENTATION_HORIZONTAL, 5),
  m_time(Gtk::ORIENTATION_HORIZONTAL, 5),

  //sets up the four buttons for start, pause, resume, stop
  m_alignment(0.5, 0.5, 0, 0), 
  m_start_button("START"),
  m_pause_button("PAUSE"),
  m_resume_button("RESUME"),
  m_stop_button("STOP"), //Adjustment widget parameters: (float value, float lower bound, float upper bound, float step_increment, float page_increment, float page_size

  //sets up the three spinbuttons for hours, minutes, seconds
  m_label_hours("Hours: "),
  m_label_minutes("Minutes: "),
  m_label_seconds("Seconds: "),
  m_label_explanation("Innermost ring = hours. Middle ring = minutes. Outermost ring = seconds. Time's up when all is full."),

  //creates the range of the spinbuttons
  m_adjustment_hours( Gtk::Adjustment::create(0.0, 0.0, 24.0, 1.0, 5.0, 0.0)),
  m_adjustment_minutes( Gtk::Adjustment::create(0.0, 0.0, 59.0, 1.0, 5.0, 0.0)),
  m_adjustment_seconds( Gtk::Adjustment::create(0.0, 0.0, 59.0, 1.0, 5.0, 0.0)),

  //creates the spinbuttons
  m_spinbutton_hours(m_adjustment_hours),
  m_spinbutton_minutes(m_adjustment_minutes),
  m_spinbutton_seconds(m_adjustment_seconds),

  //initializes the hour, minute, second spinbuttons to 0
  input_hours(0),
  input_minutes(0),
  input_seconds(0)
{

  //adds all of the boxes/widgets to the window
  set_title("Exam Timer");
  m_box1.set_border_width(10);
  add(m_box1);
  m_box1.pack_start(m_label_explanation);
  m_label_explanation.show();
 
  m_box1.pack_start(m_hbox); 
  m_hbox.show(); 
  
  m_box1.pack_start(m_labels_box);
  m_labels_box.show();  
  m_labels_box.pack_start(m_label_hours);
  m_label_hours.show();
  m_labels_box.pack_start(m_label_minutes);
  m_label_minutes.show();
  m_labels_box.pack_start(m_label_seconds); 
  m_label_seconds.show(); m_box1.pack_start(m_spinButtonBox);

  m_spinbutton_hours.set_wrap();
  m_spinButtonBox.pack_start(m_spinbutton_hours);
  m_spinbutton_hours.show(); 
  
  m_spinbutton_minutes.set_wrap();  
  m_spinButtonBox.pack_start(m_spinbutton_minutes);
  m_spinbutton_minutes.show();
    
  m_spinbutton_seconds.set_wrap(); 
  m_spinButtonBox.pack_start(m_spinbutton_seconds); 
  m_spinbutton_seconds.show();

  m_hbox.pack_start(m_start_button);
  m_start_button.show();
  m_start_button.signal_clicked().connect(sigc::mem_fun(*this, &exam_timer::start) );

  
  m_hbox.pack_start(m_pause_button);
  m_pause_button.show();
  m_pause_button.signal_clicked().connect(sigc::mem_fun(*this, &exam_timer::pause) ); 
  m_pause_button.set_sensitive(false);

  m_hbox.pack_start(m_resume_button);
  m_resume_button.show();
  m_resume_button.signal_clicked().connect(sigc::mem_fun(*this, &exam_timer::resume) );
  m_resume_button.set_sensitive(false);

  m_hbox.pack_start(m_stop_button);
  m_stop_button.show();
  m_stop_button.signal_clicked().connect(sigc::mem_fun(*this, &exam_timer::stop) );  
  m_stop_button.set_sensitive(false);  
  m_spinButtonBox.show();
 
  timerArea.set_size_request(500, 500); 
  
  m_box1.pack_start(timerArea);
  timerArea.show();
  m_box1.show();

}

void exam_timer::start()
{
  //gets the input from the spinbuttons and starts the timer
  input_hours = m_spinbutton_hours.get_value_as_int();
  input_minutes = m_spinbutton_minutes.get_value_as_int();
  input_seconds = m_spinbutton_seconds.get_value_as_int();
  timerArea.input(true, false, input_hours, input_minutes, input_seconds);

//  m_start_button.set_sensitive(false);
  m_pause_button.set_sensitive(true);  
  m_stop_button.set_sensitive(true);
}

void exam_timer::pause()
{
  timerArea.input(false, true, timerArea.get_hour_value(), timerArea.get_min_value(), timerArea.get_sec_value());
  m_resume_button.set_sensitive(false);     
  m_stop_button.set_sensitive(true); 
  m_resume_button.set_sensitive(true);
}

void exam_timer::resume()
{
  timerArea.input(true, false, timerArea.get_hour_value(), timerArea.get_min_value(), timerArea.get_sec_value());
  m_resume_button.set_sensitive(false);  
}

void exam_timer::stop()
{
  //sets everything back to 0
  timerArea.input(false, false, 0.0, 0.0, 0.0);
  m_start_button.set_sensitive(true);
  m_pause_button.set_sensitive(false); 
  m_resume_button.set_sensitive(false);

}
