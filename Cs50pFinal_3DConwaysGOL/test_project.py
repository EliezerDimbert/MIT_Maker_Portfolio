from final import findNeighborsOnAllAxis, canvasArr, main, clearBoard, runGeneration

def test_generation():
    canvasArr[9][9][9].visible = True
    canvasArr[9][9][8].visible = True
    canvasArr[8][8][9].visible = True
    canvasArr[8][8][8].visible = True
    runGeneration()
    assert canvasArr[8][9][9].visible == True
    assert canvasArr[8][9][8].visible == True
    assert canvasArr[9][8][9].visible == True
    assert canvasArr[9][8][8].visible == True
def test_neighbors():
    global canvasArr
    for x in range(0,10):
        for y in range(0,10):
            for z in range(0,10):
                canvasArr[x][y][z].visible = True
    assert findNeighborsOnAllAxis(canvasArr[9][9][9]) == 6
    assert findNeighborsOnAllAxis(canvasArr[4][4][4]) == 18

def test_clearBoard():
    global canvasArr
    clearBoard()
    for x in range(0,10):
        for y in range(0,10):
            for z in range(0,10):
                assert canvasArr[x][y][z].visible == False

if __name__ == "__main__":
    main()
