#include <gtkmm.h>
#include <cairomm/context.h>
#include <glibmm/main.h>
#include <iostream>

#include "gol_simulator.hpp"

const int kGameWidth = 1024;
const int kGameHeight = 768;
Gtk::DrawingArea* p_drawing_area = nullptr;
std::vector<std::vector<int>> game_state;

bool OnDraw(const Cairo::RefPtr<Cairo::Context>& cr) {
  Gtk::Allocation allocation = p_drawing_area->get_allocation();
  const int width = std::min(allocation.get_width(), (int)game_state[0].size());
  const int height = std::min(allocation.get_height(), (int)game_state.size());
  
  cr->set_antialias(Cairo::ANTIALIAS_NONE);

  cr->save();
  
  guint8 frame[height][width*3];
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int color;
      if (game_state[y][x] == 1) {
        color = 0xFF;
      }
      else {
        color = 0;
      }
      frame[y][x*3] = color;
      frame[y][x*3+1] = color;
      frame[y][x*3+2] = color;
    }
  }
  
  auto pixbuf = Gdk::Pixbuf::create_from_data(frame[0],
      Gdk::Colorspace::COLORSPACE_RGB,
      false,
      8,
      width,
      height,
      width*3);
  
  Gdk::Cairo::set_source_pixbuf(cr, pixbuf);
  cr->paint();
  
  return true;
}

bool OnTimeout() {
  game_state = NextState(game_state);
  
  auto win = p_drawing_area->get_window();
  if (win) {
    Gdk::Rectangle r(0, 0, p_drawing_area->get_allocation().get_width(), 
                     p_drawing_area->get_allocation().get_height());
    win->invalidate_rect(r, false);
  }
  return true;
}

int main() {
  auto app = Gtk::Application::create();
  
  auto builder = Gtk::Builder::create_from_file("golsim.glade");
  builder->set_application(app);
  
  Gtk::Window* p_window = nullptr;
  builder->get_widget("main_window", p_window);
  builder->get_widget("drawing_area", p_drawing_area);
  
  p_drawing_area->signal_draw().connect(sigc::ptr_fun(&OnDraw));
  p_drawing_area->set_size_request(kGameWidth, kGameHeight);
  
  Glib::signal_timeout().connect(sigc::ptr_fun(&OnTimeout), 500);
  
  game_state = RandomState(kGameWidth, kGameHeight);

  return app->run(*p_window);
}