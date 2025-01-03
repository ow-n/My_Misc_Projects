def CNC_square():
    bigSquare = 100
    innerSquare = 80

    count = 0
    while bigSquare > innerSquare:
        print(f"G01 {0 + count} {bigSquare}")
        print(f"G01 {bigSquare} {bigSquare}")
        print(f"G01 {bigSquare} {0 + count}")
        print(f"G01 {1 + count} {0 + count}\n")
        count += 1
        bigSquare -= 1


def CNC_diagonal_TL(): #TopLeft
    xCord = 20
    yCord = 80
    depth = 20

    count = 1
    for i in range(depth):
        print(f"G01 {xCord} {yCord - count}")
        print(f"G01 {xCord + count} {yCord}")
        count +=1

def CNC_diagonal_BR(): #BottomRight
    xCord = 80
    yCord = 20
    depth = 20

    count = 1
    for i in range(depth):
        print(f"G01 {xCord} {yCord + count}")
        print(f"G01 {xCord - count} {yCord}")
        count +=1

# =================================================================================================

#CNC_square()
#CNC_diagonal_TL()
CNC_diagonal_BR()