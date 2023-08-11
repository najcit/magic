#hook_mouse.py

import mouse


def on_event(event):
    print(f"{event} {type(event)}")


if __name__ == '__main__':
    mouse.hook(on_event)
    mouse.wait()
