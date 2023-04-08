#include "Ovls.hpp"
#include "nightlyreader.hpp"
#include "scenes.hpp"
#include <rd7.hpp>
#include <renderd7/log.hpp>

std::unique_ptr<RenderD7::StealConsole> st_stdout;

int main() {
  // st_stdout = std::make_unique<RenderD7::StealConsole>();
  rd7_do_splash = true;
  RenderD7::Init::Main("Dev-Helper");
  rd7_security->SafeInit(amInit, amExit);
  RenderD7::Msg::Display("DevHelper", "Initializing...", Top);

  RenderD7::Scene::Load(std::make_unique<DBSel>());
  while (RenderD7::MainLoop()) {
    if (d7_hDown & KEY_START)
      RenderD7::ExitApp();
    /// Push a Nonblock FrameBegin to Prevent crash...
    /// Fixed in RenderD7 0.9.4 but 0.9.4 isn't publc yet
    C3D_FrameBegin(2);
    RenderD7::FrameEnd();
  }
}
