# test_easyocr.py

import easyocr

# 创建OCR对象
reader = easyocr.Reader(['ch_sim', 'en'], model_storage_directory='./model', user_network_directory='./user_network')

# 读取图像并进行识别
result = reader.readtext('./ch.png')
# print(result)
for _rect, text, confidence in result:
    print(f'Text: {text}, Confidence: {confidence}')

# 读取图像并进行识别
result = reader.readtext('./en.png')
for _rect, text, confidence in result:
    print(f'Text: {text}, Confidence: {confidence}')
