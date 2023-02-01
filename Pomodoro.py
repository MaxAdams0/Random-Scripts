import time
import keyboard as kb

classes = []
segment = ""

def break_filter(classes):
    for i in range(len(classes)):
        if not i%4 == 0: break
        classes.insert(i)
        break_filter(classes)
    
    return classes

def wait(start, wait, index):
    print('lmao')

while True:
    print("Write 'stop' to end adding classes")
    section = input("Add a Class: ")
    if section is "stop": break
    classes.append(segment)

classes = break_filter(classes)

index = 0
class_ = classes[index]
print("Press space to start.")
kb.wait('space')
while True:
    start = time.time()
    wait(start, 15000, index)