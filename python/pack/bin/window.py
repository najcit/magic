# window.py

# 生成图像化应用程序
# pyinstaller --onefile --windowed --clean --name window window.py --icon logo.ico

if __name__ == '__main__':
    import tkinter as tk
    window = tk.Tk()
    window.title("My Tkinter Window")
    window.geometry("400x300")
    label = tk.Label(window, text="Hello, Tkinter!")
    label.pack()
    window.mainloop()
