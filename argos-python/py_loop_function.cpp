#include "py_loop_function.h"

using namespace argos;
using namespace boost::python;

#define INIT_MODULE_LOOP_FUNCTION PyInit_libpy_loop_function_interface
extern "C" PyObject* INIT_MODULE_LOOP_FUNCTION();

// TODO: I had to add these lines and the line PyImport_AppendInittab("libpy_controller_interface", INIT_MODULE_CONTROLLER)
// in this file, otherwise I god an error that libpy_controller_interface is not a built-in module
#define INIT_MODULE_CONTROLLER PyInit_libpy_controller_interface
extern "C" PyObject* INIT_MODULE_CONTROLLER();

// TODO: I had to add these lines and the line PyImport_AppendInittab("libpy_qtuser_function_interface", INIT_MODULE_QTUSER_FUNCTION)
// in this file, otherwise I god an error that libpy_qtuser_function_interface is not a built-in module
#define INIT_MODULE_QTUSER_FUNCTION PyInit_libpy_qtuser_function_interface
extern "C" PyObject* INIT_MODULE_QTUSER_FUNCTION();

BOOST_PYTHON_MODULE(libpy_loop_function_interface) {

}

CPyLoopFunction::CPyLoopFunction() {
  // init python

  // TODO: Remove from loop function and only call in controller
  // PyImport_AppendInittab("libpy_qtuser_function_interface", INIT_MODULE_QTUSER_FUNCTION); 
  PyImport_AppendInittab("libpy_controller_interface", INIT_MODULE_CONTROLLER); 
  // TODO: Remove from loop function and only call in controller

  PyImport_AppendInittab("libpy_loop_function_interface", INIT_MODULE_LOOP_FUNCTION);
  if (!Py_IsInitialized()) {
    Py_Initialize();
  }
  m_loop_interpreter = Py_NewInterpreter();
    // init main module and namespace
  m_loop_main = import("__main__");
  m_loop_namesp = m_loop_main.attr("__dict__");
}


void CPyLoopFunction::Init(TConfigurationNode& t_node) {

  TConfigurationNode& tParams = GetNode(t_node, "params");
  
  /* Load script */
  std::string strScriptFileName;
  GetNodeAttributeOrDefault(tParams, "script", strScriptFileName, strScriptFileName);
  if (strScriptFileName == "") {
    THROW_ARGOSEXCEPTION("Loop function: Error loading python script \"" << strScriptFileName << "\""
      << std::endl);
  }
  // exec user script
  try {
    m_loop_script = exec_file(strScriptFileName.c_str(), m_loop_namesp, m_loop_namesp);

    std::cout << "Loop function: strScript:" << strScriptFileName << std::endl;
  } catch (error_already_set) {
    PyErr_Print();
  }


  // TODO: Iterate over nodes / params / parameters  and make them
  // available in Python
  // int numByzantine;
  // GetNodeAttributeOrDefault(tParams, "num_byzantine", numByzantine, 0);
  // m_loop_namesp["num_byzantine"]  = numByzantine;
  

  // Iterate over all robots and add them to a boost list
  boost::python::list allRobots;    
  CSpace::TMapPerType& m_cEpuck = GetSpace().GetEntitiesByType("epuck");
  for(CSpace::TMapPerType::iterator it = m_cEpuck.begin(); it != m_cEpuck.end(); ++it)
  {
      /* Get handle to e-puck entity and controller */
    CEPuckEntity& cEpuck = *any_cast<CEPuckEntity*>(it->second);

    CPyController& cController =  dynamic_cast<CPyController&>(cEpuck.GetControllableEntity().GetController());

    allRobots.append(cController.getActusensors());
    m_environment = boost::make_shared<ActusensorsWrapper>();

  }

  m_loop_namesp["allrobots"]  = allRobots;
  m_loop_namesp["environment"]  = m_environment;
  //m_loop_namesp["params"]  = tParams;
  
  try {
    // Import the wrapper's lib
    PyRun_SimpleString("import libpy_loop_function_interface as lib");
    object lib = import("libpy_loop_function_interface");
    

    // Launch Python init function
    object init_f = m_loop_main.attr("init");
    init_f();
  } catch (error_already_set) {
    PyErr_Print();
  }

}

void CPyLoopFunction::Reset() {
  // launch python reset function
  try {
    object reset_f = m_loop_main.attr("reset");
    reset_f();
  } catch (error_already_set) {
    PyErr_Print();
  }
}

void CPyLoopFunction::Destroy() {
  
  // Launch Python destroy function
  try {
    object destroy_f = m_loop_main.attr("destroy");
    destroy_f();
  } catch (error_already_set) {
    PyErr_Print();
  }
}

void CPyLoopFunction::PreStep() {

  // Launch Python pre_step function
  try {
    object pre_step_f = m_loop_main.attr("pre_step");
    pre_step_f();
  } catch (error_already_set) {
    PyErr_Print();
  }
}

void CPyLoopFunction::PostStep() {
  // Launch Python post_step function
  try {
    object post_step_f = m_loop_main.attr("post_step");
    post_step_f();
  } catch (error_already_set) {
    PyErr_Print();
  }
}

bool CPyLoopFunction::IsExperimentFinished() {

// Launch Python is_experiment_finished function
  try {
    object is_experiment_finished_f = m_loop_main.attr("is_experiment_finished");
    return is_experiment_finished_f();
  } catch (error_already_set) {
    PyErr_Print();
    return true;
  }

}

CColor CPyLoopFunction::GetFloorColor() {

// Launch Python is_experiment_finished function
  try {
    object get_floor_color_f = m_loop_main.attr("get_floor_color");

    std::cout << "Testing GetFloorColor" << std::endl;
    return CColor::WHITE;
  } catch (error_already_set) {
    PyErr_Print();
    return CColor::WHITE;
  }

}

void CPyLoopFunction::PostExperiment() {
  // Launch Python post_experiment function
  try {
    object post_experiment_f = m_loop_main.attr("post_experiment");
    post_experiment_f();
  } catch (error_already_set) {
    PyErr_Print();
  }
}


REGISTER_LOOP_FUNCTIONS(CPyLoopFunction, "py_loop_function")
