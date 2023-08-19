# image.py

# 安装依赖
# pip install pillow
# 图片 raw.jpg

# 运行脚本
# python image.py

from PIL import Image, ImageDraw, ImageFont


def convert(input_path, dest_type, output_path=None, sizes=None):
    output_path = output_path or input_file.split('.')[0] + '.' + dest_type.lower()
    sizes = sizes or [(64, 64)]
    img = Image.open(input_path)
    img.save(output_path, format=dest_type, sizes=sizes)


def resize(input_path, output_path=None, size=None):
    output_path = output_path or 'resized.' + input_file.split('.')[1].lower()
    image = Image.open(input_path)
    size = size or (500, 500)
    resized_image = image.resize(size)
    resized_image.save(output_path)


def crop(input_path, output_path=None):
    output_path = output_path or 'cropped.' + input_file.split('.')[1].lower()
    image = Image.open(input_path)
    box = (100, 100, 400, 400)
    cropped_image = image.crop(box)
    cropped_image.save(output_path)


def merge(input_path_list):
    images = []
    new_width = 0
    new_height = 0
    for input_path in input_path_list:
        image = Image.open(input_path)
        images.append(image)
        new_width += image.width
        new_height = max(new_height, image.height)
    new_image = Image.new("RGB", (new_width, new_height))
    width_offset = 0
    for image in images:
        new_image.paste(image, (width_offset, 0))
        width_offset += image.width
    new_image.save("merged.jpg")


def overlay(input_path, bg_path):
    foreground_image = Image.open(input_path)
    if foreground_image.mode != "RGBA":
        foreground_image = foreground_image.convert("RGBA")
    background_image = Image.open(bg_path)
    background_image.paste(foreground_image, (0, 0), mask=foreground_image)
    background_image.save("overlie.jpg")


def with_text(bg_path, text_color=None, text_position=None, text_content=None):
    background_image = Image.open(bg_path)
    new_image = Image.new("RGB", background_image.size)
    new_image.paste(background_image, (0, 0))
    draw = ImageDraw.Draw(new_image)
    font = ImageFont.truetype("arial.ttf", 80)
    text_color = text_color or (255, 255, 0)
    text_position = text_position or (50, 50)
    text_content = text_content or "Hello, World!"
    draw.text(text_position, text_content, font=font, fill=text_color)
    new_image.save("with_text.jpg")


if __name__ == '__main__':
    input_file = 'raw.jpg'
    bg_file = 'bg.jpg'
    convert(input_file, 'PNG')
    convert(input_file, 'PDF')
    convert(input_file, 'ICO')
    convert(input_file, 'BMP')
    convert(input_file, 'GIF')
    resize(input_file)
    crop(input_file)
    merge([input_file, input_file, input_file])
    overlay(input_file, bg_file)
    with_text(bg_file)
