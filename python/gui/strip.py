from app import App, Controller
import tkinter.colorchooser as cc


class Strip(Controller):
    def __init__(self):
        super().__init__()
        self.top = False

    def put_top(self):
        if self.app is not None:
            self.top = not self.top
            self.app.attributes('-topmost', self.top)
            self.app.overrideredirect(self.top)

    def choose_color(self):
        color = cc.askcolor()
        if color:
            self.app.configure(bg=color[1])
            self.app.nametowidget("frame1").configure(bg=color[1])
            self.app.nametowidget("frame1").nametowidget("column3").nametowidget("entry1").configure(bg=color[1])


if __name__ == "__main__":
    app = App("strip.xml", Strip())
    app.run()
