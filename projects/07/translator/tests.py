"""
Tests for the translator.
"""

import io
import unittest

# noinspection PyCompatibility
from parser import Parser


class MyTestCase(unittest.TestCase):
    file = None
    parser = None

    def setUp(self):
        """
        Open the test file and initialize the parser.
        """
        self.file = open("test.vm")
        self.parser = Parser(self.file)

    def tearDown(self):
        """
        Close the file.
        """
        self.file.close()

    def testHasMoreCommands(self):
        self.assertTrue(self.parser.has_more_commands())

    def testHasNoMoreCommands(self):
        self.parser._file.seek(0, io.SEEK_END)
        self.assertFalse(self.parser.has_more_commands())


if __name__ == "__main__":
    unittest.main()