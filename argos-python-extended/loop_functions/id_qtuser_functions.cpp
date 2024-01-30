#include <string>

#include "id_qtuser_functions.h"


/****************************************/
/****************************************/

CIDQTUserFunctions::CIDQTUserFunctions() {
   // RegisterUserFunction<CIDQTUserFunctions,CEPuckEntity>(&CIDQTUserFunctions::DrawInWorld);
}

/****************************************/
/****************************************/

void CIDQTUserFunctions::DrawInWorld() {
   /* The position of the text is expressed wrt the reference point of the footbot
    * For a foot-bot, the reference point is the center of its base.
    * See also the description in
    * $ argos3 -q foot-bot
    */

   //TODO: specify Quaternion
   //DrawCircle(CVector3(0.0, 0.0, 0.0),
   //   CQuaternion(),
   //   0.1);

   // DrawText(CVector3(0.0, 0.0, 0.12),   // position
   //          std::to_string(stoi(c_entity.GetId().substr(2)) + 1),
   //          CColor::RED); // text

   DrawCircle(
   CVector3(0.0f, 0.0f, 0.01f), 
   CQuaternion(),
   0.4,
   CColor::RED);
}




/****************************************/
/****************************************/

REGISTER_QTOPENGL_USER_FUNCTIONS(CIDQTUserFunctions, "id_qtuser_functions")