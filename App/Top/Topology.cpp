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

const char SHTC3= 0x70;

// Registry
#if FW_OBJECT_REGISTRATION == 1
static Fw::SimpleObjRegistry simpleReg;
#endif

Fw::MallocAllocator seqMallocator;

// Component instance pointers
Svc::LinuxTimeImpl linuxTime(FW_OPTIONAL_NAME("LTIME"));

static NATIVE_INT_TYPE rgDivs[Svc::RateGroupDriverImpl::DIVIDER_SIZE] = {1, 2,
                                                                         4, 10};
Svc::RateGroupDriverImpl rateGroupDrv(FW_OPTIONAL_NAME("RGDvr"), rgDivs,
                                      FW_NUM_ARRAY_ELEMENTS(rgDivs));

static NATIVE_UINT_TYPE rg1Context[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Svc::ActiveRateGroupImpl rateGroup1(FW_OPTIONAL_NAME("RG1"), rg1Context,
                                    FW_NUM_ARRAY_ELEMENTS(rg1Context));

static NATIVE_UINT_TYPE rg2Context[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Svc::ActiveRateGroupImpl rateGroup2(FW_OPTIONAL_NAME("RG2"), rg2Context,
                                    FW_NUM_ARRAY_ELEMENTS(rg2Context));

static NATIVE_UINT_TYPE rg3Context[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Svc::ActiveRateGroupImpl rateGroup3(FW_OPTIONAL_NAME("RG3"), rg3Context,
                                    FW_NUM_ARRAY_ELEMENTS(rg3Context));

static NATIVE_UINT_TYPE rg4Context[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
Svc::ActiveRateGroupImpl rateGroup4(FW_OPTIONAL_NAME("RG3"), rg4Context,
                                    FW_NUM_ARRAY_ELEMENTS(rg4Context));

Svc::FatalHandlerComponentImpl fatalHandler(FW_OPTIONAL_NAME("fatalHandler"));
Svc::AssertFatalAdapterComponentImpl fatalAdapter(
    FW_OPTIONAL_NAME("fatalAdapter"));
Svc::CommandDispatcherImpl cmdDisp(FW_OPTIONAL_NAME("CMDDISP"));
Svc::CmdSequencerComponentImpl cmdSeq(FW_OPTIONAL_NAME("CMDSEQ"));
Svc::ActiveLoggerImpl eventLogger(FW_OPTIONAL_NAME("ELOG"));
Svc::TlmChanImpl tlmChan(FW_OPTIONAL_NAME("TLM"));
Svc::HealthImpl health(FW_OPTIONAL_NAME("health"));
Svc::PrmDbImpl prmDb(FW_OPTIONAL_NAME("PRM"), "PrmDb.dat");
Svc::GroundInterfaceComponentImpl groundIf(FW_OPTIONAL_NAME("GNDIF"));

#if FW_ENABLE_TEXT_LOGGING
Svc::ConsoleTextLoggerImpl textLogger(FW_OPTIONAL_NAME("TLOG"));
#endif

Ref::PingReceiverComponentImpl pingRcvr(FW_OPTIONAL_NAME("PngRecv"));
Drv::BlockDriverImpl blockDrv(FW_OPTIONAL_NAME("BDRV"));
Drv::SocketIpDriverComponentImpl socketIpDriver(
    FW_OPTIONAL_NAME("SocketIpDriver"));
Drv::LinuxSerialDriverComponentImpl serialDriver1(
    FW_OPTIONAL_NAME("serialDriver1"));

App::EpsComponentImpl eps(FW_OPTIONAL_NAME("Eps"));
App::FlexTrakComponentImpl flexTrak(FW_OPTIONAL_NAME("FlexTrak"));
App::GpsComponentImpl gps(FW_OPTIONAL_NAME("Gps"));
App::PiCameraComponentImpl piCamera(FW_OPTIONAL_NAME("PiCamera"));
App::PredictorComponentImpl predictor(FW_OPTIONAL_NAME("Predictor"));
App::RockBlockComponentImpl rockBlock(FW_OPTIONAL_NAME("RockBlock"));
App::TemperatureProbesComponentImpl temperatureProbes(
    FW_OPTIONAL_NAME("TemperatureProbes"));

App::SenseHatComponentImpl senseHat(FW_OPTIONAL_NAME("senseHat"));

App::ThermometerComponentImpl thermometer(FW_OPTIONAL_NAME("thermometer"));

App::MotionTrackingComponentImpl motionTracking(FW_OPTIONAL_NAME("motionTracking"));

App::BarometerComponentImpl barometer(FW_OPTIONAL_NAME("barometer"));



const char* getHealthName(Fw::ObjBase& comp) {
#if FW_OBJECT_NAMES == 1
    return comp.getObjName();
#else
    return "[no object name]"
#endif
}

bool constructApp(bool dump, U32 port_number, char* hostname) {
    bool flextrak_connected = false;
#if FW_PORT_TRACING
    Fw::PortBase::setTrace(false);
#endif

    // Initialize rate group driver
    rateGroupDrv.init();

    // Initialize the rate groups
    rateGroup1.init(10, 0);

    rateGroup2.init(10, 1);

    rateGroup3.init(10, 2);

    rateGroup4.init(10, 3);

    // Initialize block driver
    blockDrv.init(10);

    // Send/Receive example hardware components

#if FW_ENABLE_TEXT_LOGGING
    textLogger.init();
#endif

    eventLogger.init(10, 0);

    linuxTime.init(0);

    tlmChan.init(10, 0);

    cmdDisp.init(20, 0);

    cmdSeq.init(10, 0);
    cmdSeq.allocateBuffer(0, seqMallocator, 5 * 1024);

    prmDb.init(10, 0);

    groundIf.init(0);
    socketIpDriver.init(0);
    serialDriver1.init(0);

    fatalAdapter.init(0);
    fatalHandler.init(0);
    health.init(25, 0);
    pingRcvr.init(10);

    eps.init(10, 0);
    flexTrak.init(10, 0);
    gps.init(0);
    piCamera.init(10, 0);
    predictor.init(10, 0);
    rockBlock.init(10, 0);
    temperatureProbes.init(10, 0);
    senseHat.init(30, 0);
    thermometer.init(30, 0);
    motionTracking.init(30, 0);
    barometer.init(30, 0);

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
    tlmChan.regCommands();
    cmdSeq.regCommands();
    cmdDisp.regCommands();
    eventLogger.regCommands();
    prmDb.regCommands();
    health.regCommands();
    pingRcvr.regCommands();
    senseHat.regCommands();

    eps.regCommands();
    flexTrak.regCommands();
    gps.regCommands();
    piCamera.regCommands();
    predictor.regCommands();
    // rockBlock.regCommands();
    temperatureProbes.regCommands();

    // read parameters
    // prmDb.readParamFile();

    // Set health ping entries
    Svc::HealthImpl::PingEntry pingEntries[] = {
        {3, 5, getHealthName(rateGroup1)},      // 0
        {3, 5, getHealthName(rateGroup2)},      // 1
        {3, 5, getHealthName(rateGroup3)},      // 2
        {3, 5, getHealthName(cmdDisp)},         // 3
        {3, 5, getHealthName(eventLogger)},     // 4
        {3, 5, getHealthName(cmdSeq)},          // 5
        {3, 5, getHealthName(chanTlm)},         // 6
        {3, 5, getHealthName(prmDb)},           // 7
        {3, 5, getHealthName(pingRcvr)},        // 8
        {3, 5, getHealthName(blockDrv)},        // 9
        {3, 5, getHealthName(flexTrak)},        // 10
        {3, 5, getHealthName(piCamera)},        // 11
        {3, 5, getHealthName(rockBlock)},       // 12
        {3, 5, getHealthName(senseHat)},        // 13
        {3, 5, getHealthName(thermometer)},     // 14
        {3, 5, getHealthName(motionTracking)},  // 15
        {3, 5, getHealthName(barometer)},       // 16
        {3, 5, getHealthName(rateGroup4)},      // 17
    };

    // register ping table
    health.setPingEntries(pingEntries, FW_NUM_ARRAY_ELEMENTS(pingEntries),
                          0x123);

    if (!serialDriver1.open("/dev/ttyAMA0",
                   Drv::LinuxSerialDriverComponentImpl::BAUD_38400,
                   Drv::LinuxSerialDriverComponentImpl::NO_FLOW, 
                   Drv::LinuxSerialDriverComponentImpl::PARITY_NONE,
                   true))
    {
        Fw::Logger::logMsg("[ERROR] Failed to open FlexTrak UART\n");
    } else {
        Fw::Logger::logMsg("[INFO] Opened FlexTrak UART\n");
        flextrak_connected = true;
    }

    // Active component startup
    // start rate groups
    rateGroup1.start(0, 120, 10 * 1024);
    rateGroup2.start(0, 119, 10 * 1024);
    rateGroup3.start(0, 118, 10 * 1024);
    rateGroup4.start(0, 118, 10 * 1024);
    // start driver
    blockDrv.start(0, 140, 10 * 1024);
    // start dispatcher
    cmdDisp.start(0, 101, 10 * 1024);
    // start sequencer
    cmdSeq.start(0, 100, 10 * 1024);
    // start telemetry
    eventLogger.start(0, 98, 10 * 1024);
    tlmChan.start(0, 97, 10 * 1024);
    prmDb.start(0, 96, 10 * 1024);

    pingRcvr.start(0, 100, 10 * 1024);

    // App
    flexTrak.start(0, 100, 10 * 1024);
    if (flextrak_connected) {
        serialDriver1.startReadThread(90, 20 * 1024);
        flexTrak.configureHardware();
    }

    eps.start(0, 100, 10 * 1024);
    piCamera.start(0, 100, 10 * 1024);
    predictor.start(0, 100, 10 * 1024);
    rockBlock.start(0, 100, 10 * 1024);
    temperatureProbes.start(0, 100, 10 * 1024);

    senseHat.start(0, 100, 10*1024);

    thermometer.start(0, 100, 10*1024);

    motionTracking.start(0, 100, 10*1024);

    barometer.start(0, 100, 10*1024);


    // Initialize socket server if and only if there is a valid specification
    if (hostname != NULL && port_number != 0) {
        socketIpDriver.startSocketTask(100, 10 * 1024, hostname, port_number);
    }

    // Set health ping entries
    Svc::HealthImpl::PingEntry pingEntries[] = {
        {3, 5, getHealthName(rateGroup1)},   // 0
        {3, 5, getHealthName(rateGroup2)},   // 1
        {3, 5, getHealthName(rateGroup3)},   // 2
        {3, 5, getHealthName(cmdDisp)},      // 3
        {3, 5, getHealthName(eventLogger)},  // 4
        {3, 5, getHealthName(cmdSeq)},       // 5
        {3, 5, getHealthName(tlmChan)},      // 6
        {3, 5, getHealthName(prmDb)},        // 7
        {3, 5, getHealthName(pingRcvr)},     // 8
        {3, 5, getHealthName(blockDrv)},     // 9
        {3, 5, getHealthName(flexTrak)},     // 10
        {3, 5, getHealthName(piCamera)},     // 11
        {3, 5, getHealthName(rockBlock)},    // 12
    };

    // register ping table
    health.setPingEntries(pingEntries, FW_NUM_ARRAY_ELEMENTS(pingEntries),
                          0x123);
    
    return false;
}

void exitTasks(void) {
    rateGroup1.exit();
    rateGroup2.exit();
    rateGroup3.exit();
    rateGroup4.exit();
    blockDrv.exit();
    cmdDisp.exit();
    eventLogger.exit();
    tlmChan.exit();
    prmDb.exit();
    cmdSeq.exit();
    pingRcvr.exit();
    // App
    eps.exit();
    flexTrak.exit();
    piCamera.exit();
    predictor.exit();
    rockBlock.exit();
    temperatureProbes.exit();
    senseHat.exit();
    thermometer.exit();
    motionTracking.exit();
    barometer.exit();

    // Join the component threads with NULL pointers to free them
    (void)rateGroup1.ActiveComponentBase::join(NULL);
    (void)rateGroup2.ActiveComponentBase::join(NULL);
    (void)rateGroup3.ActiveComponentBase::join(NULL);
    (void)rateGroup4.ActiveComponentBase::join(NULL);
    (void)blockDrv.ActiveComponentBase::join(NULL);
    (void)cmdDisp.ActiveComponentBase::join(NULL);
    (void)eventLogger.ActiveComponentBase::join(NULL);
    (void)tlmChan.ActiveComponentBase::join(NULL);
    (void)prmDb.ActiveComponentBase::join(NULL);
    (void)cmdSeq.ActiveComponentBase::join(NULL);
    (void)pingRcvr.ActiveComponentBase::join(NULL);
    // App
    (void)eps.ActiveComponentBase::join(NULL);
    (void)flexTrak.ActiveComponentBase::join(NULL);
    (void)piCamera.ActiveComponentBase::join(NULL);
    (void)predictor.ActiveComponentBase::join(NULL);
    (void)rockBlock.ActiveComponentBase::join(NULL);
    (void)temperatureProbes.ActiveComponentBase::join(NULL);
    (void)senseHat.ActiveComponentBase::join(NULL);
    (void)thermometer.ActiveComponentBase::join(NULL);
    (void)motionTracking.ActiveComponentBase::join(NULL);
    (void)barometer.ActiveComponentBase::join(NULL);
    socketIpDriver.exitSocketTask();
    (void)socketIpDriver.joinSocketTask(NULL);
    cmdSeq.deallocateBuffer(seqMallocator);
}
