from antlr4 import * 
from turtleLexer import turtleLexer
from turtleParser import turtleParser
from turtleVisitor import turtleVisitor
import time

def main():
    lexer = turtleLexer (FileStream("turtle_test"))
    token_stream = CommonTokenStream(lexer)
    parser = turtleParser(token_stream)
    visitor = turtleVisitor()

    while True:
        tree = parser.start()
        if tree.expr() == None:
            break
        print(tree.toStringTree(recog=parser))
        visitor.visit(tree)

    time.sleep(2)

if __name__ == '__main__':
    main()
