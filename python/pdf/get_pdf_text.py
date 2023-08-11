# get_pdf_text.py

# 安装依赖包
# pip install PyPDF2
# pip install pdfplumber
# pip install pymupdf

# 运行脚本
# python get_pdf_text.py

import PyPDF2

with open('example.pdf', 'rb') as file:
    reader = PyPDF2.PdfReader(file)
    for page_num in range(len(reader.pages)):
        page = reader.pages[page_num]
        text = page.extract_text()
        print(f'Page {page_num+1}: {text}')

import pdfplumber

with pdfplumber.open('example.pdf') as pdf:
    for page_num in range(len(pdf.pages)):
        page = pdf.pages[page_num]
        text = page.extract_text()
        print(f'Page {page_num+1}: {text}')

import fitz

with fitz.open('example.pdf') as doc:
    for page_num in range(doc.page_count):
        page = doc.load_page(page_num)
        text = page.get_text("text")
        print(f'Page {page_num+1}: {text}')
