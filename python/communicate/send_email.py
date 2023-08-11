# 文件名：send_email.py

# -*- coding: utf-8 -*-

if __name__ == '__main__':
    import yagmail
    sender = '18321965985@163.com'                             # 发送者
    password = 'ITWAFVYFNCQAYLVU'                              # 授权码
    host = 'smtp.163.com'                                      # 邮箱服务地址
    receiver = ['najcit@163.com', '18321965985@163.com']       # 接收者
    subject = '测试邮件'                                        # 邮件主题
    contents = ['各位领导：', '请查收如下开会通知信息',           # 邮件内容
                yagmail.inline('sample.png'), 
                "<a href=https://www.baidu.com>具体查询网址"]
    attachments = ['sample.xlsx', 'sample.png']                # 附件
    mail = yagmail.SMTP(sender, password, host)
    mail.send(receiver, subject, contents, attachments)
    mail.close()
