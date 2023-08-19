import PyInstaller.__main__

# 图形化应用程序
# pyinstaller window.py --onefile --clean --noconfirm --name window --icon logo.ico --distpath .
PyInstaller.__main__.run([
    'window.py',
    '--onefile',
    '--clean',
    '--noconfirm',
    '--windowed',
    '--name=window',
    '--icon=logo.ico',
    '--distpath=.'
])

# 命令行程序
# pyinstaller cmdline.py --onefile --clean --noconfirm --name cmdline --icon logo.ico --distpath .
PyInstaller.__main__.run([
    'cmdline.py',
    '--onefile',
    '--clean',
    '--noconfirm',
    '--console',
    '--name=cmdline',
    '--icon=logo.ico',
    '--distpath=.'
])
