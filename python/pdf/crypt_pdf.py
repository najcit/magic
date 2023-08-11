# crypt_pdf.py

# 运行脚本
# python crypt_pdf.py

import PyPDF2

# 加密 pdf
input_pdf = "table.pdf"
output_pdf = "encrypted.pdf"
password = "654321"

with open(input_pdf, "rb") as file:
    pdf_reader = PyPDF2.PdfReader(file)
    pdf_writer = PyPDF2.PdfWriter()

    for page_num in range(len(pdf_reader.pages)):
        pdf_writer.add_page(pdf_reader.pages[page_num])

    pdf_writer.encrypt(password)

    with open(output_pdf, "wb") as output:
        pdf_writer.write(output)
