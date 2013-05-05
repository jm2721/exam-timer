#include "timer.h"
#include <cairomm/context.h>
#include <time.h>
#include <glibmm/main.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>

timer::timer() :
  //initializes the timer as stopped and not running
  started(false),
  running(false)
  
{
  //makes the program redraw every 100 milliseconds
  Glib::signal_timeout().connect(sigc::mem_fun(*this, &timer::on_timeout), 100);
  signal_draw().connect(sigc::mem_fun(*this, &timer::on_draw), false);
}

//sets up the initial input
void timer::input(bool start, bool paused, double hour, double min, double sec)
{
  this->paused = paused; 
  srand(time(NULL));
  hour_value = hour;
  min_value = min;
  sec_value = sec;
  if(start){
    running = true;
    started = true;
  }
  if(!start){
    running = false;
    started = false;
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
    cr->set_source_rgb(.4, 0, .6);
    cr->paint();	  
    cr->translate(width/2, height/2); 
    cr->set_source(clock_img, -clock_img->get_width()/2, -clock_img->get_height()/2);
    cr->paint(); 
    cr->set_source_rgb(0.6, 0, 0.4);
//    cr->move_to(width/2, height/2);  
    cr->set_line_width(10); 
 //   cr->translate(width/2, height/2); 
    cr->arc(0, 0, 180 , -1*(M_PI/2), (piSeconds * M_PI) - M_PI/2);
    cr->stroke();
     
    cr->set_source_rgb(0.4, .2, 0.4);  
    cr->arc(0, 0, 130, -1*(M_PI/2), piMinutes*M_PI - M_PI/2); 
    cr->stroke();
    cr->set_source_rgb(.3, .2, .5);
    cr->arc(0, 0, 80, -1*(M_PI/2) , piHours*M_PI - M_PI/2);
    cr->stroke();
 
    cr->set_source_rgb(1,1,1); 
    cr->translate(50, -220); 
    cr->set_font_size(20);  
 
    std::string hours;
    std::string minutes;
    std::string seconds;

    std::stringstream convert1, convert2, convert3;
    if(sec_value > 59.99){
      convert3 << sec_value - 1;
      seconds = convert3.str();
    } else {
      convert3 << sec_value;
      seconds = convert3.str();
    }
    if(min_value > 59.99){
      convert2 << min_value - 1; 
      minutes = convert2.str();
    } else {
      convert2 << min_value;
      minutes = convert2.str(); 
    } 
    
    convert1 << hour_value;
    hours = convert1.str();	 
 
    std::string countdown = "Time remaining: " + hours + ":" + minutes + ":" + seconds;
    
    cr->show_text(countdown);
    //adding stuff here

    if (min_value <= 0.01 and hour_value >= 0.01 and sec_value <= .01) {
      min_value = 60;
      hour_value = hour_value - 1;
    }

    if (sec_value <= 0.01 and min_value >= 0.01) {
      sec_value = 60;
      min_value = min_value - 1;
    }
    if (sec_value <= 0.01 and min_value <= 0.01 and hour_value <= 0.01) { 
      running = false;
    }

    sec_value = sec_value - 0.1;
  // if paused then you need to save the draw information
  } else if (paused and running) {
    cr->save();   
    cr->set_source_rgb(.4,0,.6);
    cr->paint();	    
    cr->translate(width/2, height/2);
    cr->set_source(clock_img, -clock_img->get_width()/2, -clock_img->get_height()/2);
    cr->paint(); 
    cr->set_source_rgb(.6,0,.4);
//    cr->move_to(width/2, height/2);  
    cr->set_line_width(10); 
 //   cr->translate(width/2, height/2); 
    cr->arc(0, 0, 180 , -1*(M_PI/2), (piSeconds * M_PI) - M_PI/2);
    cr->stroke();
     
    cr->set_source_rgb(.4,.2,.4);  
    cr->arc(0, 0, 130, -1*(M_PI/2), piMinutes*M_PI - M_PI/2); 
    cr->stroke();
    cr->set_source_rgb(.3,.2,.5);
    cr->arc(0, 0, 80, -1*(M_PI/2) , piHours*M_PI - M_PI/2);
    cr->stroke();
    
    cr->set_source_rgb(1,1,1); 
    cr->translate(75, -220); 
    cr->set_font_size(30);
    cr->show_text("Paused");
    
  } 
  else if(not running){
    cr->save();
    cr->set_source_rgb(.4,0,.6);
    cr->paint();	    
    cr->translate(width/2, height/2);
    cr->set_source(clock_img, -clock_img->get_width()/2, -clock_img->get_height()/2);
    cr->paint();
    if (started) {
      cr->set_source_rgb((double) rand()/RAND_MAX, (double) rand()/RAND_MAX, (double) rand()/RAND_MAX); 
      cr->set_font_size(100);   
      cr->translate(-250, 40);
      cr->show_text("TIME'S UP");
      
    }

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

double timer::get_hour_value() 
{
  return hour_value;
}

double timer::get_min_value()
{
  return min_value;
}

double timer::get_sec_value()
{
  return sec_value;
}
