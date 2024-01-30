#include "py_qtuser_function.h"
#include <string>

using namespace argos;
using namespace boost::python;

#define INIT_MODULE_QTUSER_FUNCTION PyInit_libpy_qtuser_function_interface
extern "C" PyObject* INIT_MODULE_QTUSER_FUNCTION();

BOOST_PYTHON_MODULE(libpy_qtuser_function_interface) {

  // // Export "LoopFunctionsWrapper" that contains loop functions
  //   class_<CPyQTUserFunction, boost::shared_ptr<CPyQTUserFunction>, boost::noncopyable>("environment", no_init)
  //     .def("set_resources", &CPyQTUserFunction::set_resources);   

}


CPyQTUserFunction::CPyQTUserFunction() {
    // init python
  PyImport_AppendInittab("libpy_qtuser_function_interface", INIT_MODULE_QTUSER_FUNCTION);
  if (!Py_IsInitialized()) {
    Py_Initialize();
  }
  m_qtuser_interpreter = Py_NewInterpreter();
    // init main module and namespace
  m_qtuser_main = import("__main__");
  m_qtuser_namesp = m_qtuser_main.attr("__dict__");

  // This is just to draw the ID of the robot in the robot reference frame
  RegisterUserFunction<CPyQTUserFunction,CEPuckEntity>(&CPyQTUserFunction::Draw);
}

void CPyQTUserFunction::Init(TConfigurationNode& t_node) {

  m_environment = boost::make_shared<ActusensorsWrapper>();

  // TConfigurationNode& tParams = GetNode(t_node, "params");
    
  /* Load script */
  std::string strScriptFileName;
  // GetNodeAttributeOrDefault(tParams, "script", strScriptFileName, strScriptFileName);
  // if (strScriptFileName == "") {
  //   THROW_ARGOSEXCEPTION("QTUSER function: Error loading python script \"" << strScriptFileName << "\""
  //     << std::endl);
  // }
  strScriptFileName = "/home/ubuntu/geth-argos-docker-inside/FastFloor/loop_functions/qtuser_function.py";
  // exec user script
  try {
    m_qtuser_script = exec_file(strScriptFileName.c_str(), m_qtuser_namesp, m_qtuser_namesp);

    std::cout << "QTUSER function: strScript:" << strScriptFileName << std::endl;
  } catch (error_already_set) {
    PyErr_Print();
  }

  try {
    // Import the wrapper's lib
    // PyRun_SimpleString("import libpy_qtuser_function_interface as lib");
    // object lib = import("libpy_qtuser_function_interface");

    m_qtuser_namesp["environment"] = m_environment;

    // Launch Python init function
    object init_f = m_qtuser_main.attr("init");
    init_f();
  } catch (error_already_set) {
    PyErr_Print();
  }

}

void CPyQTUserFunction::Destroy() {
  
  // Launch Python destroy function
  try {
    object destroy_f = m_qtuser_main.attr("destroy");
    destroy_f();
  } catch (error_already_set) {
    PyErr_Print();
  }
}


void CPyQTUserFunction::DrawInWorld() {
  // launch python reset function
  try {
    object draw_in_world_f = m_qtuser_main.attr("DrawInWorld");
    draw_in_world_f();

    // object color_f = m_qtuser_main.attr("color");
    // std::cout << color_f << std::endl;
//
  } catch (error_already_set) {
    PyErr_Print();
  }
}


// This is just to draw the ID of the robot in the robot reference frame
void CPyQTUserFunction::Draw(CEPuckEntity& c_entity) {
   /* The position of the text is expressed wrt the reference point of the epuck
    * For a epuck, the reference point is the center of its base.
    * See also the description in
    * $ argos3 -q epuck
    */

   DrawText(CVector3(0.0, 0.0, 0.13),   // position
            std::to_string(stoi(c_entity.GetId().substr(2)) + 1),
            CColor::BLUE); // text

}


REGISTER_QTOPENGL_USER_FUNCTIONS(CPyQTUserFunction, "py_qtuser_function")
