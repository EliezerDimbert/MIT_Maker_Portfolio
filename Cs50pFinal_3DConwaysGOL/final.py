from vpython import *
import time
import threading


# 2 or 3 -> live
# 1 -> die
# >3 -> die
# 3 -> turn on

canvasSide = 10
spacing = 2

canvasArr = [[[sphere(visible=False, pos=vector(z * spacing,y * spacing, x * spacing)) for x in range(canvasSide)] for y in range(canvasSide)] for z in range(canvasSide)]
scene.width = 1000
scene.height = 1000
scene.userzoom = False
scene.center = vector(5,5,5)
frameRate = 10

pointer = sphere(pos=vector(0,0,0), color=color.orange, emissive=False)
pointerCol = 9
pointerRow = 9
pointerSlice = 9
quickPlaceBox = sphere(pos=vector(-1,0,0), color=color.blue, opacity=.3, radius=1.1, visible=False)

lowerLimitToLive = 3
upperLimitToLive = 5
neighborsToBeBorn = [4]

def processKeys(mypointer, mykeys):
    print(f"Detected keys: {keysdown()}")
    global pointerRow, pointerCol, pointerSlice, canvasArr, quickPlaceBox
    if 'left' in mykeys and pointerCol != 0:
        pointerCol -= 1
    if 'right' in mykeys and pointerCol != 9:
        pointerCol += 1
        
    if '(' in mykeys and 'shift' in mykeys and pointerSlice != 9:
        pointerSlice += 1
    if 'down' in mykeys and pointerRow != 0:
        pointerRow -= 1

    if '&' in mykeys and 'shift' in mykeys and pointerSlice != 0:
        pointerSlice -= 1
    elif 'up' in mykeys and pointerRow != 9:
        pointerRow += 1

    if ' ' in mykeys:
        canvasArr[pointerCol][pointerRow][pointerSlice].visible = True
        print("spawning at ", pointerCol, pointerRow, pointerSlice)
    
    if 'n' in mykeys:
        global alreadyCountedNeighbors
        alreadyCountedNeighbors = []
        print('x', findNeighborsOnAxis('x', pointer))
        print('y',findNeighborsOnAxis('y', pointer))
        print('z',findNeighborsOnAxis('z', pointer))
    
    if 'b' in mykeys:
        if quickPlaceBox.visible == False:
            quickPlaceBox.pos = vector(pointerCol * spacing, pointerRow * spacing, pointerSlice * spacing)
            quickPlaceBox.visible = True
        else:
            tempPointerPosX = int(pointer.pos.x / spacing)
            tempQuickSpherePosX = int(quickPlaceBox.pos.x / spacing)
            tempPointerPosY = int(pointer.pos.y / spacing)
            tempQuickSpherePosY = int(quickPlaceBox.pos.y / spacing)
            tempPointerPosZ = int(pointer.pos.z / spacing)
            tempQuickSpherePosZ = int(quickPlaceBox.pos.z / spacing)
            smallestX = min(tempPointerPosX,tempQuickSpherePosX)
            biggestX = max(tempPointerPosX,tempQuickSpherePosX)
            smallestY = min(tempPointerPosY,tempQuickSpherePosY)
            biggestY = max(tempPointerPosY,tempQuickSpherePosY)
            smallestZ = min(tempPointerPosZ,tempQuickSpherePosZ)
            biggestZ = max(tempPointerPosZ,tempQuickSpherePosZ)
            for x in range(smallestX, biggestX + 1):
                for y in range(smallestY, biggestY + 1):
                    for z in range(smallestZ, biggestZ + 1):
                        canvasArr[x][y][z].color = color.white
                        canvasArr[x][y][z].visible = True
            quickPlaceBox.visible = False

    if canvasArr[pointerCol][pointerRow][pointerSlice].visible == False:
        mypointer.pos = vector(pointerCol * spacing, pointerRow * spacing, pointerSlice * spacing)
        mypointer.opacity = 1
        mypointer.radius = 1
    else:
        mypointer.pos = vector(pointerCol * spacing, pointerRow * spacing, pointerSlice * spacing)
        mypointer.opacity = .5
        mypointer.radius = 1.2
    
    if 's' in mykeys:
        start_simulation()
    if 'p' in mykeys:
        stop_simulation()
    if 'c' in mykeys:
        clearBoard()
    if 'r' in mykeys:
        randomizeBoard()

def mvPointerU():
    global pointerRow
    if pointerRow != 9:
        pointerRow += 1
    pointer.pos = vector(pointerCol * spacing, pointerRow * spacing, pointerSlice * spacing)
def mvPointerR():
    global pointerCol
    if pointerCol != 9:
        pointerCol += 1
    pointer.pos = vector(pointerCol * spacing, pointerRow * spacing, pointerSlice * spacing)
def mvPointerD():
    global pointerRow
    if pointerRow != 0:
        pointerRow -= 1
    pointer.pos = vector(pointerCol * spacing, pointerRow * spacing, pointerSlice * spacing)
def mvPointerL():
    global pointerCol
    if pointerCol != 0:
        pointerCol -= 1
    pointer.pos = vector(pointerCol * spacing, pointerRow * spacing, pointerSlice * spacing)
def mvPointerF():
    global pointerSlice
    if pointerSlice != 9:
        pointerSlice += 1
    pointer.pos = vector(pointerCol * spacing, pointerRow * spacing, pointerSlice * spacing)
def mvPointerB():
    global pointerSlice
    if pointerSlice != 0:
        pointerSlice -= 1
    pointer.pos = vector(pointerCol * spacing, pointerRow * spacing, pointerSlice * spacing)

alreadyCountedNeighbors = []
def findNeighborsOnAxis(axis, mysphere):
    if axis is None or mysphere is None:
        return
    global canvasArr, canvasSide, alreadyCountedNeighbors
    # maxIndex = canvasSide - 1
    # minIndex = 0
    acceptedIndicies = [0,1,2,3,4,5,6,7,8,9]
    x = int(mysphere.pos.x / spacing)
    y = int(mysphere.pos.y / spacing)
    z = int(mysphere.pos.z / spacing)
    numNeighbors = 0
    for relitivex in [-1, 0, 1]:
        for relitivey in [-1,0,1]:
            xcheck = x
            ycheck = y
            zcheck = z
            # print(relitivex, relitivey)
            if relitivex == 0 and relitivey == 0:
                continue
            if axis == 'x':
                xcheck = x + relitivex
                ycheck = y + relitivey
            elif axis == 'y':
                zcheck = z + relitivex
                ycheck = y + relitivey
            elif axis == 'z':
                xcheck = x + relitivex
                zcheck = z + relitivey
            if xcheck in acceptedIndicies and ycheck in acceptedIndicies and zcheck in acceptedIndicies:
                if canvasArr[int(xcheck)][int(ycheck)][int(zcheck)].visible is True and canvasArr[int(xcheck)][int(ycheck)][int(zcheck)] not in alreadyCountedNeighbors:
                    numNeighbors += 1    
                    alreadyCountedNeighbors.append(canvasArr[int(xcheck)][int(ycheck)][int(zcheck)])
            # print('checking point: ', xcheck,ycheck,zcheck)
    # print(axis, numNeighbors)
    return numNeighbors
def findNeighborsOnAllAxis(mysphere):
    global alreadyCountedNeighbors
    alreadyCountedNeighbors = []
    totalNeighbors = 0
    totalNeighbors += findNeighborsOnAxis('x', mysphere)
    totalNeighbors += findNeighborsOnAxis('y', mysphere)
    totalNeighbors += findNeighborsOnAxis('z', mysphere)
    # print('tatalNeighbors =', totalNeighbors)
    return totalNeighbors

def runGeneration():
    global canvasSide
    currNeighbors = 0
    spheresToTurnOn = []
    spheresToTurnOff = []

    for x in range(canvasSide): 
        for y in range(canvasSide):
            for z in range(canvasSide):
                currSphere = canvasArr[x][y][z]
                if currSphere.visible == False:
                    currNeighbors = findNeighborsOnAllAxis(currSphere)
                    if currNeighbors in neighborsToBeBorn:
                        spheresToTurnOn.append(currSphere)
                        currSphere.color = color.green
                    else:
                        continue
                else:
                    if currNeighbors < lowerLimitToLive or currNeighbors > upperLimitToLive:
                        spheresToTurnOff.append(currSphere)
                    else:
                        currSphere.color = color.white

    for x in range(canvasSide): 
        for y in range(canvasSide):
            for z in range(canvasSide):
                currSphere = canvasArr[x][y][z]
                if currSphere in spheresToTurnOn:
                    currSphere.visible = True
                elif currSphere in spheresToTurnOff:
                    currSphere.visible = False


stop_event = threading.Event()
def continuousGeneration(stop_event):
    global frameRate
    while not stop_event.is_set():
        runGeneration()
        time.sleep(1/frameRate)
def start_simulation():
    global simulation_thread, stop_event
    stop_event.clear()  
    simulation_thread = threading.Thread(target=continuousGeneration, args=(stop_event,))
    simulation_thread.start()
def stop_simulation():
    global stop_event
    stop_event.set()

def randomizeBoard():
    for x in range(canvasSide): 
        for y in range(canvasSide):
            for z in range(canvasSide):
                currSphere = canvasArr[x][y][z]
                if round(random() * 8) == 1:
                    currSphere.color = color.white
                    currSphere.visible = True
                else:
                    currSphere.visible = False

def clearBoard():
    for x in range(canvasSide): 
        for y in range(canvasSide):
            for z in range(canvasSide):
                currSphere = canvasArr[x][y][z]
                currSphere.visible = False
                currSphere.color = color.white


def main():
    global canvasArr, pointer, upperLimitToLive, lowerLimitToLive, spacing
    box(pos=vector(4.5*spacing,4.5*spacing,4.5*spacing), width=10.2*spacing, height=10.2*spacing, length=10.2*spacing, opacity=.3)
    button(bind=mvPointerU, text="Up")
    button(bind=mvPointerR, text="Rht")
    button(bind=mvPointerD, text="Dwn")
    button(bind=mvPointerL, text="Lft")
    button(bind=mvPointerF, text="Fwd")
    button(bind=mvPointerB, text="Bck")
    button(bind=start_simulation, text="Start")
    button(bind=stop_simulation, text="Stop")
    button(bind=randomizeBoard, text="Randomize")
    button(bind=clearBoard, text="Clear")
    scene.append_to_caption("""
    <style>
        #top-right-text {
            position: fixed;
            top: 10px;
            right: 10px;
            background-color: rgba(255, 255, 255, 0.8);
            padding: 10px;
            border-radius: 5px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.2);
            font-family: Arial, sans-serif;
            font-size: 14px;
            z-index: 1000;
        }
    </style>
    <body>
        <div id="top-right-text">
            <h3>Instructions:</h3>
            <ul style="list-style-type: disc;">
                <li>Up/Right/Down/Left Arrow Keys: Move through your selected plane</li>
                <li>Shift + Up/Down: Move Between Planes</li>
                <li>B: Starts a box selection. Pressing again will fill a box from the initial position to the cursor</li>
                <li>Rotate using RMB | P: Pause | S: Start | R: Randomize | C: Clear | Space: Place one cell</li>
                <li>Less than 3 neighbors or greater than 5 neighbors - Die (invisible)</li>
                <li>Exactly 4 neighbors - Birth (green)</li>
                <li>Between 2 and 5 neighbors - Stay alive (white)
            </ul>
        </div> 
    </body>
    """)
    while True:
        rate(frameRate)
        if keysdown() is not []:
            allkeys = keysdown() 
            processKeys(pointer, allkeys)

if __name__ == "__main__":
    main()

