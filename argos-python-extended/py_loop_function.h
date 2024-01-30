#ifndef PY_LOOP_FUNCTION_H
#define PY_LOOP_FUNCTION_H

#include <boost/make_shared.hpp>
#include <boost/python.hpp>

#include <argos3/plugins/robots/e-puck/simulator/epuck_entity.h>
#include <argos3/core/simulator/loop_functions.h>

#include <py_controller.h>
#include <py_qtuser_function.h>

using namespace argos;

class CPyLoopFunction : public CLoopFunctions {

 public:
  CPyLoopFunction();
  virtual ~CPyLoopFunction(){};
  
  virtual void Init(TConfigurationNode& t_node);

  virtual void Reset();

  virtual void Destroy ();

  virtual void PreStep();

  virtual void PostStep();

  virtual bool IsExperimentFinished();

  virtual CColor GetFloorColor();

  virtual void PostExperiment();

 private:
  
    boost::python::object m_loop_main;
    boost::python::object m_loop_namesp;
    boost::python::object m_loop_script;
    PyThreadState* m_loop_interpreter;
   
    boost::shared_ptr<ActusensorsWrapper> m_environment;
};

#endif
