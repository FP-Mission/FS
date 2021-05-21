#ifndef __LIST_COMPONENTS_HEADER__
#define __LIST_COMPONENTS_HEADER__


#include <Drv/BlockDriver/BlockDriverImpl.hpp>
#include <Fw/Obj/SimpleObjRegistry.hpp>
#include <Ref/PingReceiver/PingReceiverComponentImpl.hpp>
#include <Svc/ActiveLogger/ActiveLoggerImpl.hpp>
#include <Svc/ActiveRateGroup/ActiveRateGroupImpl.hpp>
#include <Svc/Health/HealthComponentImpl.hpp>
#include <Svc/LinuxTime/LinuxTimeImpl.hpp>
#include <Svc/PassiveConsoleTextLogger/ConsoleTextLoggerImpl.hpp>
#include <Svc/RateGroupDriver/RateGroupDriverImpl.hpp>

void constructAppArchitecture(void);
bool constructApp(bool dump);
void exitTasks(void);

extern Svc::RateGroupDriverImpl rateGroupDrv;
extern Svc::ActiveRateGroupImpl rateGroup1, rateGroup3;
extern Svc::ConsoleTextLoggerImpl textLogger;
extern Svc::ActiveLoggerImpl eventLogger;
extern Svc::LinuxTimeImpl linuxTime;
extern Svc::HealthImpl health;

extern Drv::BlockDriverImpl blockDrv;
extern Ref::PingReceiverComponentImpl pingRcvr;

#endif
