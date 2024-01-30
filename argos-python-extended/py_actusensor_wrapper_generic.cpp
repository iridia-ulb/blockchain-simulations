#include "py_actusensor_wrapper_generic.h"
#include "py_wrapper.h"

using namespace argos;

/****************************************/
/****************************************/

CQTOpenGLUserFunctionsWrapper::CQTOpenGLUserFunctionsWrapper() {}

// Add bool fill, color, number of vertices inputs
// const boost::python::list c_position_list, const boost::python::list c_orientation_list, const Real f_radius
void CQTOpenGLUserFunctionsWrapper::DrawCircle(const boost::python::list c_position_list, 
                                               const boost::python::list c_orientation_list, 
                                               const Real f_radius, 
                                               const std::string str_color_name,
                                               const bool  b_fill) {
    m_pcCQTOpenGLUserFunctions->DrawCircle(
        CVector3(boost::python::extract<Real>(boost::python::object(c_position_list[0])), 
                 boost::python::extract<Real>(boost::python::object(c_position_list[1])), 
                 boost::python::extract<Real>(boost::python::object(c_position_list[2]))),
        CQuaternion(), // Implement orientation
        f_radius, 
        ActusensorsWrapper::CColorWrapper(str_color_name).m_cColor,
        b_fill);
}

void CQTOpenGLUserFunctionsWrapper::DrawPolygon(const boost::python::list c_position_list, 
                                                const boost::python::list c_orientation_list, 
                                                const boost::python::list vec_points_list, 
                                                const std::string str_color_name,
                                                const bool  b_fill) {
  
    std::vector<CVector2> vec_point_vector;
    boost::python::list vec_point;

    for (size_t i = 0; i < boost::python::len(vec_points_list); ++i) {

            vec_point = boost::python::extract<boost::python::list>(boost::python::object(vec_points_list[i]));

            vec_point_vector.push_back(CVector2(boost::python::extract<Real>(boost::python::object(vec_point[0])),
                                                boost::python::extract<Real>(boost::python::object(vec_point[1]))));
        }

    m_pcCQTOpenGLUserFunctions->DrawPolygon(
        CVector3(boost::python::extract<Real>(boost::python::object(c_position_list[0])), 
                 boost::python::extract<Real>(boost::python::object(c_position_list[1])), 
                 boost::python::extract<Real>(boost::python::object(c_position_list[2]))),
        CQuaternion(), // Implement orientation
        vec_point_vector, 
        ActusensorsWrapper::CColorWrapper(str_color_name).m_cColor,
        b_fill);
}

void CQTOpenGLUserFunctionsWrapper::DrawRay(const boost::python::list c_start,
                                            const boost::python::list c_end,
                                            const std::string str_color_name,
                                            const Real f_width) {
    CVector3 c_stt_vec;
    CVector3 c_end_vec;

    c_stt_vec = CVector3(boost::python::extract<Real>(boost::python::object(c_start[0])), 
                         boost::python::extract<Real>(boost::python::object(c_start[1])), 
                         boost::python::extract<Real>(boost::python::object(c_start[2])));

    c_end_vec = CVector3(boost::python::extract<Real>(boost::python::object(c_end[0])), 
                         boost::python::extract<Real>(boost::python::object(c_end[1])), 
                         boost::python::extract<Real>(boost::python::object(c_end[2])));

    m_pcCQTOpenGLUserFunctions->DrawRay(CRay3(c_stt_vec, c_end_vec), 
                                        ActusensorsWrapper::CColorWrapper(str_color_name).m_cColor,
                                        f_width);
}

void CQTOpenGLUserFunctionsWrapper::DrawBox(const boost::python::list c_position_list, 
                                            const boost::python::list c_orientation_list, 
                                            const boost::python::list c_size_list, 
                                            const std::string str_color_name) {
    m_pcCQTOpenGLUserFunctions->DrawBox(
        CVector3(boost::python::extract<Real>(boost::python::object(c_position_list[0])), 
                 boost::python::extract<Real>(boost::python::object(c_position_list[1])), 
                 boost::python::extract<Real>(boost::python::object(c_position_list[2]))),
        CQuaternion(), // Implement orientation
        CVector3(boost::python::extract<Real>(boost::python::object(c_size_list[0])), 
                 boost::python::extract<Real>(boost::python::object(c_size_list[1])), 
                 boost::python::extract<Real>(boost::python::object(c_size_list[2]))), 
        ActusensorsWrapper::CColorWrapper(str_color_name).m_cColor);
}

void CQTOpenGLUserFunctionsWrapper::DrawCylinder(const boost::python::list c_position_list, 
                                                 const boost::python::list c_orientation_list, 
                                                 const Real f_radius, 
                                                 const Real f_height,
                                                 const std::string str_color_name) {
    m_pcCQTOpenGLUserFunctions->DrawCylinder(
        CVector3(boost::python::extract<Real>(boost::python::object(c_position_list[0])), 
                 boost::python::extract<Real>(boost::python::object(c_position_list[1])), 
                 boost::python::extract<Real>(boost::python::object(c_position_list[2]))),
        CQuaternion(), // Implement orientation
        f_radius,
        f_height, 
        ActusensorsWrapper::CColorWrapper(str_color_name).m_cColor);
}


void CQTOpenGLUserFunctionsWrapper::DrawText(const boost::python::list c_position,
                                             const std::string str_text,
                                             const std::string str_color_name) {

    CVector3 c_pos_vec;
    c_pos_vec = CVector3(boost::python::extract<Real>(boost::python::object(c_position[0])), 
                         boost::python::extract<Real>(boost::python::object(c_position[1])), 
                         boost::python::extract<Real>(boost::python::object(c_position[2])));

}

void CQTOpenGLUserFunctionsWrapper::CloseWindow() {
  m_pcCQTOpenGLUserFunctions->GetMainWindow().close();

    // NOT WORKING; CORE DUMP
    // m_pcCQTOpenGLUserFunctions->DrawText(CVector3(0,0,1),
    //                                      "sdsd");
}

/****************************************/
/****************************************/

CWheelsWrapper::CWheelsWrapper() {}

void CWheelsWrapper::SetSpeed(const Real f_left_wheel_speed, const Real f_right_wheel_speed) {
    if (m_pcWheels == nullptr) {
        ActusensorsWrapper::Logprint(
            "Differential Steering Actuator not implemented or not stated in XML config.");
        return;
    }
    m_pcWheels->SetLinearVelocity(f_left_wheel_speed, f_right_wheel_speed);
}

/****************************************/
/****************************************/

CDifferentialSteeringSensorWrapper::CDifferentialSteeringSensorWrapper() {}

boost::python::list CDifferentialSteeringSensorWrapper::GetReading() const {
    if (m_pcDifferentialSteeringSensor == nullptr) {
        ActusensorsWrapper::Logprint(
            "Differential Steering Sensor not implemented or not stated in XML config.");
        return {};
    }
    // Probably there is an better way to convert SReadings to boost::python::list
    boost::python::list readings;
    readings.append((Real) m_pcDifferentialSteeringSensor->GetReading().CoveredDistanceLeftWheel);
    readings.append((Real) m_pcDifferentialSteeringSensor->GetReading().CoveredDistanceRightWheel);
    readings.append((Real) m_pcDifferentialSteeringSensor->GetReading().VelocityLeftWheel);
    readings.append((Real) m_pcDifferentialSteeringSensor->GetReading().VelocityRightWheel);
    readings.append((Real) m_pcDifferentialSteeringSensor->GetReading().WheelAxisLength);

    return readings;

}

boost::python::list CDifferentialSteeringSensorWrapper::GetDistances() const {
    if (m_pcDifferentialSteeringSensor == nullptr) {
        ActusensorsWrapper::Logprint(
            "Differential Steering Sensor not implemented or not stated in XML config.");
        return {};
    }
    // Probably there is an better way to convert SReadings to boost::python::list
    boost::python::list readings;
    readings.append((Real) m_pcDifferentialSteeringSensor->GetReading().CoveredDistanceLeftWheel);
    readings.append((Real) m_pcDifferentialSteeringSensor->GetReading().CoveredDistanceRightWheel);

    return readings;
}

/****************************************/
/****************************************/

CPositioningSensorWrapper::CPositioningSensorWrapper() {}

boost::python::list CPositioningSensorWrapper::GetPosition() const {
    if (m_pcPositioning == nullptr) {
        ActusensorsWrapper::Logprint("Positioning Sensor not implemented or not stated in XML config.");
        return {};
    }

    // Probably there is an better way to convert CVector3 to boost::python::list
    boost::python::list position;
    position.append((float) m_pcPositioning->GetReading().Position[0]);
    position.append((float) m_pcPositioning->GetReading().Position[1]);
    position.append((float) m_pcPositioning->GetReading().Position[2]);

    return position;
}

Real CPositioningSensorWrapper::GetOrientation() const {
    if (m_pcPositioning == nullptr) {
        ActusensorsWrapper::Logprint("Positioning Sensor not implemented or not stated in XML config.");
        return {};
    }

    // Currently only returns rotation along Z and ignores other axis
    CRadians cZAngle, cYAngle, cXAngle; 
    m_pcPositioning->GetReading().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);

    return cZAngle.GetValue();
}

/****************************************/
/****************************************/

COmnidirectionalCameraWrapper::COmnidirectionalCameraWrapper() {}

boost::python::list COmnidirectionalCameraWrapper::GetReadings() const {
    if (m_pcOmniCam == nullptr) {
        ActusensorsWrapper::Logprint(
            "Omnidirectional Camera Sensor not implemented or not stated in XML config.");
        return {};
    }
    return ActusensorsWrapper::ToPythonList(m_pcOmniCam->GetReadings().BlobList);
}
// Enable the camera.
void COmnidirectionalCameraWrapper::Enable() {
    if (m_pcOmniCam == nullptr) {
        ActusensorsWrapper::Logprint(
            "Omnidirectional Camera Sensor not implemented or not stated in XML config.");
        return;
    }
    m_pcOmniCam->Enable();
}
// Disable the camera.
void COmnidirectionalCameraWrapper::Disable() {
    if (m_pcOmniCam == nullptr) {
        ActusensorsWrapper::Logprint(
            "Omnidirectional Camera Sensor not implemented or not stated in XML config.");
        return;
    }
    m_pcOmniCam->Disable();
}
// Return the number of readings obtained so far, i.e. the number of control steps from which the
// recording started.
const int COmnidirectionalCameraWrapper::GetCounter() const {
    if (m_pcOmniCam == nullptr) {
        ActusensorsWrapper::Logprint(
            "Omnidirectional Camera Sensor not implemented or not stated in XML config.");
        return {};
    }
    return m_pcOmniCam->GetReadings().Counter;
}

/****************************************/
/****************************************/

CRangeAndBearingWrapper::CRangeAndBearingWrapper() {}

void CRangeAndBearingWrapper::ClearData() {
    if (m_pcRABA == nullptr) {
        ActusensorsWrapper::Logprint("RABA not implemented or not stated in XML config.");
        return;
    }
    m_pcRABA->ClearData();
}
// Set the i-th bit of the data table.
void CRangeAndBearingWrapper::SetData(const size_t un_idx, const UInt8 un_value) {
    if (m_pcRABA == nullptr) {
        ActusensorsWrapper::Logprint("RABA not implemented or not stated in XML config.");
        return;
    }
    m_pcRABA->SetData(un_idx, un_value);
}
// TODO: Set all bits at once
// Return the readings obtained at this control step.
// Each reading contains the range, the horizontal bearing, the vertical bearing and the data table.
// The data table is exposed as a c_byte_array.
boost::python::list CRangeAndBearingWrapper::GetReadings() const {
    if (m_pcRABS == nullptr) {
        ActusensorsWrapper::Logprint("RABA not implemented or not stated in XML config.");
        return {};
    }
    return ActusensorsWrapper::ToPythonList(m_pcRABS->GetReadings());
}

/****************************************/
/****************************************/

CLedsActuatorWrapper::CLedsActuatorWrapper() {}

// Set the color of a given led, given its name.
void CLedsActuatorWrapper::SetSingleColorString(const UInt8 un_led_id,
                                                const std::string str_color_name) {
    if (m_pcLeds == nullptr) {
        ActusensorsWrapper::Logprint("Leds not implemented or not stated in XML config.");
        return;
    }
    m_pcLeds->SetSingleColor(un_led_id, ActusensorsWrapper::CColorWrapper(str_color_name).m_cColor);
}
// Set the color of a given led, given its RGB values.
void CLedsActuatorWrapper::SetSingleColorRGB(const UInt8 un_led_id, const UInt8 un_red,
                                             const UInt8 un_green, const UInt8 un_blue) {
    if (m_pcLeds == nullptr) {
        ActusensorsWrapper::Logprint("Leds not implemented or not stated in XML config.");
        return;
    }
    m_pcLeds->SetSingleColor(un_led_id,
                             ActusensorsWrapper::CColorWrapper(un_red, un_green, un_blue).m_cColor);
}
// Set the color of every led, given its name.
void CLedsActuatorWrapper::SetAllColorsString(const std::string str_color_name) {
    if (m_pcLeds == nullptr) {
        ActusensorsWrapper::Logprint("Leds not implemented or not stated in XML config.");
        return;
    }
    m_pcLeds->SetAllColors(ActusensorsWrapper::CColorWrapper(str_color_name).m_cColor);
}
// Set the color of every led, given its RGB values.
void CLedsActuatorWrapper::SetAllColorsRGB(const UInt8 un_red, const UInt8 un_green,
                                           const UInt8 un_blue) {
    if (m_pcLeds == nullptr) {
        ActusensorsWrapper::Logprint("Leds not implemented or not stated in XML config.");
        return;
    }
    m_pcLeds->SetAllColors(ActusensorsWrapper::CColorWrapper(un_red, un_green, un_blue).m_cColor);
}
