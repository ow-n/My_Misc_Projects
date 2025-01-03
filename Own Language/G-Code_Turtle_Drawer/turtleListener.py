# Generated from turtle.g4 by ANTLR 4.13.1
from antlr4 import *
if "." in __name__:
    from .turtleParser import turtleParser
else:
    from turtleParser import turtleParser

# This class defines a complete listener for a parse tree produced by turtleParser.
class turtleListener(ParseTreeListener):

    # Enter a parse tree produced by turtleParser#start.
    def enterStart(self, ctx:turtleParser.StartContext):
        pass

    # Exit a parse tree produced by turtleParser#start.
    def exitStart(self, ctx:turtleParser.StartContext):
        pass


    # Enter a parse tree produced by turtleParser#G01LinearInterpolation.
    def enterG01LinearInterpolation(self, ctx:turtleParser.G01LinearInterpolationContext):
        pass

    # Exit a parse tree produced by turtleParser#G01LinearInterpolation.
    def exitG01LinearInterpolation(self, ctx:turtleParser.G01LinearInterpolationContext):
        pass


    # Enter a parse tree produced by turtleParser#G28ZeroReturn.
    def enterG28ZeroReturn(self, ctx:turtleParser.G28ZeroReturnContext):
        pass

    # Exit a parse tree produced by turtleParser#G28ZeroReturn.
    def exitG28ZeroReturn(self, ctx:turtleParser.G28ZeroReturnContext):
        pass


    # Enter a parse tree produced by turtleParser#setFeedRate.
    def enterSetFeedRate(self, ctx:turtleParser.SetFeedRateContext):
        pass

    # Exit a parse tree produced by turtleParser#setFeedRate.
    def exitSetFeedRate(self, ctx:turtleParser.SetFeedRateContext):
        pass


    # Enter a parse tree produced by turtleParser#M03SpindleStartClockwise.
    def enterM03SpindleStartClockwise(self, ctx:turtleParser.M03SpindleStartClockwiseContext):
        pass

    # Exit a parse tree produced by turtleParser#M03SpindleStartClockwise.
    def exitM03SpindleStartClockwise(self, ctx:turtleParser.M03SpindleStartClockwiseContext):
        pass


    # Enter a parse tree produced by turtleParser#M05SpindleStop.
    def enterM05SpindleStop(self, ctx:turtleParser.M05SpindleStopContext):
        pass

    # Exit a parse tree produced by turtleParser#M05SpindleStop.
    def exitM05SpindleStop(self, ctx:turtleParser.M05SpindleStopContext):
        pass



del turtleParser