# hook_keyboard.py

import keyboard


def on_key_event(event):
    print(f"{event} {type(event)}")


if __name__ == '__main__':
    keyboard.hook(on_key_event)
    keyboard.wait()
