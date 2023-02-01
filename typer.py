import keyboard as kb
import time
text = input('Text: ')
wpm = int(input('WPM: '))
wait = 1/((wpm*5)/60)
print(f'wait time: {wait}')
if wait<0:
    wait=0
time.sleep(2)
for char in text:
    kb.write(char)
    time.sleep(wait)