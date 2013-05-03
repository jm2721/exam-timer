#ifndef TIMER_H
#define TIMER_H
#include <stdio.h>
#include <gtkmm/drawingarea.h>
#include <cairomm/context.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/alignment.h>
#include <time.h>

class timer : public Gtk::DrawingArea
{
  public:
    timer();
    void input(bool start, bool paused, int hour ,int min, int sec);
    int get_hour_value();
    int get_min_value();
    int get_sec_value();
  protected:
    //gets the system time
    time_t start_time;
    time_t end_time;
    time_t remaining;
    //drawing function for the timer
    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    bool on_timeout();
 private:
    int hour_value, min_value, sec_value, paused_time, remaining_time;
    bool running, paused, stopped;
    void draw_text(const Cairo::RefPtr<Cairo::Context>& cr);
    Gtk::ProgressBar m_progressbar;
    Gtk::Alignment m_alignment;
    void draw_rectangle(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
};
#endif //TIMER_H
