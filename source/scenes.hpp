#include "renderd7.hpp"

class DBSel : public RenderD7::Scene
{
     public:
     DBSel(){}
     void Draw(void) const override;
     void Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch) override;
};
