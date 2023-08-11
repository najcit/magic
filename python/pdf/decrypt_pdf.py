# decrypt_pdf.py

# 运行脚本
# python decrypt_pdf.py

import PyPDF2

encrypted_pdf = "encrypted.pdf"
decrypted_pdf = "decrypted.pdf"

with open(encrypted_pdf, "rb") as file:
    pdf_reader = PyPDF2.PdfReader(file)
    pdf_writer = PyPDF2.PdfWriter()

    if pdf_reader.is_encrypted:
        pdf_reader.decrypt(password)

    for page_num in range(len(pdf_reader.pages)):
        pdf_writer.add_page(pdf_reader.pages[page_num])

    with open(decrypted_pdf, "wb") as output:
        pdf_writer.write(output)
