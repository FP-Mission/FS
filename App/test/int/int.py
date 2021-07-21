import os
import sys
import time
import platform
import subprocess
import unittest
from enum import Enum

filename = os.path.dirname(__file__)
gdsName = os.path.join(filename, "../../../fprime/Gds/src")
fprimeName = os.path.join(filename, "../../../fprime/Fw/Python/src")
sys.path.insert(0, gdsName)
sys.path.insert(0, fprimeName)

from fprime_gds.common.pipeline.standard import StandardPipeline
from fprime_gds.common.testing_fw import predicates
from fprime_gds.common.testing_fw.api import IntegrationTestAPI
from fprime_gds.common.utils.config_manager import ConfigManager
from fprime_gds.common.utils.event_severity import EventSeverity


class TestAppClass(object):
    @classmethod
    def setup_class(cls):
        cls.pipeline = StandardPipeline()
        config = ConfigManager()
        filename = os.path.dirname(__file__)
        path = os.path.join(
            filename,
            "../../build-artifacts/{}/dict/AppTopologyAppDictionary.xml".format(
                platform.system()
            ),
        )
        cls.pipeline.setup(config, path, "./tmp")
        cls.pipeline.connect("127.0.0.1", 50000)
        logpath = os.path.join(filename, "./logs")
        cls.api = IntegrationTestAPI(cls.pipeline, logpath)
        cls.case_list = []  # TODO find a better way to do this.
        cls.dictionary = path

    @classmethod
    def teardown_class(cls):
        cls.pipeline.disconnect()
        cls.api.teardown()

    def setup_method(self, method):
        self.case_list.append(method.__name__)
        self.api.start_test_case(method.__name__, len(self.case_list))

    def test_is_streaming(self):
        results = self.api.assert_telemetry_count(0, timeout=10)
        for result in results:
            msg = "received channel {} update: {}".format(
                result.get_id(), result.get_str()
            )
            print(msg)

    def assert_command(self, command, args=[], max_delay=None, timeout=5):

            cmd_id = self.api.translate_command_name(command)
            self.api.log(
                "Starting assert_command helper for {}({})".format(command, cmd_id)
            )
            events = []
            events.append(self.api.get_event_pred("OpCodeDispatched", [cmd_id, None]))
            events.append(self.api.get_event_pred("OpCodeCompleted", [cmd_id]))
            results = self.api.send_and_assert_event(command, args, events, timeout=timeout)
            if max_delay is not None:
                delay = results[1].get_time() - results[0].get_time()
                msg = "The delay, {}, between the two events should be < {}".format(
                    delay, max_delay
                )
                assert delay < max_delay, msg
            self.api.log("assert_command helper completed successfully")
            return results

if __name__ == "__main__":
    test = TestAppClass()
    test.setup_class()
