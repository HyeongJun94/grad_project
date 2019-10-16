#!/usr/bin/env python

import os
from Tkinter import *


root = Tk()
root.title("PC_ServerForGraduate")
root.geometry("200x200")

button1 = Button(root, text="run", command=lambda:os.system('./server'))
button1.grid(row=1, column=0)
 
root.mainloop()
