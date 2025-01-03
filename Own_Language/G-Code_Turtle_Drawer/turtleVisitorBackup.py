# Generated from turtle.g4 by ANTLR 4.13.1
from antlr4 import *
if "." in __name__:
    from .turtleParser import turtleParser
else:
    from turtleParser import turtleParser

# This class defines a complete generic visitor for a parse tree produced by turtleParser.

import turtle
tutu = turtle.Turtle()

class turtleVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by turtleParser#start.
    def visitStart(self, ctx:turtleParser.StartContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by turtleParser#G01LinearInterpolation.
    def visitG01LinearInterpolation(self, ctx:turtleParser.G01LinearInterpolationContext):
        target_x    = int(ctx.x_cord.text)
        target_y    = int(ctx.y_cord.text)
        tutu.goto(target_x, target_y)
        return self.visitChildren(ctx)


    # Visit a parse tree produced by turtleParser#G28ZeroReturn.
    def visitG28ZeroReturn(self, ctx:turtleParser.G28ZeroReturnContext):
        target_x    = int(ctx.x_cord.text)
        target_y    = int(ctx.y_cord.text)
        tutu.penup()
        tutu.goto(target_x, target_y)
        tutu.goto(0, 0)
        tutu.pendown()
        return self.visitChildren(ctx)


    # Visit a parse tree produced by turtleParser#setFeedRate.
    def visitSetFeedRate(self, ctx:turtleParser.SetFeedRateContext):
        speed = int(ctx.speed.text)
        tutu.speed(speed)
        return self.visitChildren(ctx)


    # Visit a parse tree produced by turtleParser#M03SpindleStartClockwise.
    def visitM03SpindleStartClockwise(self, ctx:turtleParser.M03SpindleStartClockwiseContext):
        tutu.pendown()
        return self.visitChildren(ctx)


    # Visit a parse tree produced by turtleParser#M05SpindleStop.
    def visitM05SpindleStop(self, ctx:turtleParser.M05SpindleStopContext):
        tutu.penup()
        return self.visitChildren(ctx)



del turtleParser



# Changing Function Names
# =================================================================================================

# Generated from turtle.g4 by ANTLR 4.13.1
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .turtleParser import turtleParser
else:
    from turtleParser import turtleParser

# This class defines a complete generic visitor for a parse tree produced by turtleParser.

import turtle
tutu = turtle.Turtle()

class turtleVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by turtleParser#start.
    def visitStart(self, ctx:turtleParser.StartContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by turtleParser#drawlineExpr.
    def visitG01(self, ctx:turtleParser.DrawlineExprContext):
        target_x    = int(ctx.x_cord.text)
        target_y    = int(ctx.y_cord.text)

        tutu.goto(target_x, target_y)
        
        """
        cur_pos     = tutu.pos()
        if target_x > cur_pos[0]:
            tutu.right( target_x - cur_pos[0])
        else:
            tutu.left( cur_pos[0] - target_x)

        if target_y > cur_pos[1]:
            tutu.forward( target_y - cur_pos[1])
        else:
            tutu.backward( cur_pos[1] - target_y)
        """
            
        return self.visitChildren(ctx)


    # Visit a parse tree produced by turtleParser#printlineExpr.
    def visitPrintlineExpr(self, ctx:turtleParser.PrintlineExprContext):
        print(f"Draw line to x={ctx.x_cord.text} y={ctx.y_cord.text}")
        return self.visitChildren(ctx)

del turtleParser
