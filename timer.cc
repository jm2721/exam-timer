#include "timer.h"
#include <cairomm/context.h>
#include <glibmm/main.h>
#include <string.h>
#include <iostream>

timer::timer() :
  //initializes the timer as stopped and not running
  stopped(true),
  running(false)
{
  //makes the program redraw every second (or 1000 milliseconds)
  Glib::signal_timeout().connect(sigc::mem_fun(*this, &timer::on_timeout), 1000);
  signal_draw().connect(sigc::mem_fun(*this, &timer::on_draw), false);
}

//sets up the initial input
void timer::input(bool start, bool paused, int hour, int min, int sec)
{
  this->paused = paused; 
  hour_value = hour;
  min_value = min;
  sec_value = sec;
  if(start){
    running = true;
  }
}

bool timer::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  //normalize seconds to be on a scale from 0 to 2 so it can change the angle
  double piSeconds = (60.0 - sec_value)/30; 
  double piMinutes = (60.0 - min_value)/30;
  double piHours = (24.0 - hour_value)/12; 
  
  Cairo::RefPtr<Cairo::ImageSurface> clock_img = Cairo::ImageSurface::create_from_png("clock.png");
 
  if(running and not paused){ 
    cr->save();   
    cr->set_source_rgb(.5, .5, 1.0);
    cr->paint();	  
    cr->translate(width/2, height/2); 
    cr->set_source(clock_img, -clock_img->get_width()/2, -clock_img->get_height()/2);
    cr->paint(); 
    cr->set_source_rgb(0.8, .2, 0.2);
//    cr->move_to(width/2, height/2);  
    cr->set_line_width(10); 
 //   cr->translate(width/2, height/2); 
    cr->arc(0, 0, 180 , -1*(M_PI/2), (piSeconds * M_PI) - M_PI/2);
    cr->stroke();
     
    cr->set_source_rgb(0.0, 1.0, 0.0);  
    cr->arc(0, 0, 130, -1*(M_PI/2), piMinutes*M_PI - M_PI/2); 
    cr->stroke();
    cr->set_source_rgb(0.0, 0.0, 1.0);
    cr->arc(0, 0, 80, -1*(M_PI/2) , piHours*M_PI - M_PI/2);
    cr->stroke();
    //adding stuff here

    if (min_value == 0 and hour_value != 0) {
      min_value = 60;
      hour_value--;
    }

    if (sec_value == 0 and min_value != 0) {
      sec_value = 60;
      min_value--;
    }

    if (sec_value == 0) {
      running = false;
    }

    sec_value--;

  // if paused then you need to save the draw information
  } else if (paused and running) {
    cr->save();   
    cr->set_source_rgb(.5, .5, 1.0);
    cr->paint();	    
    cr->translate(width/2, height/2);
    cr->set_source(clock_img, -clock_img->get_width()/2, -clock_img->get_height()/2);
    cr->paint(); 
    cr->set_source_rgb(0.8, .2, 0.2);
//    cr->move_to(width/2, height/2);  
    cr->set_line_width(10); 
 //   cr->translate(width/2, height/2); 
    cr->arc(0, 0, 180 , -1*(M_PI/2), (piSeconds * M_PI) - M_PI/2);
    cr->stroke();
     
    cr->set_source_rgb(0.0, 1.0, 0.0);  
    cr->arc(0, 0, 130, -1*(M_PI/2), piMinutes*M_PI - M_PI/2); 
    cr->stroke();
    cr->set_source_rgb(0.0, 0.0, 1.0);
    cr->arc(0, 0, 80, -1*(M_PI/2) , piHours*M_PI - M_PI/2);
    cr->stroke();
    
    cr->set_source_rgb(.5, 1.0, .5); 
    cr->translate(75, -220); 
    cr->set_font_size(30);
    cr->show_text("Paused");
    /*cr->save();
    cr->set_source_rgb(0.5, 0.5, 1.0);	  
    cr->set_font_size(30); 
    cr->move_to(width/2, height/2 - 25); 
    cr->show_text("Paused");
    cr->save();*/
  } 
  else if(!running && !paused){
    
  }
  return true;
}

bool timer::on_timeout()
{
  // force our program to redraw the entire clock.
  Glib::RefPtr<Gdk::Window> win = get_window();
  if (win) {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
    win->invalidate_rect(r, false);
  }
  return true;
}

int timer::get_hour_value() 
{
  return hour_value;
}

int timer::get_min_value()
{
  return min_value;
}

int timer::get_sec_value()
{
  return sec_value;
}
