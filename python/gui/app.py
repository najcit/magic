import xml.etree.ElementTree as ElementTree
import tkinter as tk
from tkinter import ttk


class Controller:
    def __init__(self):
        self.app = None
        self.functions = {}
        self.data = {}

    def __getitem__(self, index):
        return self.functions[index] if index in self.functions else None

    def __setitem__(self, index, value):
        self.functions[index] = value


class App:
    def __init__(self, config, controller=None):
        self.xml_file = config
        self.app = tk.Tk()
        self.controller = controller
        self.controller.app = self.app

    @staticmethod
    def on_drag_start(event):
        widget = event.widget
        widget.drag_start_x = event.x
        widget.drag_start_y = event.y

    def on_drag_motion(self, event):
        widget = event.widget
        x = widget.winfo_pointerx() - widget.drag_start_x
        y = widget.winfo_pointery() - widget.drag_start_y
        self.app.geometry(f"+{x}+{y}")

    def parse_element(self, layout_element):
        elements = []
        for element in list(layout_element):
            elements.append({"type": element.tag, "layout": self.parse_element(element), "property": element.attrib})
        return elements

    def parse_layout(self):
        tree = ElementTree.parse(self.xml_file)
        root = tree.getroot()
        return {"type": root.tag, "layout": self.parse_element(root), "property": root.attrib}

    def create_control(self, parent, control, index=0):
        moveable = False
        if "moveable" in control["property"]:
            moveable = True if control["property"]["moveable"] == "True" else False
            control['property'].pop("moveable")
        control_type = control["type"]
        if control_type == "window":
            if "title" in control["property"]:
                parent.title(control["property"]["title"])
            if "geometry" in control["property"]:
                parent.geometry(control["property"]["geometry"])
            if "minsize" in control["property"]:
                width, height = control["property"]["minsize"].split("x")
                parent.minsize(width, height)
            if "icon" in control["property"]:
                parent.iconbitmap(control["property"]["icon"])
            if "bg" in control["property"]:
                parent.configure(bg=control["property"]["bg"])
            for element in control["layout"]:
                self.create_control(parent, element)
        elif control_type == "frame":
            frame = tk.Frame(parent, **control['property'])
            frame.pack()
            for index, element in enumerate(control["layout"]):
                self.create_control(frame, element, index)
        elif control_type == "row":
            frame = tk.Frame(parent, **control['property'])
            for index, element in enumerate(control["layout"]):
                self.create_control(frame, element, index)
            frame.pack()
        elif control_type == "column":
            frame = tk.Frame(parent, **control['property'])
            frame.grid(row=0, column=index)
            for index, element in enumerate(control["layout"]):
                self.create_control(frame, element, index)
        elif control_type == "button":
            if "command" in control['property']:
                command = control['property']['command']
                # print(command)
                if hasattr(self.controller, command):
                    self.controller[command] = getattr(self.controller, command)
                control['property']['command'] = self.controller[command]
            button = tk.Button(parent, **control['property'])
            button.pack()
        elif control_type == "label":
            label = tk.Label(parent, **control['property'])
            label.pack()
            if moveable:
                label.bind("<Button-1>", self.on_drag_start)
                label.bind("<B1-Motion>", self.on_drag_motion)
        elif control_type == "entry":
            if "textvariable" in control['property']:
                textvariable = control['property']['textvariable']
                self.controller.data[textvariable] = tk.StringVar()
                if "text" in control['property']:
                    self.controller.data[textvariable].set(control['property']["text"])
                    control['property'].pop("text")  # 如果移除，会造成 entry 控件不显示问题
                control['property']['textvariable'] = self.controller.data[textvariable]
            entry = tk.Entry(parent, **control['property'])
            entry.pack()
        elif control_type == "checkbutton":
            checkbutton = ttk.Checkbutton(parent, **control['property'])
            checkbutton.pack()
        elif control_type == "radiobutton":
            radiobutton = ttk.Radiobutton(parent, **control['property'])
            radiobutton.pack()
        elif control_type == "combobox":
            combobox = ttk.Combobox(parent, **control['property'])
            combobox.pack()

    def create_window(self, layout):
        self.create_control(self.app, layout)

    def run(self):
        layout = self.parse_layout()
        self.create_window(layout)
        self.app.mainloop()


if __name__ == "__main__":
    app = App("app.xml")
    app.run()
