#ifndef __LIST_COMPONENTS_HEADER__
#define __LIST_COMPONENTS_HEADER__
#include <Svc/ActiveRateGroup/ActiveRateGroupImpl.hpp>
#include <Svc/RateGroupDriver/RateGroupDriverImpl.hpp>

#include <Svc/CmdDispatcher/CommandDispatcherImpl.hpp>
#include <Svc/CmdSequencer/CmdSequencerImpl.hpp>
#include <Svc/PassiveConsoleTextLogger/ConsoleTextLoggerImpl.hpp>
#include <Svc/ActiveLogger/ActiveLoggerImpl.hpp>
#include <Svc/LinuxTime/LinuxTimeImpl.hpp>
#include <Svc/TlmChan/TlmChanImpl.hpp>
#include <Svc/PrmDb/PrmDbImpl.hpp>
#include <Fw/Obj/SimpleObjRegistry.hpp>
#include <Svc/FileUplink/FileUplink.hpp>
#include <Svc/FileDownlink/FileDownlink.hpp>
#include <Svc/FileManager/FileManager.hpp>
#include <Svc/BufferManager/BufferManager.hpp>
#include <Svc/Health/HealthComponentImpl.hpp>

#include <Ref/PingReceiver/PingReceiverComponentImpl.hpp>
#include <Svc/AssertFatalAdapter/AssertFatalAdapterComponentImpl.hpp>
#include <Svc/FatalHandler/FatalHandlerComponentImpl.hpp>
#include <Drv/BlockDriver/BlockDriverImpl.hpp>
#include <Drv/SocketIpDriver/SocketIpDriverComponentImpl.hpp>
#include <Svc/GroundInterface/GroundInterface.hpp>

#include <App/SenseHat/SenseHatComponentImpl.hpp>
#include <App/Thermometer/ThermometerComponentImpl.hpp>
#include <App/MotionTracking/MotionTrackingComponentImpl.hpp>

void constructAppArchitecture(void);
bool constructApp(bool dump, U32 port_number, char* hostname);
void exitTasks(void);


extern Svc::RateGroupDriverImpl rateGroupDriverComp;
extern Svc::ActiveRateGroupImpl rateGroup1Comp, rateGroup2Comp, rateGroup3Comp;
extern Svc::CmdSequencerComponentImpl cmdSeq;
extern Svc::GroundInterfaceComponentImpl groundIf;
extern Svc::ConsoleTextLoggerImpl textLogger;
extern Svc::ActiveLoggerImpl eventLogger;
extern Svc::LinuxTimeImpl linuxTime;
extern Svc::TlmChanImpl chanTlm;
extern Svc::CommandDispatcherImpl cmdDisp;
extern Svc::PrmDbImpl prmDb;
extern Svc::FileUplink fileUplink;
extern Svc::FileDownlink fileDownlink;
extern Svc::FileManager fileManager;
extern Svc::BufferManager fileUplinkBufferManager;
extern Svc::AssertFatalAdapterComponentImpl fatalAdapter;
extern Svc::FatalHandlerComponentImpl fatalHandler;
extern Svc::HealthImpl health;

extern Drv::BlockDriverImpl blockDrv;
extern Ref::PingReceiverComponentImpl pingRcvr;
extern Drv::SocketIpDriverComponentImpl socketIpDriver;

extern App::SenseHatComponentImpl senseHat;
extern App::ThermometerComponentImpl thermometer;
extern App::MotionTrackingComponentImpl motionTracking;

#endif
