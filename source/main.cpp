#include "Ovls.hpp"
#include "nightlyreader.hpp"
#include "scenes.hpp"
#include <rd7.hpp>
#include <renderd7/log.hpp>


Log flog;

int main() {
  // flog.Init("DevHelper");
  RenderD7::Init::Main("Dev-Helper");

  RenderD7::Scene::Load(std::make_unique<DBSel>());
  flog.Write("Loading Scene");
  while (RenderD7::MainLoop()) {
    if (d7_hDown & KEY_START)
      RenderD7::ExitApp();

    RenderD7::FrameEnd();
  }
  flog.Write("Call RD7::Exit::Main");
  RenderD7::Exit::Main();
}
