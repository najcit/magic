# get_pdf_image.py

# 运行脚本
# python get_pdf_image.py

import fitz

pdf = fitz.open('example.pdf')
for page_num in range(len(pdf)):
    page = pdf[page_num]
    image_list = page.get_images()
    for image_index, img in enumerate(image_list):
        xref = img[0]
        base_image = pdf.extract_image(xref)
        image_data = base_image["image"]
        with open(f'image_{page_num}_{image_index}.png', 'wb') as file:
            file.write(image_data)
