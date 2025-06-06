# Generated from turtle.g4 by ANTLR 4.13.1
from antlr4 import *
from io import StringIO
import sys
if sys.version_info[1] > 5:
    from typing import TextIO
else:
    from typing.io import TextIO


def serializedATN():
    return [
        4,0,8,64,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,
        6,7,6,2,7,7,7,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,2,1,2,1,3,1,3,1,
        3,1,3,1,4,1,4,1,4,1,4,1,5,4,5,37,8,5,11,5,12,5,38,1,5,1,5,4,5,43,
        8,5,11,5,12,5,44,3,5,47,8,5,1,6,4,6,50,8,6,11,6,12,6,51,1,6,1,6,
        1,7,1,7,5,7,58,8,7,10,7,12,7,61,9,7,1,7,1,7,0,0,8,1,1,3,2,5,3,7,
        4,9,5,11,6,13,7,15,8,1,0,2,3,0,9,10,13,13,32,32,2,0,10,10,13,13,
        68,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,
        11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,1,17,1,0,0,0,3,21,1,0,0,0,5,
        25,1,0,0,0,7,27,1,0,0,0,9,31,1,0,0,0,11,36,1,0,0,0,13,49,1,0,0,0,
        15,55,1,0,0,0,17,18,5,71,0,0,18,19,5,48,0,0,19,20,5,49,0,0,20,2,
        1,0,0,0,21,22,5,71,0,0,22,23,5,50,0,0,23,24,5,56,0,0,24,4,1,0,0,
        0,25,26,5,70,0,0,26,6,1,0,0,0,27,28,5,77,0,0,28,29,5,48,0,0,29,30,
        5,51,0,0,30,8,1,0,0,0,31,32,5,77,0,0,32,33,5,48,0,0,33,34,5,53,0,
        0,34,10,1,0,0,0,35,37,2,48,57,0,36,35,1,0,0,0,37,38,1,0,0,0,38,36,
        1,0,0,0,38,39,1,0,0,0,39,46,1,0,0,0,40,42,5,46,0,0,41,43,2,48,57,
        0,42,41,1,0,0,0,43,44,1,0,0,0,44,42,1,0,0,0,44,45,1,0,0,0,45,47,
        1,0,0,0,46,40,1,0,0,0,46,47,1,0,0,0,47,12,1,0,0,0,48,50,7,0,0,0,
        49,48,1,0,0,0,50,51,1,0,0,0,51,49,1,0,0,0,51,52,1,0,0,0,52,53,1,
        0,0,0,53,54,6,6,0,0,54,14,1,0,0,0,55,59,5,35,0,0,56,58,8,1,0,0,57,
        56,1,0,0,0,58,61,1,0,0,0,59,57,1,0,0,0,59,60,1,0,0,0,60,62,1,0,0,
        0,61,59,1,0,0,0,62,63,6,7,0,0,63,16,1,0,0,0,6,0,38,44,46,51,59,1,
        6,0,0
    ]

class turtleLexer(Lexer):

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    T__0 = 1
    T__1 = 2
    T__2 = 3
    T__3 = 4
    T__4 = 5
    NUMBER = 6
    WS = 7
    COMMENT = 8

    channelNames = [ u"DEFAULT_TOKEN_CHANNEL", u"HIDDEN" ]

    modeNames = [ "DEFAULT_MODE" ]

    literalNames = [ "<INVALID>",
            "'G01'", "'G28'", "'F'", "'M03'", "'M05'" ]

    symbolicNames = [ "<INVALID>",
            "NUMBER", "WS", "COMMENT" ]

    ruleNames = [ "T__0", "T__1", "T__2", "T__3", "T__4", "NUMBER", "WS", 
                  "COMMENT" ]

    grammarFileName = "turtle.g4"

    def __init__(self, input=None, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.13.1")
        self._interp = LexerATNSimulator(self, self.atn, self.decisionsToDFA, PredictionContextCache())
        self._actions = None
        self._predicates = None


