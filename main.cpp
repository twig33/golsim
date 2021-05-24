#include <gtkmm.h>

int main()
{
  auto app = Gtk::Application::create();
  auto builder = Gtk::Builder::create_from_file("golsim.glade");
  builder->set_application(app);
  Gtk::Window* pWindow = nullptr;
  builder->get_widget("mainWindow", pWindow);
  return app->run(*pWindow);
}