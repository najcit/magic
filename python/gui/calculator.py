from app import App, Controller


class Calculator(Controller):
    def __init__(self):
        super().__init__()
        self.index = 0
        self.values = [0.0, 0.0]
        self.operator = ""
        self.interrupt = False

    def division100(self):
        result = self.values[self.index] / 100
        self.values[self.index] = result
        self.data['input'].set(str(result))

    def sign(self):
        result = self.values[self.index] * -1
        self.values[self.index] = result
        self.data['input'].set(str(result))

    def clear(self):
        self.data['input'].set("0")
        self.values[self.index] = 0.0
        self.interrupt = False

    def reset(self):
        self.data['input'].set("0")
        self.index = 0
        self.values = [0.0, 0.0]
        self.interrupt = False

    def division(self):
        if self.operator == "":
            self.index = (self.index + 1) % 2
        self.operator = "/"
        self.interrupt = True

    def multiply(self):
        if self.operator == "":
            self.index = (self.index + 1) % 2
        self.operator = "x"
        self.interrupt = True

    def subtract(self):
        if self.operator == "":
            self.index = (self.index + 1) % 2
        self.operator = "-"
        self.interrupt = True

    def add(self):
        if self.operator == "":
            self.index = (self.index + 1) % 2
        self.operator = "+"
        self.interrupt = True

    def dot(self):
        val = str(self.data['input'].get())
        val = '0.' if val == '0' or self.interrupt else val + '.'
        self.values[self.index] = float(val)
        self.interrupt = False if self.interrupt else self.interrupt
        self.data['input'].set(val)

    def equal(self):
        result = ''
        if self.operator == "+":
            result = self.values[0] + self.values[1]
        elif self.operator == "-":
            result = self.values[0] - self.values[1]
        elif self.operator == "x":
            result = self.values[0] * self.values[1]
        elif self.operator == "/":
            result = self.values[0] / self.values[1]
        self.index = (self.index + 1) % 2
        self.values[self.index] = result
        self.operator = ''
        self.interrupt = True
        self.data['input'].set(str(result))

    def num7(self):
        val = str(self.data['input'].get())
        val = '7' if val == '0' or self.interrupt else val + '7'
        self.values[self.index] = float(val) if val.find('.') != -1 else int(val)
        self.interrupt = False if self.interrupt else self.interrupt
        self.data['input'].set(val)

    def num4(self):
        val = str(self.data['input'].get())
        val = '4' if val == '0' or self.interrupt else val + '4'
        self.interrupt = False if self.interrupt else self.interrupt
        self.values[self.index] = float(val) if val.find('.') != -1 else int(val)
        self.data['input'].set(val)

    def num1(self):
        val = str(self.data['input'].get())
        val = '1' if val == '0' or self.interrupt else val + '1'
        self.interrupt = False if self.interrupt else self.interrupt
        self.values[self.index] = float(val) if val.find('.') != -1 else int(val)
        self.data['input'].set(val)

    def num8(self):
        val = str(self.data['input'].get())
        val = '8' if val == '0' or self.interrupt else val + '8'
        self.interrupt = False if self.interrupt else self.interrupt
        self.values[self.index] = float(val) if val.find('.') != -1 else int(val)

        self.data['input'].set(val)

    def num5(self):
        val = str(self.data['input'].get())
        val = '5' if val == '0' or self.interrupt else val + '5'
        self.interrupt = False if self.interrupt else self.interrupt
        self.values[self.index] = float(val) if val.find('.') != -1 else int(val)
        self.data['input'].set(val)

    def num2(self):
        val = str(self.data['input'].get())
        val = '2' if val == '0' or self.interrupt else val + '2'
        self.interrupt = False if self.interrupt else self.interrupt
        self.values[self.index] = float(val) if val.find('.') != -1 else int(val)
        self.data['input'].set(val)

    def num9(self):
        val = str(self.data['input'].get())
        val = '9' if val == '0' or self.interrupt else val + '9'
        self.interrupt = False if self.interrupt else self.interrupt
        self.values[self.index] = float(val) if val.find('.') != -1 else int(val)
        self.data['input'].set(val)

    def num6(self):
        val = str(self.data['input'].get())
        val = '6' if val == '0' or self.interrupt else val + '6'
        self.interrupt = False if self.interrupt else self.interrupt
        self.values[self.index] = float(val) if val.find('.') != -1 else int(val)
        self.data['input'].set(val)

    def num3(self):
        val = str(self.data['input'].get())
        val = '3' if val == '0' or self.interrupt else val + '3'
        self.interrupt = False if self.interrupt else self.interrupt
        self.values[self.index] = float(val) if val.find('.') != -1 else int(val)
        self.data['input'].set(val)

    def num0(self):
        val = str(self.data['input'].get())
        val = '0' if val == '0' or self.interrupt else val + '0'
        self.interrupt = False if self.interrupt else self.interrupt
        self.values[self.index] = float(val) if val.find('.') != -1 else int(val)
        self.data['input'].set(val)


if __name__ == "__main__":
    app = App("calculator.xml", Calculator())
    app.run()
