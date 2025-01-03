# Generated from turtle.g4 by ANTLR 4.13.1
# encoding: utf-8
from antlr4 import *
from io import StringIO
import sys
if sys.version_info[1] > 5:
	from typing import TextIO
else:
	from typing.io import TextIO

def serializedATN():
    return [
        4,1,8,21,2,0,7,0,2,1,7,1,1,0,1,0,3,0,7,8,0,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,3,1,19,8,1,1,1,0,0,2,0,2,0,0,23,0,6,1,0,0,0,2,
        18,1,0,0,0,4,7,3,2,1,0,5,7,1,0,0,0,6,4,1,0,0,0,6,5,1,0,0,0,7,1,1,
        0,0,0,8,9,5,1,0,0,9,10,5,6,0,0,10,19,5,6,0,0,11,12,5,2,0,0,12,13,
        5,6,0,0,13,19,5,6,0,0,14,15,5,3,0,0,15,19,5,6,0,0,16,19,5,4,0,0,
        17,19,5,5,0,0,18,8,1,0,0,0,18,11,1,0,0,0,18,14,1,0,0,0,18,16,1,0,
        0,0,18,17,1,0,0,0,19,3,1,0,0,0,2,6,18
    ]

class turtleParser ( Parser ):

    grammarFileName = "turtle.g4"

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    sharedContextCache = PredictionContextCache()

    literalNames = [ "<INVALID>", "'G01'", "'G28'", "'F'", "'M03'", "'M05'" ]

    symbolicNames = [ "<INVALID>", "<INVALID>", "<INVALID>", "<INVALID>", 
                      "<INVALID>", "<INVALID>", "NUMBER", "WS", "COMMENT" ]

    RULE_start = 0
    RULE_expr = 1

    ruleNames =  [ "start", "expr" ]

    EOF = Token.EOF
    T__0=1
    T__1=2
    T__2=3
    T__3=4
    T__4=5
    NUMBER=6
    WS=7
    COMMENT=8

    def __init__(self, input:TokenStream, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.13.1")
        self._interp = ParserATNSimulator(self, self.atn, self.decisionsToDFA, self.sharedContextCache)
        self._predicates = None




    class StartContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def expr(self):
            return self.getTypedRuleContext(turtleParser.ExprContext,0)


        def getRuleIndex(self):
            return turtleParser.RULE_start

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterStart" ):
                listener.enterStart(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitStart" ):
                listener.exitStart(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitStart" ):
                return visitor.visitStart(self)
            else:
                return visitor.visitChildren(self)




    def start(self):

        localctx = turtleParser.StartContext(self, self._ctx, self.state)
        self.enterRule(localctx, 0, self.RULE_start)
        try:
            self.state = 6
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [1, 2, 3, 4, 5]:
                self.enterOuterAlt(localctx, 1)
                self.state = 4
                self.expr()
                pass
            elif token in [-1]:
                self.enterOuterAlt(localctx, 2)

                pass
            else:
                raise NoViableAltException(self)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class ExprContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser


        def getRuleIndex(self):
            return turtleParser.RULE_expr

     
        def copyFrom(self, ctx:ParserRuleContext):
            super().copyFrom(ctx)



    class SetFeedRateContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a turtleParser.ExprContext
            super().__init__(parser)
            self.speed = None # Token
            self.copyFrom(ctx)

        def NUMBER(self):
            return self.getToken(turtleParser.NUMBER, 0)

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterSetFeedRate" ):
                listener.enterSetFeedRate(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitSetFeedRate" ):
                listener.exitSetFeedRate(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitSetFeedRate" ):
                return visitor.visitSetFeedRate(self)
            else:
                return visitor.visitChildren(self)


    class M05SpindleStopContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a turtleParser.ExprContext
            super().__init__(parser)
            self.copyFrom(ctx)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterM05SpindleStop" ):
                listener.enterM05SpindleStop(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitM05SpindleStop" ):
                listener.exitM05SpindleStop(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitM05SpindleStop" ):
                return visitor.visitM05SpindleStop(self)
            else:
                return visitor.visitChildren(self)


    class G01LinearInterpolationContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a turtleParser.ExprContext
            super().__init__(parser)
            self.x_cord = None # Token
            self.y_cord = None # Token
            self.copyFrom(ctx)

        def NUMBER(self, i:int=None):
            if i is None:
                return self.getTokens(turtleParser.NUMBER)
            else:
                return self.getToken(turtleParser.NUMBER, i)

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterG01LinearInterpolation" ):
                listener.enterG01LinearInterpolation(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitG01LinearInterpolation" ):
                listener.exitG01LinearInterpolation(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitG01LinearInterpolation" ):
                return visitor.visitG01LinearInterpolation(self)
            else:
                return visitor.visitChildren(self)


    class M03SpindleStartClockwiseContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a turtleParser.ExprContext
            super().__init__(parser)
            self.copyFrom(ctx)


        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterM03SpindleStartClockwise" ):
                listener.enterM03SpindleStartClockwise(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitM03SpindleStartClockwise" ):
                listener.exitM03SpindleStartClockwise(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitM03SpindleStartClockwise" ):
                return visitor.visitM03SpindleStartClockwise(self)
            else:
                return visitor.visitChildren(self)


    class G28ZeroReturnContext(ExprContext):

        def __init__(self, parser, ctx:ParserRuleContext): # actually a turtleParser.ExprContext
            super().__init__(parser)
            self.x_cord = None # Token
            self.y_cord = None # Token
            self.copyFrom(ctx)

        def NUMBER(self, i:int=None):
            if i is None:
                return self.getTokens(turtleParser.NUMBER)
            else:
                return self.getToken(turtleParser.NUMBER, i)

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterG28ZeroReturn" ):
                listener.enterG28ZeroReturn(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitG28ZeroReturn" ):
                listener.exitG28ZeroReturn(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitG28ZeroReturn" ):
                return visitor.visitG28ZeroReturn(self)
            else:
                return visitor.visitChildren(self)



    def expr(self):

        localctx = turtleParser.ExprContext(self, self._ctx, self.state)
        self.enterRule(localctx, 2, self.RULE_expr)
        try:
            self.state = 18
            self._errHandler.sync(self)
            token = self._input.LA(1)
            if token in [1]:
                localctx = turtleParser.G01LinearInterpolationContext(self, localctx)
                self.enterOuterAlt(localctx, 1)
                self.state = 8
                self.match(turtleParser.T__0)
                self.state = 9
                localctx.x_cord = self.match(turtleParser.NUMBER)
                self.state = 10
                localctx.y_cord = self.match(turtleParser.NUMBER)
                pass
            elif token in [2]:
                localctx = turtleParser.G28ZeroReturnContext(self, localctx)
                self.enterOuterAlt(localctx, 2)
                self.state = 11
                self.match(turtleParser.T__1)
                self.state = 12
                localctx.x_cord = self.match(turtleParser.NUMBER)
                self.state = 13
                localctx.y_cord = self.match(turtleParser.NUMBER)
                pass
            elif token in [3]:
                localctx = turtleParser.SetFeedRateContext(self, localctx)
                self.enterOuterAlt(localctx, 3)
                self.state = 14
                self.match(turtleParser.T__2)
                self.state = 15
                localctx.speed = self.match(turtleParser.NUMBER)
                pass
            elif token in [4]:
                localctx = turtleParser.M03SpindleStartClockwiseContext(self, localctx)
                self.enterOuterAlt(localctx, 4)
                self.state = 16
                self.match(turtleParser.T__3)
                pass
            elif token in [5]:
                localctx = turtleParser.M05SpindleStopContext(self, localctx)
                self.enterOuterAlt(localctx, 5)
                self.state = 17
                self.match(turtleParser.T__4)
                pass
            else:
                raise NoViableAltException(self)

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx





