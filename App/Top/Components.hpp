#ifndef __LIST_COMPONENTS_HEADER__
#define __LIST_COMPONENTS_HEADER__

#include <App/Eps/EpsComponentImpl.hpp>
#include <App/FlexTrak/FlexTrakComponentImpl.hpp>
#include <App/Gps/GpsComponentImpl.hpp>
#include <App/PiCamera/PiCameraComponentImpl.hpp>
#include <App/Predictor/PredictorComponentImpl.hpp>
#include <App/RockBlock/RockBlockComponentImpl.hpp>
#include <App/TemperatureProbes/TemperatureProbesComponentImpl.hpp>
#include <Drv/BlockDriver/BlockDriverImpl.hpp>
#include <Drv/SocketIpDriver/SocketIpDriverComponentImpl.hpp>
#include <Drv/LinuxSerialDriver/LinuxSerialDriverComponentImpl.hpp>
#include <Fw/Obj/SimpleObjRegistry.hpp>
#include <Ref/PingReceiver/PingReceiverComponentImpl.hpp>
#include <Svc/ActiveLogger/ActiveLoggerImpl.hpp>
#include <Svc/ActiveRateGroup/ActiveRateGroupImpl.hpp>
#include <Svc/AssertFatalAdapter/AssertFatalAdapterComponentImpl.hpp>
#include <Svc/BufferManager/BufferManager.hpp>
#include <Svc/CmdDispatcher/CommandDispatcherImpl.hpp>
#include <Svc/CmdSequencer/CmdSequencerImpl.hpp>
#include <Svc/FatalHandler/FatalHandlerComponentImpl.hpp>
#include <Svc/GroundInterface/GroundInterface.hpp>
#include <Svc/Health/HealthComponentImpl.hpp>
#include <Svc/LinuxTime/LinuxTimeImpl.hpp>
#include <Svc/PassiveConsoleTextLogger/ConsoleTextLoggerImpl.hpp>
#include <Svc/PrmDb/PrmDbImpl.hpp>
#include <Svc/RateGroupDriver/RateGroupDriverImpl.hpp>
#include <Svc/TlmChan/TlmChanImpl.hpp>

#include <App/SenseHat/SenseHatComponentImpl.hpp>
#include <App/Thermometer/ThermometerComponentImpl.hpp>
#include <App/MotionTracking/MotionTrackingComponentImpl.hpp>
#include <App/Barometer/BarometerComponentImpl.hpp>
#include <App/PiCamera/PiCameraComponentImpl.hpp>

void constructAppArchitecture(void);
bool constructApp(bool dump, U32 port_number, char* hostname);
void exitTasks(void);

extern Svc::RateGroupDriverImpl rateGroupDrv;
extern Svc::ActiveRateGroupImpl rateGroup1, rateGroup2, rateGroup3;
extern Svc::CmdSequencerComponentImpl cmdSeq;
extern Svc::GroundInterfaceComponentImpl groundIf;
extern Svc::ConsoleTextLoggerImpl textLogger;
extern Svc::ActiveLoggerImpl eventLogger;
extern Svc::LinuxTimeImpl linuxTime;
extern Svc::TlmChanImpl chanTlm;
extern Svc::CommandDispatcherImpl cmdDisp;
extern Svc::PrmDbImpl prmDb;
extern Svc::AssertFatalAdapterComponentImpl fatalAdapter;
extern Svc::FatalHandlerComponentImpl fatalHandler;
extern Svc::HealthImpl health;

extern Drv::BlockDriverImpl blockDrv;
extern Ref::PingReceiverComponentImpl pingRcvr;
extern Drv::SocketIpDriverComponentImpl socketIpDriver;
extern Drv::LinuxSerialDriverComponentImpl serialDriver1;

extern App::EpsComponentImpl eps;
extern App::FlexTrakComponentImpl flexTrak;
extern App::GpsComponentImpl gps;
extern App::PiCameraComponentImpl piCamera;
extern App::PredictorComponentImpl predictor;
extern App::RockBlockComponentImpl rockBlock;
extern App::TemperatureProbesComponentImpl temperatureProbes;

extern App::SenseHatComponentImpl senseHat;
extern App::ThermometerComponentImpl thermometer;
extern App::MotionTrackingComponentImpl motionTracking;
extern App::BarometerComponentImpl barometer;
extern App::PiCameraComponentImpl picamera;

#endif
