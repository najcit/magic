# make_qrcode.py

# 依赖安装
# pip install qrcode
# pip install pillow
# pip install myqr

# 运行脚本
# python make_qrcode.py

# 备注说明
# 生成的带动态图的二维码，可能查看时只运行一次
# 可以通过 ScreenToGif 等 gif 编辑工具重新保存以下，调整为循环播放

def make_simple_qrcode(file_path="simple_qrcode.png"):
    import qrcode
    data = "hello world"
    # data = "https://www.baidu.com"
    img = qrcode.make(data)
    img.save(file_path)


def make_logo_qrcode(file_path="logo_qrcode.png"):
    from MyQR import myqr
    # words = 'https://www.baidu.com'
    words = "hello world"
    myqr.run(words=words, version=3, picture='logo.png', save_name=file_path)


def make_gif_qrcode(file_path="logo_qrcode.gif"):
    from MyQR import myqr
    # words = 'https://www.baidu.com'
    words = "hello world"
    myqr.run(words=words, version=3, picture='logo.gif', level='L',
             save_name=file_path, colorized=True, contrast=1.5)


if __name__ == '__main__':
    make_simple_qrcode()
    make_logo_qrcode()
    make_gif_qrcode()
