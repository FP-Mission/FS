#include <Components.hpp>
#include <Fw/Logger/Logger.hpp>
#include <Fw/Types/Assert.hpp>
#include <Fw/Types/MallocAllocator.hpp>
#include <Os/Log.hpp>
#include <Os/Task.hpp>

#if defined TGT_OS_TYPE_LINUX || TGT_OS_TYPE_DARWIN
#include <ctype.h>
#include <getopt.h>
#include <stdlib.h>
#endif

// List of context IDs
enum {
    DOWNLINK_PACKET_SIZE = 500,
    DOWNLINK_BUFFER_STORE_SIZE = 2500,
    DOWNLINK_BUFFER_QUEUE_SIZE = 5,
    UPLINK_BUFFER_STORE_SIZE = 3000,
    UPLINK_BUFFER_QUEUE_SIZE = 30
};

Os::Log osLogger;

// Registry
#if FW_OBJECT_REGISTRATION == 1
static Fw::SimpleObjRegistry simpleReg;
#endif

Fw::MallocAllocator seqMallocator;

// Component instance pointers
Svc::LinuxTimeImpl linuxTime(FW_OPTIONAL_NAME("LTIME"));

static NATIVE_INT_TYPE rgDivs[Svc::RateGroupDriverImpl::DIVIDER_SIZE] = {1, 2,
                                                                         4};
Svc::RateGroupDriverImpl rateGroupDrv(FW_OPTIONAL_NAME("RGDvr"), rgDivs,
                                      FW_NUM_ARRAY_ELEMENTS(rgDivs));

static NATIVE_UINT_TYPE rg1Context[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Svc::ActiveRateGroupImpl rateGroup1(FW_OPTIONAL_NAME("RG1"), rg1Context,
                                    FW_NUM_ARRAY_ELEMENTS(rg1Context));

static NATIVE_UINT_TYPE rg3Context[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Svc::ActiveRateGroupImpl rateGroup3(FW_OPTIONAL_NAME("RG3"), rg3Context,
                                    FW_NUM_ARRAY_ELEMENTS(rg3Context));

Svc::FatalHandlerComponentImpl fatalHandler(FW_OPTIONAL_NAME("fatalHandler"));
Svc::AssertFatalAdapterComponentImpl fatalAdapter(
    FW_OPTIONAL_NAME("fatalAdapter"));
Svc::CommandDispatcherImpl cmdDisp(FW_OPTIONAL_NAME("CMDDISP"));
Svc::ActiveLoggerImpl eventLogger(FW_OPTIONAL_NAME("ELOG"));
Svc::TlmChanImpl chanTlm(FW_OPTIONAL_NAME("TLM"));
Svc::HealthImpl health(FW_OPTIONAL_NAME("health"));
Svc::GroundInterfaceComponentImpl groundIf(FW_OPTIONAL_NAME("GNDIF"));

#if FW_ENABLE_TEXT_LOGGING
Svc::ConsoleTextLoggerImpl textLogger(FW_OPTIONAL_NAME("TLOG"));
#endif

Ref::PingReceiverComponentImpl pingRcvr(FW_OPTIONAL_NAME("PngRecv"));
Drv::BlockDriverImpl blockDrv(FW_OPTIONAL_NAME("BDRV"));

const char* getHealthName(Fw::ObjBase& comp) {
#if FW_OBJECT_NAMES == 1
    return comp.getObjName();
#else
    return "[no object name]"
#endif
}

bool constructApp(bool dump) {
#if FW_PORT_TRACING
    Fw::PortBase::setTrace(false);
#endif

    // Initialize rate group driver
    rateGroupDrv.init();

    // Initialize the rate groups
    rateGroup1.init(10, 0);

    rateGroup3.init(10, 2);

    // Initialize block driver
    blockDrv.init(10);

    // Send/Receive example hardware components

#if FW_ENABLE_TEXT_LOGGING
    textLogger.init();
#endif

    eventLogger.init(10, 0);

    linuxTime.init(0);

    chanTlm.init(10, 0);

    cmdDisp.init(20, 0);

    groundIf.init(0);

    fatalAdapter.init(0);
    fatalHandler.init(0);
    health.init(25, 0);
    pingRcvr.init(10);

    // Connect rate groups to rate group driver
    constructAppArchitecture();

    // dump topology if requested
    if (dump) {
#if FW_OBJECT_REGISTRATION == 1
        simpleReg.dump();
#endif
        return true;
    }

    /* Register commands */
    cmdDisp.regCommands();
    eventLogger.regCommands();
    health.regCommands();
    pingRcvr.regCommands();

    // Set health ping entries
    Svc::HealthImpl::PingEntry pingEntries[] = {
        {3, 5, getHealthName(rateGroup1)},   // 0
        {3, 5, getHealthName(rateGroup3)},   // 1
        {3, 5, getHealthName(cmdDisp)},      // 2
        {3, 5, getHealthName(eventLogger)},  // 3
        {3, 5, getHealthName(chanTlm)},      // 4
        {3, 5, getHealthName(pingRcvr)},     // 5
        {3, 5, getHealthName(blockDrv)},     // 6
    };

    // register ping table
    health.setPingEntries(pingEntries, FW_NUM_ARRAY_ELEMENTS(pingEntries),
                          0x123);


    // Active component startup
    // start rate groups
    rateGroup1.start(0, 120, 10 * 1024);
    rateGroup3.start(0, 118, 10 * 1024);
    // start driver
    blockDrv.start(0, 140, 10 * 1024);
    // start dispatcher
    cmdDisp.start(0, 101, 10 * 1024);
    // start telemetry
    eventLogger.start(0, 98, 10 * 1024);
    chanTlm.start(0, 97, 10 * 1024);

    pingRcvr.start(0, 100, 10 * 1024);
    
    return false;
}

void exitTasks(void) {
    rateGroup1.exit();
    rateGroup3.exit();
    blockDrv.exit();
    cmdDisp.exit();
    eventLogger.exit();
    chanTlm.exit();
    pingRcvr.exit();

    // Join the component threads with NULL pointers to free them
    (void)rateGroup1.ActiveComponentBase::join(NULL);
    (void)rateGroup3.ActiveComponentBase::join(NULL);
    (void)blockDrv.ActiveComponentBase::join(NULL);
    (void)cmdDisp.ActiveComponentBase::join(NULL);
    (void)eventLogger.ActiveComponentBase::join(NULL);
    (void)chanTlm.ActiveComponentBase::join(NULL);
    (void)pingRcvr.ActiveComponentBase::join(NULL);
}
