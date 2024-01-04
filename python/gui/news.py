import datetime
from playwright.sync_api import Playwright, sync_playwright
import yaml
import tkinter as tk
import wx
import xml.etree.ElementTree as ElementTree


def run_360(playwright: Playwright):
    # browser = playwright.chromium.launch(headless=False)
    browser = playwright.chromium.launch()
    context = browser.new_context()
    page = context.new_page()
    page.goto("https://www.so.com/")
    page.wait_for_timeout(timeout=1000)
    # visible = page.is_visible(selector="#real_time_news")
    # print(visible)
    # enabled = page.is_enabled(selector=".change")
    # print(enabled)
    # 1 - 36 共 36 条热点
    data = []
    for _i in range(4):
        hot_topics = page.query_selector(selector="#real_time_news").query_selector_all(selector='.g-ellipsis')
        for topic in hot_topics:
            print(topic.inner_text(), topic.get_property('href'))
            data.append({
                'title': str(topic.inner_text()),
                'url': str(topic.get_property('href')),
                'source': '360'
            })
        page.query_selector(selector="#real_time_news").query_selector(selector='.change').click()
        page.wait_for_timeout(timeout=100)

    context.close()
    browser.close()
    return data


def run_baidu(playwright: Playwright) -> []:
    # browser = playwright.chromium.launch(headless=False)
    browser = playwright.chromium.launch()
    context = browser.new_context()
    page = context.new_page()
    page.goto("https://www.baidu.com/")
    page.wait_for_timeout(timeout=1000)
    # visible = page.is_visible(selector=".hotsearch-item")
    # print(visible)
    # enabled = page.is_enabled(selector=".hot-refresh")
    # print(enabled)

    # 0 - 29 共 30 条热点
    data = []
    for _i in range(5):
        hot_topics = page.query_selector_all(".hotsearch-item")
        for topic in hot_topics:
            print(topic.query_selector(".title-content-title").inner_text(),
                  topic.query_selector('.title-content').get_property('href'))
            data.append({
                'title': str(topic.query_selector(".title-content-title").inner_text()),
                'url': str(topic.query_selector('.title-content').get_property('href')),
                'source': '360'
            })
        page.query_selector(selector='.hot-refresh').click()
        page.wait_for_timeout(timeout=1000)

    context.close()
    browser.close()
    return data


def run_toutiao(playwright: Playwright) -> []:
    # browser = playwright.chromium.launch(headless=False)
    browser = playwright.chromium.launch()
    context = browser.new_context()
    page = context.new_page()
    page.goto("https://www.toutiao.com/")
    page.wait_for_timeout(timeout=10000)
    # visible = page.is_visible(selector=".article-item")
    # print(visible)
    # enabled = page.is_enabled(selector=".refresh")
    # print(enabled)
    # 0 - 50 共 51 条热点
    data = []
    for _i in range(5):
        hot_topics = page.query_selector_all(".article-item")
        for topic in hot_topics:
            print(topic.query_selector(".gui-title").inner_text(), topic.get_property('href'))
            data.append({
                'title': str(topic.query_selector(".gui-title").inner_text()),
                'url': str(topic.get_property('href')),
                'source': '360'
            })
        page.get_by_role("button", name="换一换", exact=True).click()
        page.wait_for_timeout(timeout=1000)

    context.close()
    browser.close()
    return data


def run():
    with sync_playwright() as pw:
        result = run_360(pw)
        name = '360#' + str(datetime.datetime.now().date()) + ".yaml"
        with open(name, 'w', encoding='utf8') as file:
            yaml.dump(result, file, allow_unicode=True)

    with sync_playwright() as pw:
        result = run_baidu(pw)
        name = 'baidu#' + str(datetime.datetime.now().date()) + ".yaml"
        with open(name, 'w', encoding='utf8') as file:
            yaml.dump(result, file, allow_unicode=True)

    with sync_playwright() as pw:
        result = run_toutiao(pw)
        name = 'toutiao#' + str(datetime.datetime.now().date()) + ".yaml"
        with open(name, 'w', encoding='utf8') as file:
            yaml.dump(result, file, allow_unicode=True)


class tkApp:
    def __init__(self, ui_path):
        self.app = tk.Tk()
        self.create(ui_path)
        self.load()

    def run(self):
        self.app.mainloop()

    def create(self, ui_path):
        root = ElementTree.parse(ui_path).getroot()
        print(root.tag, root.attrib)
        if 'title' in root.attrib:
            self.app.title(root.get('title'))
        if 'width' in root.attrib and 'height' in root.attrib:
            self.app.geometry(f"{root.get('width')}x{root.get('height')}")

        for child in root:
            print(child.tag, child.attrib)
            if child.tag == 'label':
                label = tk.Label(self.app, text=child.get('text'))
                label.pack()
            elif child.tag == 'entry':
                entry = tk.Entry(self.app)
                entry.insert(0, child.get('text'))
                entry.pack()
            elif child.tag == 'text':
                # value = child.get('text')
                child.attrib.pop('text')
                text = tk.Text(self.app, **child.attrib)
                # text.insert(tk.INSERT, value)
                text.pack()

    def load(self):
        name = '360#' + str(datetime.datetime.now().date()) + ".yaml"
        with open(name, 'r', encoding='utf8') as file:
            data = yaml.load(file, Loader=yaml.FullLoader)
            for item in data:
                self.app.nametowidget('360热搜内容').insert(tk.INSERT, item.get('title') + '\n')
        name = 'baidu#' + str(datetime.datetime.now().date()) + ".yaml"
        with open(name, 'r', encoding='utf8') as file:
            data = yaml.load(file, Loader=yaml.FullLoader)
            for item in data:
                self.app.nametowidget('百度热搜内容').insert(tk.INSERT, item.get('title') + '\n')
        name = 'toutiao#' + str(datetime.datetime.now().date()) + ".yaml"
        with open(name, 'r', encoding='utf8') as file:
            data = yaml.load(file, Loader=yaml.FullLoader)
            for item in data:
                self.app.nametowidget('头条热搜内容').insert(tk.INSERT, item.get('title') + '\n')


class wxApp:
    def __init__(self, ui_path):
        self.app = wx.App(False)
        self.window = wx.Frame(None)
        self.create(ui_path)
        self.load()

    def create(self, ui_path):
        # button = wx.Button(self.window, label="Click Me")
        # self.window.Bind(wx.EVT_BUTTON, self.on_button_click, button)
        root = ElementTree.parse(ui_path).getroot()
        # print(root.tag, root.attrib)
        if 'title' in root.attrib:
            self.window.SetTitle(root.get('title'))
        if 'width' in root.attrib and 'height' in root.attrib:
            self.window.SetSize(int(root.get('width')), int(root.get('height')))

        for child in root:
            print(child.tag, child.attrib)
            if child.tag == 'StaticText':
                # label = tk.Label(self.app, text=child.get('text'))
                label = wx.StaticText(self.window)
                label.SetLabel(child.get('text'))
            # elif child.tag == 'entry':
            #     entry = tk.Entry(self.app)
            #     entry.insert(0, child.get('text'))
            #     entry.pack()
            # elif child.tag == 'text':
            #     value = child.get('text')
            #     child.attrib.pop('text')
            #     text = tk.Text(self.app, **child.attrib)
            #     # text.insert(tk.INSERT, value)
            #     text.pack()

    def load(self):
        pass

    @staticmethod
    def on_button_click(event):
        print(event)
        wx.MessageBox('Hello wxPython', 'Message', wx.OK | wx.ICON_INFORMATION)

    def run(self):
        self.window.Show(True)
        self.app.MainLoop()


def main():
    # app = tkApp(ui_path='gui.xml')
    app = wxApp(ui_path='news.xml')
    app.run()


def run2():
    from nicegui import ui
    ui.input(label='Text', on_change=lambda e: text_input.set_text('Your Input: ' + e.value))
    text_input = ui.label()
    ui.number(label='Number', value=3.1415, format='%.2f',
              on_change=lambda e: number_input.set_text('Your Input: ' + str(e.value)))
    number_input = ui.label()
    ui.run()


if __name__ in {"__main__", "__mp_main__"}:
    # main()
    run()
