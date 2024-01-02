# 文件名: send_sms.py

#coding=utf-8

from aliyunsdkcore.client import AcsClient
from aliyunsdkcore.request import CommonRequest
client = AcsClient('LTAIqEab3HRpRm34', 'TrnLKl5Qdd7aiAxsUF9v57635y08IO', 'default')

request = CommonRequest()
request.set_accept_format('json')
request.set_domain('dysmsapi.aliyuncs.com')
request.set_method('POST')
request.set_version('2017-05-25')
request.set_action_name('SendSms')

request.add_query_param('PhoneNumbers', '18321965985')
request.add_query_param('SignName', '小小')
request.add_query_param('TemplateCode', 'SMS_155355731')
request.add_query_param('TemplateParam', '{"name":"test","state":"haha"}')

response = client.do_action(request)
# python2:  print(response) 
print(response)
#print(str(response, encoding = 'utf-8'))