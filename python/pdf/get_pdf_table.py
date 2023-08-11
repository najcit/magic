# get_pdf_table.py

# 运行脚本
# python get_pdf_table.py

import pdfplumber

read_path = r'table.pdf'
pdf = pdfplumber.open(read_path)
for page in pdf.pages:
    table = page.extract_table()
    print(table)
