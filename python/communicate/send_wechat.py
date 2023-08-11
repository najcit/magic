# send_wechat.py

from wxauto import WeChat

if __name__ == '__main__':
    # 保证本地微信已安装，并已登录
    # 获取当前微信客户端
    wx = WeChat()

    # 向某人发送消息（以`文件传输助手`为例）
    who = '文件传输助手'
    wx.ChatWith(who)  # 打开`文件传输助手`聊天窗口

    msg = '你好'
    wx.SendMsg(msg)  # 向`文件传输助手`发送消息：你好

    # 向某人发送文件（向`文件传输助手`发送文件）
    file = ['info.txt', 'sample.png']
    wx.SendFiles(file)  # 向`文件传输助手`发送文件
